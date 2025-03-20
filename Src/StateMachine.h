#include <iostream>
#include <memory>
#include <unordered_map>

class State {
public:
    virtual ~State() = default;
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
};

class FSM {
public:
    void AddState(const std::string& name, std::shared_ptr<State> state) {
        states[name] = std::move(state);
    }

    void ChangeState(const std::string& name) {
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

    void Update() {
        if (currentState) {
            currentState->Update();
        }
    }

    std::string GetCurrentState() const {
        return currentState ? typeid(*currentState).name() : "NONE";
    }

private:
    std::unordered_map<std::string, std::shared_ptr<State>> states;
    std::shared_ptr<State> currentState;
};