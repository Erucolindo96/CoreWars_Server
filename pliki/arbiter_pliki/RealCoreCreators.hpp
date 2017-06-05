#ifndef REALCORECREATORS_HPP
#define REALCORECREATORS_HPP

#include"CoreCreator.hpp"
#include"RealInstructions.hpp"

#include<memory>
namespace arbiter
{




    /**
    * @brief The DATCreator class Tworzy rdzeń zapełniony instrukcjami DAT
    *
    */
    class DATCreator : public CoreCreator
    {
    public:

        typedef std::unique_ptr<Core> CorePtr;

        DATCreator(const unsigned int CORE_TO_CREATE_SIZE, const Warrior &warrior_1, const Warrior &warrior_2 );

         virtual CorePtr createCore(Observer &obs_ptr) const;
        virtual void modifyCore(CorePtr &existed_core_ptr)const;
    };

    class DefInsCreator: public CoreCreator
    {
    public:
        typedef std::unique_ptr<Core> CorePtr;
        typedef std::unique_ptr<Instruction> InsPtr;

        DefInsCreator(const unsigned int CORE_TO_CREATE_SIZE, const Warrior &warrior_1, const Warrior &warrior_2, const InsPtr&default_ins  );

        virtual CorePtr createCore(Observer &obs_ptr) const;
        virtual void modifyCore(CorePtr &existed_core_ptr)const;
    private:
        InsPtr def_ins_;
    };


}
#endif // REALCORECREATORS_HPP
