#ifndef WARRIORFACTORY_HPP
#define WARRIORFACTORY_HPP


#include<map>
#include<string>
#include<memory>
#include"Warrior.hpp"
#include"InstructionFactory.hpp"
#include"OperandFactory.hpp"
#include<sstream>

namespace arbiter
{

    class WarriorFactory
    {
    public:
        static Warrior createWarrior(const std::string warrior_code, const unsigned int CORE_SIZE );


    private:

        WarriorFactory() = delete;
        WarriorFactory(const WarriorFactory &other) = delete;
        WarriorFactory& operator=(const WarriorFactory &other) = delete;

    };

}

#endif // WARRIORFACTORY_HPP
