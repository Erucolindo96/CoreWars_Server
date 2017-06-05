#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP
#include<map>
#include<string>
#include<memory>
#include"RealOperands.hpp"

namespace arbiter
{

class OperandFactory
{
public:

    typedef std::unique_ptr<Operand> OperandPtr;

    OperandFactory(const unsigned int core_size);
    OperandFactory(const OperandFactory &other);

    std::unique_ptr<Operand> createOperand(const std::string &operand_type,const std::string &value);


private:
    std::map<std::string, OperandPtr > callbacks_;

    void createFactory(const unsigned int CORE_SIZE);

    const unsigned int CORE_SIZE_;

    OperandFactory() = delete;

};


}
#endif // OPERANDFACTORY_HPP
