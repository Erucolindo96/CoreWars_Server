#include "OperandFactory.hpp"

namespace arbiter
{

OperandFactory::OperandFactory(const unsigned int core_size): CORE_SIZE_(core_size)
{
    createFactory(core_size);
}

void OperandFactory::createFactory(const unsigned int CORE_SIZE)
{
    const IntegerRegister ZERO(CORE_SIZE);
    callbacks_.insert(std::pair<std::string, OperandPtr>("#", OperandPtr(new ImmidiateOperand(ZERO)) ) );
    callbacks_.insert(std::pair<std::string, OperandPtr>("", OperandPtr(new DirectOperand(ZERO)) ) );
    callbacks_.insert(std::pair<std::string, OperandPtr>("@", OperandPtr(new IndirectOperand(ZERO)) ) );
    callbacks_.insert(std::pair<std::string, OperandPtr>("<", OperandPtr(new IndirectDecrementOperand(ZERO)) ) );

}

std::unique_ptr<Operand> OperandFactory::createOperand(const std::string &operand_type,const std::string &value)
{
    auto iter = callbacks_.find(operand_type);
    if(iter == callbacks_.end() )
        return nullptr;
    int val;
    try
    {
        val = std::stoi(value);
    }catch(std::invalid_argument e)
    {
        return nullptr;//bo nie da się utworzyć z tego stringa liczby
    }

    OperandPtr operand = (*iter).second->clone();
    operand->setValue(IntegerRegister(CORE_SIZE_, val) );
    return operand;

}

}
