#include "Session.h"




Session::Session(int c, int t, QString w1, QString def, QTcpSocket* s1, QString n)
{
	core = c;
	turns = t;
	warrior_1 = w1;
	defaultInstruction = def;
	client_1 = s1;
	name = n;
	isFull = false;

}


Session::~Session()
{


}

void Session::addClient2(QString w2, QTcpSocket* s2)
{
	warrior_2 = w2;
	client_2 = s2;
	isFull = true;

	sendBoard();

}

void Session::sendBoard()
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << (qint16)3;

	out << (qint16)core;
	out << warrior_1;
	out << warrior_2;
	out << defaultInstruction;

	sendMesage(block);

}


void Session::actualizeBoard(int address, QString inst)
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << (qint16)4;	
	out << (qint16)address;
	out << inst;

	sendMesage(block);
}

void Session::sendMesage(QByteArray &message)
{

	client_1->write(message);
	client_2->write(message);

}
WINNER Session::startGame()
{
    const unsigned  int CORE_SIZE = 10;

    IntegerRegister zero(CORE_SIZE, 0);
    IntegerRegister one(CORE_SIZE, 1);
    unique_ptr<Instruction> mov_ins(new MOVInstruction(unique_ptr<Operand>(new DirectOperand(zero) ), unique_ptr<Operand>(new DirectOperand(one) ) )  );

    Warrior war_1, war_2;
    war_1.addInstruction(mov_ins);
    war_2.addInstruction(mov_ins);

    std::unique_ptr<Observer> moke_obs_ptr(new MokeObserver());
    std::unique_ptr<CoreCreator> creator(new DATCreator(CORE_SIZE, war_1, war_2 ) );
    Arbiter sedzia(moke_obs_ptr,std::move(creator) );

    while(sedzia.executeNextInstruction())
    {}

    return sedzia.getWinner();

}


void Session::update(const IntegerRegister &mod_ins_ptr)
{
    QString ins_name;
    unique_ptr<Instruction> &ins_ref = core_ptr_->getInstructionRef(mod_ins_ptr);
    if(dynamic_cast<MOVInstruction*>(ins_ref.get()) )
    {
        ins_name = "MOV";
    }
    else
    {
        ins_name = "DAT";
    }
    actualizeBoard(mod_ins_ptr.getValue(), ins_name);
}
