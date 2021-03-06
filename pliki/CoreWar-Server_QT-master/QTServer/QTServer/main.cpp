
#include"pliki/arbiter_pliki/Arbiter.hpp"
#include<memory>
#include"pliki/arbiter_pliki/RealInstructions.hpp"
#include"pliki/arbiter_pliki/RealCoreCreators.hpp"
#include<iostream>

#include"pliki/CoreWar-Server_QT-master/QTServer/QTServer/MyServer.h"
#include<QApplication>
using namespace arbiter ;
using namespace std;

class MokeObserver: public Observer
{
public:
    virtual void update(const IntegerRegister &mod_ins_ptr)
    {
        cout << "Wykonała sie isntrukcja :"+ to_string(mod_ins_ptr.getValue() )<< endl;
    }

};


int main(int argc, char *argv[])
{/*
    const unsigned  int CORE_SIZE = 10;

    IntegerRegister zero(CORE_SIZE, 0);
    IntegerRegister one(CORE_SIZE, 1);
    unique_ptr<Instruction> mov_ins(new MOVInstruction(unique_ptr<Operand>(new DirectOperand(zero) ), unique_ptr<Operand>(new DirectOperand(one) ) )  );

    Warrior war_1, war_2;
    war_1.addInstruction(mov_ins);
    war_2.addInstruction(mov_ins);

    MokeObserver moke;
    //std::unique_ptr<Observer> moke_obs_ptr(new MokeObserver());
    std::unique_ptr<CoreCreator> creator(new DATCreator(CORE_SIZE, war_1, war_2 ) );
    Arbiter sedzia(moke,std::move(creator) );

    int i=0;
    const int MAX_ITER = 100;
    while(sedzia.executeNextInstruction() && i<MAX_ITER)
    {
        ++i;
    }
    cout<<sedzia.getWinner();
*/
    QApplication a(argc, argv);
    //QTServer w;
    //w.show();
    MyServer server;
    server.startServer();
    return a.exec();
    return 0;
}
