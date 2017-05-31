#pragma once
#include <qstring.h>
#include <qtcpsocket.h>
#include <qdatastream.h>

#include"pliki/arbiter_pliki/Arbiter.hpp"
#include<memory>
#include"pliki/arbiter_pliki/RealInstructions.hpp"
#include"pliki/arbiter_pliki/RealCoreCreators.hpp"
#include<iostream>
using namespace arbiter ;
using namespace std;

class Session : public Observer
{
public:
	Session(int c, int t, QString w1, QString def, QTcpSocket* s1, QString n);
	~Session();
	bool isFull;		//pole okre�laj�ce czy gracz mo�e do��czy� do sesji


	/**
	* @brief Metoda dodaj�ca gracza 2 do istniej�cej sesji
	*/
	void addClient2(QString w2, QTcpSocket* s1);
	

private:

    virtual void update(const IntegerRegister &mod_ins_ptr);

    /**
     * @brief parseWarriors Na razie przypisuje, niezale?nie od przys?anych od klienta wojownik�w,
     * obydwu wojom MOV 0 1
     */
    void parseWarriors();


	int core;		//wielko�� rdzenia w grze dla danej sesji
	int turns;		//ilo�� tur w grze dla danej sesji
	QString name;	//nazwa sesji
	QString warrior_1;		//wojownik gracza 1
	QString warrior_2;		//wojownika gracza 2
	QString defaultInstruction;		//domy�lna instruckja w rdzeniu

    Warrior real_war1, real_war2;

	QTcpSocket* client_1;		//gniazdo tcp klienta 1
	QTcpSocket* client_2;		//gniazdo tcp klienta 2


    WINNER startGame();
	/**
	* @brief Metoda tworz�ca wiadomo�� o pocz�tkowej planszy
	*/
	void sendBoard();

	/**
	* @brief Metoda tworz�ca wiadomo�� do aktualizacji planszy
	*/
	void actualizeBoard(int address, QString inst);

	/**
	* @brief Metoda wysy�aj�ca wiadomo�� do klient�w sesji
	*/
	void sendMesage(QByteArray &message);
	

};

