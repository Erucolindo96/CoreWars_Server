#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T17:30:21
#
#-------------------------------------------------

QT       += core gui network widgets

#greaterThan(QT_MAJOR_VERSION, 3): QT += widgets

TARGET = CoreWars_Server
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 #dodane przeze mnie

SOURCES += \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/main.cpp \
    pliki/arbiter_pliki/Arbiter.cpp \
    pliki/arbiter_pliki/Core.cpp \
    pliki/arbiter_pliki/CoreCreator.cpp \
    pliki/arbiter_pliki/ExecutionLog.cpp \
    pliki/arbiter_pliki/Instruction.cpp \
    pliki/arbiter_pliki/IntegerRegister.cpp \
    pliki/arbiter_pliki/Operand.cpp \
    pliki/arbiter_pliki/Process.cpp \
    pliki/arbiter_pliki/Processor.cpp \
    pliki/arbiter_pliki/Queuemanager.cpp \
    pliki/arbiter_pliki/RealCoreCreators.cpp \
    pliki/arbiter_pliki/RealInstruction.cpp \
    pliki/arbiter_pliki/RealOperands.cpp \
    pliki/arbiter_pliki/Warrior.cpp \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/MyServer.cpp \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/QTServer.cpp \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/Session.cpp

HEADERS  += \
    pliki/arbiter_pliki/Arbiter.hpp \
    pliki/arbiter_pliki/Core.hpp \
    pliki/arbiter_pliki/CoreCreator.hpp \
    pliki/arbiter_pliki/ExecutionLog.hpp \
    pliki/arbiter_pliki/Instruction.hpp \
    pliki/arbiter_pliki/IntegerRegister.hpp \
    pliki/arbiter_pliki/Observer.hpp \
    pliki/arbiter_pliki/opcode.hpp \
    pliki/arbiter_pliki/Operand.hpp \
    pliki/arbiter_pliki/Process.hpp \
    pliki/arbiter_pliki/Processor.hpp \
    pliki/arbiter_pliki/Queuemanager.hpp \
    pliki/arbiter_pliki/RealCoreCreators.hpp \
    pliki/arbiter_pliki/RealInstructions.hpp \
    pliki/arbiter_pliki/RealOperands.hpp \
    pliki/arbiter_pliki/Warrior.hpp \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/MyServer.h \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/QTServer.h \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/Session.h

FORMS    += \
    pliki/CoreWar-Server_QT-master/QTServer/QTServer/QTServer.ui
