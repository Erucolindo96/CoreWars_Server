#include "Operand.hpp"
namespace arbiter
{

    typedef std::shared_ptr<Core> CorePtr;

    //public
    Operand::Operand(IntegerRegister value ): value_(value)
    {}

    Operand::Operand(const Operand& other): value_(other.value_), type_(other.type_)
    {}

    Operand::Operand(const Operand &&other):  value_(other.value_), type_(other.type_)
    {}

    Operand& Operand::operator=(const Operand& other)
    {
        if(this == &other)
            return *this;

        value_ = other.value_;
        type_ = other.type_;
        return *this;
    }

    Operand& Operand::operator=(const Operand &&other)
    {
        if(this == &other)
            return *this;

        value_ = other.value_;
        type_ = type_;
        return *this;
    }

    IntegerRegister Operand::getValue()const
    {
        return value_;
    }
    AdressingType Operand::getAddressingType()const
    {
        return type_;
    }

    void Operand::setValue(const IntegerRegister value)
    {
        value_ = value;
    }
    void Operand::addValue(const IntegerRegister value)
    {
        value_ = value_ + value;
    }

    void Operand::subValue(const IntegerRegister value)
    {
        value_ = value_ - value;
    }






    //protected

}
