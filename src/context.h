#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <memory>
#include <vector>

#include "state.h"

class StateContext {
private:
    std::unique_ptr<State> currentState;
    int blockLevel = 0;
    std::vector<std::string> vec;
    std::string programName;
    int number;

public:
    StateContext(std::string name, int num);

    void SetState(std::unique_ptr<State> newState);
    void ProcessLine(const std::string &line);
    void ProcessEnd();

    void IncrementBlock();
    void DecrementBlock();
    int GetBlockLevel() const;
    void AddToVector(const std::string &line);
    void PrintVector();
    int GetVectorSize() const;
    int GetN() const;

    ~StateContext() = default;
};

#endif 