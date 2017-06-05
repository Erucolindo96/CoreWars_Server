#pragma once
#include <qstring.h>
#include <qtcpsocket.h>
#include <qdatastream.h>

#include"pliki/arbiter_pliki/Arbiter.hpp"
#include<memory>
#include"pliki/arbiter_pliki/RealInstructions.hpp"
#include"pliki/arbiter_pliki/RealCoreCreators.hpp"
#include<iostream>
#include<chrono>
#include<thread>
#include<sstream>
#include"pliki/arbiter_pliki/WarriorFactory.hpp"

#include"pliki/qstringconverter.hpp"
using namespace arbiter ;
using namespace std;

class Session : public Observer
{
public:
	Session(int c, int t, QString w1, QString def, QTcpSocket* s1, QString n);
	~Session();
	bool isFull;		//pole okreœlaj¹ce czy gracz mo¿e do³¹czyæ do sesji


	/**
	* @brief Metoda dodaj¹ca gracza 2 do istniej¹cej sesji
	*/
	void addClient2(QString w2, QTcpSocket* s1);
	

private:

    virtual void update(const IntegerRegister &mod_ins_ptr);




    const unsigned int MAX_ITERATIONS = 100;
	int core;		//wielkoœæ rdzenia w grze dla danej sesji
	int turns;		//iloœæ tur w grze dla danej sesji
	QString name;	//nazwa sesji
	QString warrior_1;		//wojownik gracza 1
	QString warrior_2;		//wojownika gracza 2
	QString defaultInstruction;		//domyœlna instruckja w rdzeniu

    Warrior real_war1, real_war2;



	QTcpSocket* client_1;		//gniazdo tcp klienta 1
	QTcpSocket* client_2;		//gniazdo tcp klienta 2


    WINNER startGame();
	/**
	* @brief Metoda tworz¹ca wiadomoœæ o pocz¹tkowej planszy
	*/
	void sendBoard();

	/**
	* @brief Metoda tworz¹ca wiadomoœæ do aktualizacji planszy
	*/
	void actualizeBoard(int address, QString inst);

	/**
	* @brief Metoda wysy³aj¹ca wiadomoœæ do klientów sesji
	*/
	void sendMesage(QByteArray &message);
	
    void sendWinner(WINNER winner);




};

