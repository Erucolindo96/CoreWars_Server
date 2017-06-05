#include "InstructionFactory.hpp"

namespace arbiter
{

    InstructionFactory::InstructionFactory()
    {
        createFactory();
    }


    void InstructionFactory::createFactory()
    {
        callbacks_.insert(Pair("DAT", InsPtr(new DATInstruction()) ) );
        callbacks_.insert(Pair("MOV", InsPtr(new MOVInstruction()) ) );
        callbacks_.insert(Pair("ADD", InsPtr(new ADDInstruction()) ) );
        callbacks_.insert(Pair("SUB", InsPtr(new SUBInstruction()) ) );
        callbacks_.insert(Pair("JMP", InsPtr(new JMPInstruction()) ) );
//tu reszta została do dopisania

        callbacks_.insert(Pair("SPL", InsPtr(new SPLInstruction()) ) );

    }

    InstructionFactory::InsPtr InstructionFactory::createInstruction(const std::string &opcode,const OperandPtr &oper_a,const OperandPtr &oper_b)
    {
        auto iter = callbacks_.find(opcode);
        if(iter == callbacks_.end() )
            return nullptr;

        InsPtr instruction = iter->second->clone();
        instruction->setOperandA(oper_a);
        instruction->setOperandB(oper_b);
        return instruction;
    }

}
