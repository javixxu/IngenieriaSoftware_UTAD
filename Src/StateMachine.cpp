#include "StateMachine.h"

void FSM::AddState(const std::string& name, std::shared_ptr<State> state) {
    states[name] = std::move(state);
}

void FSM::ChangeState(const std::string& name) {
    if (states.find(name) != states.end()) {
        if (currentState) {
            currentState->Exit();
        }
        currentState = states[name];
        currentState->Enter();
    }
    else {
        std::cerr << "State Not Found: " << name << std::endl;
    }
}

void FSM::Update() {
    if (currentState) {
        currentState->Update();
    }
}

std::string FSM::GetCurrentState() const {
    return currentState ? typeid(*currentState).name() : "NONE";
}