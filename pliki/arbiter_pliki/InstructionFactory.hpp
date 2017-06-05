#ifndef INSTRUCTIONFACTORY_HPP
#define INSTRUCTIONFACTORY_HPP

#include<map>
#include<string>
#include<memory>
#include"RealInstructions.hpp"


namespace arbiter
{

class InstructionFactory
{
public:

    typedef std::unique_ptr<Operand> OperandPtr;
    typedef std::unique_ptr<Instruction> InsPtr;
    typedef std::pair<std::string, InsPtr> Pair;

    InstructionFactory();

    InsPtr createInstruction(const std::string &opcode,const OperandPtr &oper_a,const OperandPtr &oper_b);


private:
    std::map<std::string, InsPtr > callbacks_;


    InstructionFactory(const InstructionFactory &other) = delete;


    void createFactory();
};

}
#endif // INSTRUCTIONFACTORY_HPP
