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
private:
    std::unordered_map<std::string, std::shared_ptr<State>> states;
    std::unordered_map< std::shared_ptr<State>, std::shared_ptr<State>> transitions;
    std::shared_ptr<State> currentState;
    std::string currentStateName;

public:
    void AddState(const std::string& name, std::shared_ptr<State> state) {
        states[name] = std::move(state);
    }
    void AddTransitions(const std::string& from, std::shared_ptr<State> to) {
        transitions[states[from]] = transitions[states[to]];
    }

    void ChangeState(const std::string& name) {
        auto it = states.find(name);
        if (it != states.end()) {
            if (currentState) {
                currentState->Exit();
            }
            currentState = it->second;
            currentStateName = name;
            currentState->Enter();
        }
        else {
            std::cerr << "Invalid state transition from " << currentStateName << " to " << name << "!\n";
        }
    }

    void Update() {
        if (currentState) {
            currentState->Update();
        }
    }

    const std::string& GetCurrentStateName() const {
        return currentStateName;
    }

    std::shared_ptr<State> GetCurrentState() const {
        return currentState;
    }
};