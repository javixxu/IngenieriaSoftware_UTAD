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

int main(){
    FSM fsm;

    fsm.AddState("Standing", std::make_shared<StandingState>());
    fsm.AddState("Ducking", std::make_shared<DuckingState>());
    fsm.AddState("Jumping", std::make_shared<JumpingState>());
    fsm.AddState("Diving", std::make_shared<DivingState>());

    fsm.AddTransitions("Ducking", "Standing");

    fsm.ChangeState("Standing");  // Comienza en estado Idle

    std::string input;

    while (true) {
        if (_kbhit()) {
            input = _getch(); 

            switch (input[0]) {
            case 'a':  // Idle
                fsm.ChangeState("Idle");
                break;
            case 'b':  // Cambiar al estado de correr
                fsm.ChangeState("Running");
                break;
            case 'q': 
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid key! Use WASD to move, R to run, Q to quit.\n";
                break;
            }

            fsm.Update();
          
        }
    }
    return 0;
}