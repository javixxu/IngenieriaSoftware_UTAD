#pragma once
#include <iostream>
#include <vector>

class Command {
public:
	virtual void execute() = 0;
};

class Invoker {
	std::vector<Command*> Commands;
public:
	void AddCommand(Command* command) {
		Commands.push_back(command);
	};
	void ExecuteCommand(int command = -1) {
		Commands[command == -1 ? Commands.size() - 1 : command]->execute();
	}
};