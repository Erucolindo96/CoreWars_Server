#include "Arbiter.hpp"
//#include<unistd.h>
#include<iostream>

namespace arbiter
{

    Arbiter::Arbiter(Observer &obs_ptr, CoreCreatorPtr core_creator):
    warrior1_(core_creator->getWarrior1Ref()), warrior2_(core_creator->getWarrior2Ref()),
    core_ptr_(),processor_(core_ptr_, core_creator->getCoreSize() ),
    manager_(core_creator->getCoreSize()),observer_ptr_(obs_ptr)
    {
     //   cnt = 0;
        //tworzymy rdzeń
        core_ptr_ = core_creator->createCore(obs_ptr);
        //tworzymy początkowe procesy graczy
        manager_.createFirstProcesses(core_creator->getPositionWarriorFirst(), core_creator->getPositionWarriorSecond());
    }
/*
    void Arbiter::createCore(const CoreCreatorPtr &core_creator)
    {
         core_ptr_ = core_creator->createCore(observer_ptr_);
    }
*/

    bool Arbiter::executeNextInstruction()
    {
        //QTimer timer;
    //sprawdzamy na wszelki wielki, czy w ogole jakies procesy zostały w kolejce
        if(!manager_.checkIfAny2WarriorsExist() )
            throw std::runtime_error("Arbiter - Zlecono wykonanie pomimo braku procesów do wykonania");

        Process proc_to_exec = manager_.getProcessToExecute();
        ExecutionLog log = processor_.executeProcess(proc_to_exec);

        if(log.is_proc_live_)
            manager_.saveProcess(log.next_pc_current_proc_);
        else
            manager_.removeActualProcess();

        if(log.is_proc_split_)
            manager_.addProcessToActualWarrior(log.next_pc_new_proc_);

        return manager_.checkIfAny2WarriorsExist();

  }

    WINNER Arbiter::getWinner()const
    {
        return manager_.getWinner();
    }

}

