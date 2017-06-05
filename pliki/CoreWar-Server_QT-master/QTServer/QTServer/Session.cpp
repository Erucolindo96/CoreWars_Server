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

    winner = startGame();

    //sendWinner(winner);

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

    //WINNER winner = startGame();

    //sendWinner(winner);
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

void Session::sendWinner(WINNER winner)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    QString result;

    switch(winner)
    {
        case FIRST:
        result = "Wygrał gracz nr 1";
        break;

        case SECOND:
        result = "Wygrał gracz nr 2";
        break;

        case NONE:
        result = "Remis";

    }

    out << (qint16)5;
    out << result;

    sendMesage(block);
    qDebug() << "Wyslelem wynik";
}

void Session::sendMesage(QByteArray &message)
{
    cout << "Wysylam wiadomosc";
	client_1->write(message);
	client_2->write(message);


}
WINNER Session::startGame()
{
    parseWarriors();//tworzy wojowników na podstawie wysłanych przez klientów kodów
    Warrior war_1 = real_war1, war_2 = real_war2;

    std::unique_ptr<CoreCreator> creator(new DATCreator(core, war_1, war_2 ) );
    Arbiter sedzia(*this, std::move(creator) );

    unsigned int i = 0;

    while(sedzia.executeNextInstruction() && i<MAX_ITERATIONS)
    {
    ++i;
    }
    qDebug() << tmpInstruction.size();

    sendBoard();

    sendAllInstructions();
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
    //actualizeBoard(mod_ins_ptr.getValue(), ins_name);
    tmpInstruction.push_back(TmpInstruction(mod_ins_ptr.getValue(), ins_name));

}
void Session::parseWarriors()
{//na razie nie zważa na przesłane przez klientów dane
    //tylko na sztywno wpisuje MOV 0 1

    IntegerRegister zero(core, 0);
    IntegerRegister one(core, 1);
    unique_ptr<Instruction> mov_ins(new MOVInstruction(unique_ptr<Operand>(new DirectOperand(zero) ), unique_ptr<Operand>(new DirectOperand(one) ) )  );

    real_war1.addInstruction(mov_ins);
    real_war2.addInstruction(mov_ins);

}

void Session::sendAllInstructions()
{
    for(int i=0; i < tmpInstruction.size(); ++i)
    {
        actualizeBoard(tmpInstruction[i].addr, tmpInstruction[i].ins);
    }

}


void Session::sendActualInstruction(int &n)
{
    actualizeBoard(tmpInstruction[n].addr, tmpInstruction[n].ins);
    ++n;
}

