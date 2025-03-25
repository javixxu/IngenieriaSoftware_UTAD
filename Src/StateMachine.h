#pragma once
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
    void AddState(const std::string& name, std::shared_ptr<State> state);

    void ChangeState(const std::string& name);

    void Update();

    std::string GetCurrentState() const;

private:
    std::unordered_map<std::string, std::shared_ptr<State>> states;
    std::shared_ptr<State> currentState;
};