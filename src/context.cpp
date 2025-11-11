#include "context.h"

StateContext::StateContext(std::string name, int num) : programName(std::move(name)), number(num){
    currentState = std::make_unique<NormalState>();
}

void StateContext::SetState(std::unique_ptr<State> newState) {
    currentState = std::move(newState);
}

void StateContext::ProcessLine(const std::string &line) {
    if(currentState) {
        currentState->ProcessLine(line, this);
    }
}

void StateContext::ProcessEnd() {
    if(currentState) {
        currentState->ProcessEnd(this);
    }
}

void StateContext::IncrementBlock() {
    blockLevel++;
}

void StateContext::DecrementBlock() {
    blockLevel--;
}

int StateContext::GetBlockLevel() const { 
    return blockLevel;
}

void StateContext::AddToVector(const std::string &line) {
    vec.push_back(line);
}

void StateContext::PrintVector() {
    if (!vec.empty()) {
        std::cout << programName << ": ";

        for (auto i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
        }
        std::cout << std::endl;
        vec.clear();
    }
}

int StateContext::GetVectorSize() const { 
    return vec.size(); 
}

int StateContext::GetN() const {
    return number;
}
