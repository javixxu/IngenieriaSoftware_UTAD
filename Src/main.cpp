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
};

class MoveCommand :public Command {
    Character* character;
    unsigned gamepad;
public:
    MoveCommand(Character* cha, unsigned game) :character(cha), gamepad(game) {
    }
    void execute() override {
        character->x += !!(gamepad & 8) - !!(gamepad & 4);
        character->y += !!(gamepad & 2) - !!(gamepad & 1);
    }
    void undo() override {
        character->x -= (!!(gamepad & 8) - !!(gamepad & 4));
        character->y -= (!!(gamepad & 2) - !!(gamepad & 1));
    };
};

int main() {
    Tigr* screen = tigrWindow(800, 600, "Command Pattern - Character Movement", 0);
    Character character;
    std::vector<unsigned> commands;
    Invoker invoker;

    bool is_recording = true;
    int frame = 0;
    while (!tigrClosed(screen)) {

        if (tigrKeyDown(screen, 'R')) {
            is_recording = !is_recording;
            frame = 0;
        }

        unsigned gamepad = 0;

        // recording
        if (is_recording) {

            gamepad |= tigrKeyHeld(screen, TK_UP) * 1;
            gamepad |= tigrKeyHeld(screen, TK_DOWN) * 2;
            gamepad |= tigrKeyHeld(screen, TK_LEFT) * 4;
            gamepad |= tigrKeyHeld(screen, TK_RIGHT) * 8;
            commands.push_back(gamepad);
            invoker.AddCommand(new MoveCommand(&character, gamepad));
        }
        else {
            invoker.ExecuteCommand();
            //gamepad = commands[frame++ % commands.size()];
        }

        //character.x += !!(gamepad & 8) - !!(gamepad & 4);
        //character.y += !!(gamepad & 2) - !!(gamepad & 1);


        tigrClear(screen, tigrRGB(0, 0, 0));
        tigrFillCircle(screen, character.x, character.y, 10, tigrRGB(255, 255, 255));
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}