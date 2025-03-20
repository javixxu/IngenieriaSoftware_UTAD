// Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <conio.h>  // Para _kbhit() y _getch() (captura de teclas en tiempo real)
#include "StateMachine.h"


class StandingState : public State {
public:
    void Enter() override {
        std::cout << "Entering StandingState\n";
    }

    void Update() override {
        std::cout << "Updating StandingState\n";
    }

    void Exit() override {
        std::cout << "Exiting StandingState\n";
    }
};

class DuckingState : public State {
public:
    void Enter() override {
        std::cout << "Entering DuckingState\n";
    }

    void Update() override {
        std::cout << "Updating DuckingState\n";
    }

    void Exit() override {
        std::cout << "Exiting DuckingState\n";
    }
};

class JumpingState : public State {
public:
    void Enter() override {
        std::cout << "Entering JumpingState\n";
    }

    void Update() override {
        std::cout << "Updating JumpingState\n";
    }

    void Exit() override {
        std::cout << "Exiting JumpingState\n";
    }
};

class DivingState : public State {
public:
    void Enter() override {
        std::cout << "Entering DivingState\n";
    }

    void Update() override {
        std::cout << "Updating DivingState\n";
    }

    void Exit() override {
        std::cout << "Exiting DivingState\n";
    }
};

int main() {

    //TAL CUAL LA FOTO DE CLASE PERO SI ESTAS EN DIVING Y PULSAS LA C SE CAMBIA A STANDING
    FSM fsm;

    fsm.AddState(typeid(StandingState).name(), std::make_shared<StandingState>());
    fsm.AddState(typeid(DuckingState).name(), std::make_shared<DuckingState>());
    fsm.AddState(typeid(JumpingState).name(), std::make_shared<JumpingState>());
    fsm.AddState(typeid(DivingState).name(), std::make_shared<DivingState>());

    fsm.ChangeState(typeid(StandingState).name());  // Comienza en estado Idle

    static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> transitions = {
           {typeid(StandingState).name(), {{"a", typeid(DuckingState).name()},{"b", typeid(JumpingState).name()}}},
           {typeid(DuckingState).name(),  {{"a", typeid(StandingState).name()}}},
           {typeid(JumpingState).name(),  {{"a", typeid(DivingState).name()}}},
           {typeid(DivingState).name(),  {{"c", typeid(StandingState).name()}}}
    };

    std::string input;

    while (true) {
        if (_kbhit()) {
            input = _getch(); 

            switch (input[0]) {
            case 'q': 
                std::cout << "Exiting...\n";
                return 0;
            }

            std::string currentState = fsm.GetCurrentState();

            auto stateIt = transitions.find(currentState);

            if (stateIt != transitions.end()) {
                auto inputIt = stateIt->second.find(input);
                if (inputIt != stateIt->second.end()) {
                    fsm.ChangeState(inputIt->second);
                }
            }

            fsm.Update();
          
        }
    }
    return 0;
}