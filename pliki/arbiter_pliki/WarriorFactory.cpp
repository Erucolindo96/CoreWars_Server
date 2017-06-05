#include "WarriorFactory.hpp"

namespace arbiter
{
    Warrior WarriorFactory::createWarrior(const std::string warrior_code, const unsigned int CORE_SIZE)
    {

        Warrior returned;
        //tworzymy fabryki instrucji i operandów
        OperandFactory op_factory(CORE_SIZE);
        InstructionFactory ins_factory;
        std::stringstream stream;
        stream << warrior_code;
        std::string oper_a, oper_b, opcode, val_a, val_b;

        OperandFactory::OperandPtr operand_a, operand_b;
        InstructionFactory::InsPtr instruction;
        do
        {
            stream>>opcode;
            stream>>oper_a;
            stream>>oper_b;
            //trzeba oddzielić wartość operandu od jego typu
            if(oper_a.size()== 1)//nie ma specyfikacji typu
            {
                val_a = oper_a;
                oper_a = "";
            }
            else
            {
                val_a = oper_a.substr(1);//wartość
                oper_a = oper_a.substr(0,1);//specyfikator typu
            }
            //analogicznie dla drugiego operandu
            if(oper_b.size()== 1)//nie ma specyfikacji typu
            {
                val_b = oper_b;
                oper_b = "";
            }
            else
            {
                val_b = oper_b.substr(1);//wartość
                oper_b = oper_b.substr(0,1);//specyfikator typu
            }

            operand_a = op_factory.createOperand(oper_a, val_a);
            operand_b = op_factory.createOperand(oper_b, val_b);
            if(operand_a.get() == nullptr || operand_b.get() == nullptr)
                throw std::invalid_argument("WarriorFactory: Nieprawidłowy format kodu wojownika");

            instruction = ins_factory.createInstruction(opcode, operand_a, operand_b);
            if(instruction.get() == nullptr)
                throw std::invalid_argument("WarriorFactory: Nieprawidłowy format kodu wojownika");

            returned.addInstruction(instruction);
        }while(!stream.eof());

        return returned;

    }

}

