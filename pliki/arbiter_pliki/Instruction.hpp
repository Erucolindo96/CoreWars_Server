﻿#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP


#include"Operand.hpp"
#include <stdexcept>
#include <memory>
#include "IntegerRegister.hpp"
#include"Core.hpp"
#include"ExecutionLog.hpp"
namespace arbiter
{



enum Opcode
{
DAT,
MOV,
ADD,
SUB,
JMP,
JMZ,
JMN,
DJN,
CMP,
SPL,
SLT
};



     class Core;
     class Operand;

/**
 * Instrukcja - klasa implementująca wzorzec komendy. Jest to klasa abstrakcyjna - z niej będą dziedziczyć rzeczywiste instrukcje.
 * Instrukcje znajdują się w rdzeniu. Zawierają dwa operandy(również komendy), reprezentujące sposoby adresowania. Zawiera również rozmiar swojego rdzenia(operacje muszą być wykonywane modulo rozmiar rdzenia).
 * Aby mogła nadpisać rdzeń musi mieć do niego dostęp, Dajemy więc jej shared_ptr do rdzenia.
 *
 * Wykonanie instrukcji:
 * 1.Najpierw obliczane są operandy.
 * 2.Potem modyfikowany jest rdzeń(w zależności od tego jaka jest to instrukcja rzeczywista - metoda czysto wirtualna).
 * 3.Zwraca też wyniki wykonania instrukcji
 * @brief The Instruction class
 */

class Instruction
{
public:


    typedef std::unique_ptr<Core> CorePtr;
    typedef std::unique_ptr<Operand> OperandPtr;
    typedef std::unique_ptr<Instruction> InsPtr;


    explicit Instruction();
    Instruction(const Instruction& other);
    Instruction( Instruction &&other);

    explicit Instruction(const OperandPtr& operand_A, const OperandPtr& operand_B);

    virtual Instruction& operator=(const Instruction& other);
    virtual Instruction& operator=( Instruction &&other);

    IntegerRegister getValueOperandA()const;
    IntegerRegister getValueOperandB()const;

    OperandPtr& getOperandARef();
    OperandPtr& getOperandBRef();

    Opcode getOpcode()const;

    OperandPtr operandA() const;
    OperandPtr operandB() const;

    void setOperandA(const OperandPtr& operand);
    void setOperandB(const OperandPtr& operand);

    /**
     * @brief execute Wykonuje instrukcję, tzn oblicza argumenty, modyfikuje rdzeń, i zwraca do wołającego informację o wykonaniu
     * @return Informacja o wykonaniu instrukcji.
     */
    virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) = 0;
    virtual InsPtr clone()const = 0;

    virtual ~Instruction()  ;

protected:

    OperandPtr operand_A_;
    OperandPtr operand_B_;
    Opcode opcode_;
};




//    std::vector<std::unique_ptr<Instruction> >&& copyInstructionVector(const std::vector<std::unique_ptr<Instruction> > copy_vect);
}
#endif // INSTRUCTION_HPP
