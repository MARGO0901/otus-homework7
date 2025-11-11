#ifndef STATE_H
#define STATE_H

#include <iostream>

class StateContext;

class State {
    std::string name;

public:
    virtual ~State() = default;
    State(const std::string &name) : name(name) {}
    virtual void ProcessLine(const std::string &line, StateContext *) = 0;
    virtual void ProcessEnd(StateContext *) = 0;
};

class NormalState : public State {
public:
    NormalState() : State("NormalState") {}
    void ProcessLine(const std::string &line, StateContext *context) override;
    void ProcessEnd(StateContext *) override;
};

class BlockState : public State {
public:
    BlockState() : State("BlockState") {}
    void ProcessLine(const std::string &line, StateContext *context) override;
    void ProcessEnd(StateContext *) override;
};

#endif 