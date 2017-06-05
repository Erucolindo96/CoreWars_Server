#ifndef STRINGOPCODEFACTORY_HPP
#define STRINGOPCODEFACTORY_HPP

#include<map>
#include<string>
#include"pliki/arbiter_pliki/Instruction.hpp"


namespace arbiter {


class StringOpcodeFactory
{
public:
    static std::string createStringFromOpcode(const arbiter::Opcode opcode);



private:
    static std::map<arbiter::Opcode, std::string> callbacks_;
    static bool fabricWasCreated_;

    static void createFactory();

    StringOpcodeFactory() = delete;
    StringOpcodeFactory(const StringOpcodeFactory &other) = delete;


};




}
#endif // STRINGOPCODEFACTORY_HPP
