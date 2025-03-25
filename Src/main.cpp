#include <iostream>
#include <memory>
#include <unordered_map>
#include <conio.h>  
#include "CommandPatern.h"
#include <tigr/tigr.h>

// Receiver (Personaje)
class Character {
public:
    int x, y;
    Character() : x(100), y(100) {}
    void Move(int dx, int dy) {
        x += dx;
        y += dy;
    }
    void UndoMove(int dx, int dy) {
        x -= dx;
        y -= dy;
    }
};

class MoveCommand :public Command {
    Character* character;
    unsigned gamepad;
public:
    MoveCommand(Character* cha, unsigned game):character(cha),gamepad(game) {
    }
    void execute() override {
        character->x += !!(gamepad & 8) - !!(gamepad & 4);
        character->y += !!(gamepad & 2) - !!(gamepad & 1);
    }
};

int main() {
	Tigr* screen = tigrWindow(800, 600, "Command Pattern - Character Movement", 0);
    Character character;
    std::vector<unsigned> commands;

    bool is_recording = true;
    int frame = 0;
    while (!tigrClosed(screen)) {
        if (tigrKeyDown(screen, 'R')) is_recording = !is_recording, frame = 0;

        unsigned gamepad = 0;
        
        // recording
        if (is_recording) {

            gamepad |= tigrKeyHeld(screen, TK_UP) * 1;
            gamepad |= tigrKeyHeld(screen, TK_DOWN) * 2;
            gamepad |= tigrKeyHeld(screen, TK_LEFT) * 4;
            gamepad |= tigrKeyHeld(screen, TK_RIGHT) * 8;

            commands.push_back(gamepad);

        }
        else {
            
            gamepad = commands[frame++ % commands.size()];
        }

        character.x += !!(gamepad & 8) - !!(gamepad & 4);
        character.y += !!(gamepad & 2) - !!(gamepad & 1);
              

        tigrClear(screen, tigrRGB(0, 0, 0));
        tigrFillCircle(screen, character.x, character.y, 10, tigrRGB(255, 255, 255));
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}










//
//class StandingState : public State {
//public:
//    void Enter() override {
//        std::cout << "Entering StandingState\n";
//    }
//
//    void Update() override {
//        std::cout << "Updating StandingState\n";
//    }
//
//    void Exit() override {
//        std::cout << "Exiting StandingState\n";
//    }
//};
//
//class DuckingState : public State {
//public:
//    void Enter() override {
//        std::cout << "Entering DuckingState\n";
//    }
//
//    void Update() override {
//        std::cout << "Updating DuckingState\n";
//    }
//
//    void Exit() override {
//        std::cout << "Exiting DuckingState\n";
//    }
//};
//
//class JumpingState : public State {
//public:
//    void Enter() override {
//        std::cout << "Entering JumpingState\n";
//    }
//
//    void Update() override {
//        std::cout << "Updating JumpingState\n";
//    }
//
//    void Exit() override {
//        std::cout << "Exiting JumpingState\n";
//    }
//};
//
//class DivingState : public State {
//public:
//    void Enter() override {
//        std::cout << "Entering DivingState\n";
//    }
//
//    void Update() override {
//        std::cout << "Updating DivingState\n";
//    }
//
//    void Exit() override {
//        std::cout << "Exiting DivingState\n";
//    }
//};
//
//int main() {
//
//    //TAL CUAL LA FOTO DE CLASE PERO SI ESTAS EN DIVING Y PULSAS LA C SE CAMBIA A STANDING
//    FSM fsm;
//
//    fsm.AddState(typeid(StandingState).name(), std::make_shared<StandingState>());
//    fsm.AddState(typeid(DuckingState).name(), std::make_shared<DuckingState>());
//    fsm.AddState(typeid(JumpingState).name(), std::make_shared<JumpingState>());
//    fsm.AddState(typeid(DivingState).name(), std::make_shared<DivingState>());
//
//    fsm.ChangeState(typeid(StandingState).name());  // Comienza en estado Idle
//
//    static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> transitions = {
//           {typeid(StandingState).name(), {{"a", typeid(DuckingState).name()},{"b", typeid(JumpingState).name()}}},
//           {typeid(DuckingState).name(),  {{"a", typeid(StandingState).name()}}},
//           {typeid(JumpingState).name(),  {{"a", typeid(DivingState).name()}}},
//           {typeid(DivingState).name(),  {{"c", typeid(StandingState).name()}}}
//    };
//
//    std::string input;
//
//    while (true) {
//        if (_kbhit()) {
//            input = _getch(); 
//
//            switch (input[0]) {
//            case 'q': 
//                std::cout << "Exiting...\n";
//                return 0;
//            }
//
//            std::string currentState = fsm.GetCurrentState();
//
//            auto stateIt = transitions.find(currentState);
//
//            if (stateIt != transitions.end()) {
//                auto inputIt = stateIt->second.find(input);
//                if (inputIt != stateIt->second.end()) {
//                    fsm.ChangeState(inputIt->second);
//                }
//            }
//            fsm.Update();
//        }
//        
//    }
//    return 0;
//}