#pragma once
#include <iostream>
#include <vector>

class Command {
public:
	virtual void execute() = 0;
    virtual void undo() = 0;
};

class Invoker {
	std::vector<Command*> history;
public:
	void AddCommand(Command* command) {
		history.push_back(command);
		command->execute();
	};
	void ExecuteCommand(int command = -1) {
        // Si el comando no se especifica, usamos el ultimo
        int index = (command == -1) ? history.size() - 1 : command;
        command = history.size() - command;

        // Verificar que el indice es valido
        if (index >= 0 && index < history.size()) {
            Command* CMP = history[index];

            // Ejecutar el comando
            CMP->undo();

            // Eliminar el comando de la lista despues de ejecutarlo
            history.erase(history.begin() + index);
            delete CMP;
        }
	}
    void deleteHistory() {
        if (history.empty())return;
       delete history.back();
       history.pop_back();
    }
    ~Invoker() {
        deleteHistory();
    }
};