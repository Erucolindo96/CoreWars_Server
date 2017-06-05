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
    std::cout<<QStringConverter::convertQString(warrior_1)<<endl;
    std::cout<<"Koniec\n";
    //   std::cout<<QStringConverter::convertQString(warrior_2)<<endl;

}


Session::~Session()
{


}
/*
Warrior Session::warriorInstance(string warrior_code)
{
    stringstream stream;
    //string warrior_c = QStringConverter::convertQString(warrior_code);
    Warrior war;

    std::unique_ptr<Operand> operand_a, operand_b;
    std::unique_ptr<Instruction> ins;

    stream << warrior_code;
    string opcode, oper_a, oper_b, val_a, val_b ;
    bool isFirstDirect = false, isSecondDirect = false;
    do
    {
        stream>>opcode;
        stream>>oper_a;
        stream>>oper_b;
        //wnioskujemy typu operandów
        if(oper_a.at(0) == '#' )
            operand_a = std::unique_ptr<Operand>(new ImmidiateOperand(IntegerRegister(core)));
        else if(oper_a.at(0) == '@')
            operand_a = std::unique_ptr<Operand>(new IndirectOperand(IntegerRegister(core)));
        else if(oper_a.at(0) == '<')
            operand_a = std::unique_ptr<Operand>(new IndirectDecrementOperand(IntegerRegister(core)));
        else
        {
            isFirstDirect = true;//od razu ustawiamy wartość operandu
            operand_a = std::unique_ptr<Operand>(new DirectOperand(IntegerRegister(core, std::stoi(oper_a) )));

        }

        if(oper_b.at(0) == '#')
            operand_b = std::unique_ptr<Operand>(new ImmidiateOperand(IntegerRegister(core)));
        else if(oper_b.at(0) == '@')
            operand_b = std::unique_ptr<Operand>(new IndirectOperand(IntegerRegister(core)));
        else if(oper_b.at(0) == '<')
            operand_b = std::unique_ptr<Operand>(new IndirectDecrementOperand(IntegerRegister(core)));
        else
        {
            isSecondDirect = true;//od razu ustawiamy wartość operandu
            operand_b = std::unique_ptr<Operand>(new DirectOperand(IntegerRegister(core, std::stoi(oper_b) )));
        }
            //wnioskujemy wartości operandów
        if(!isFirstDirect)
        {
            val_a = oper_a.substr(1);
            operand_a->setValue(IntegerRegister(core, std::stoi(val_a) ) );
            isFirstDirect = false;
        }
        if(!isSecondDirect)
        {
            val_b = oper_b.substr(1);
            operand_b->setValue(IntegerRegister(core,std::stoi(val_b)  ) );
            isSecondDirect = false;
        }
            //wnioskujemy typ instrkcji
        if(opcode == "DAT")
            ins = std::unique_ptr<Instruction>(new DATInstruction(operand_a, operand_b));
        else if(opcode =="MOV")
            ins = std::unique_ptr<Instruction>(new MOVInstruction(operand_a, operand_b));
        else if(opcode == "ADD")
            ins = std::unique_ptr<Instruction>(new ADDInstruction(operand_a, operand_b));
        //dodajemy instrukcję do wojownika
        war.addInstruction(ins);
        opcode.clear();
        oper_a.clear();
        oper_b.clear();
        val_a.clear();
        val_b.clear();

    }while(!stream.eof());
    return war;

}
*/
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


    WINNER winner = startGame();

    sendWinner(winner);
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
}

void Session::sendMesage(QByteArray &message)
{
    long client1_sended, client2_sended;

    client1_sended = client_1->write(message);
    client2_sended = client_2->write(message);

    std::cout<<"Wyslano do klienta 1 : "+ std::to_string(client1_sended)<<std::endl;
    std::cout<<"Wyslano do klienta 2 : "+ std::to_string(client2_sended)<<std::endl<<std::endl;

}
WINNER Session::startGame()
{
    //parseWarriors();//tworzy wojowników na podstawie wysłanych przez klientów kodów
    //Warrior war_1 = real_war1, war_2 = real_war2;

    string war_1 = QStringConverter::convertQString(warrior_1), war_2 = QStringConverter::convertQString(warrior_2);

    std::unique_ptr<CoreCreator> creator(new DATCreator(core, WarriorFactory::createWarrior(war_1, core) ,WarriorFactory::createWarrior(war_2,core) ) );
    Arbiter sedzia(*this, std::move(creator) );

    int i = 0;

  //  std::cout<<"Śpie"<<std::endl;

    //std::this_thread::sleep_for( std::chrono::milliseconds(500)  );


    while(sedzia.executeNextInstruction() && i<turns)
    {

        //std::cout<<"Śpie"<<std::endl;

        //std::this_thread::sleep_for( std::chrono::milliseconds(100)  );

        ++i;
    }

    return sedzia.getWinner();
}


void Session::update(const IntegerRegister &mod_ins_ptr)
{
    QString ins_name;
    unique_ptr<Instruction> &ins_ref = core_ptr_->getInstructionRef(mod_ins_ptr);
    if(ins_ref->getOpcode() == MOV )
    {
        ins_name = "MOV";
    }
    else if (ins_ref->getOpcode() == DAT)
    {
        ins_name = "DAT";
    }
    else
    {
        ins_name = "ADD";
    }
    actualizeBoard(mod_ins_ptr.getValue(), ins_name);
}
/*
void Session::parseWarriors()
{//na razie nie zważa na przesłane przez klientów dane
    //tylko na sztywno wpisuje MOV 0 1

    IntegerRegister zero(core, 0);
    IntegerRegister one(core, 1);
    unique_ptr<Instruction> mov_ins(new MOVInstruction(unique_ptr<Operand>(new DirectOperand(zero) ), unique_ptr<Operand>(new DirectOperand(one) ) )  );

    real_war1.addInstruction(mov_ins);
    real_war2.addInstruction(mov_ins);

}
*/
