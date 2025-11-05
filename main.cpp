#include <iostream>
#include <vector>
#include <memory>

class StateContext;

class State {
    std::string name;
public:
    virtual ~State() = default;
    State(const std::string& name) : name(name) {}
    virtual void ProcessLine(const std::string &line, StateContext*) = 0;
};

class StateContext {
private:
    std::unique_ptr<State> currentState;
    int blockLevel = 0;
    std::vector<std::string> vec;
    std::string programName;

public:
    StateContext(std::string name) ;

    void SetState(std::unique_ptr<State> newState) {
        currentState = std::move(newState);
    }

    void processLine(const std::string &line) {
        if(currentState) {
            currentState->ProcessLine(line, this);
        }
    }

    void IncrementBlock() {blockLevel++;}
    void DecrementBlock() {blockLevel--;}
    int GetBlockLevel() const { return blockLevel; }
    void AddToVector(const std::string& line) { vec.push_back(line); }
    void PrintVector() {
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

    ~StateContext() = default;
};

class NormalState : public State {
public:
    NormalState() : State("NormalState") {}  
    void ProcessLine(const std::string &line, StateContext *context) override;
};

class BlockState : public State {
public: 
    BlockState() : State("BlockState") {}  
    void ProcessLine(const std::string &line, StateContext *context) override;
};


void NormalState::ProcessLine(const std::string &line, StateContext *context) {
    if (line == "{") {
        if (context->GetBlockLevel() == 0) {
            context->PrintVector();
        }
        context->IncrementBlock();
        context->SetState(std::make_unique<BlockState>());
    }
    else if (line == "}") {
    }
    else {
        context->AddToVector(line);
    }
}


void BlockState::ProcessLine(const std::string &line, StateContext *context) {
    if (line == "{") {
        context->IncrementBlock();
    }
    else if (line == "}") {
        context->DecrementBlock();
        if (context->GetBlockLevel() == 0) {
            context->SetState(std::make_unique<NormalState>());
            context->PrintVector();
        }
    }
    else {
        context->AddToVector(line);
    }
}

StateContext::StateContext(std::string name) {
    programName = name;
    currentState = std::make_unique<NormalState>();
}



int main(int argc, char** argv) {
    std::string programName = argv[0];
    programName = programName.substr(2);

    StateContext sc(programName);
    std::string line;

    while (std::cin >> line) {
        sc.processLine(line);
    }
    return 0;
}