#include "state.h"

#include <memory>

#include "context.h"

void NormalState::ProcessLine(const std::string &line, StateContext *context) {
    if (line == "{") {
        if (context->GetBlockLevel() == 0) {
        context->PrintVector();
        }
        context->IncrementBlock();
        context->SetState(std::make_unique<BlockState>());
    } else if (line == "}") {
    } else {
        context->AddToVector(line);
        if (context->GetVectorSize() >= context->GetN()) {
            context->PrintVector();
        }
    }
}

void NormalState::ProcessEnd(StateContext *context) {
    context->PrintVector();
}

void BlockState::ProcessLine(const std::string &line, StateContext *context) {
    if (line == "{") {
        context->IncrementBlock();
    } else if (line == "}") {
        context->DecrementBlock();
        if (context->GetBlockLevel() == 0) {
        context->SetState(std::make_unique<NormalState>());
        context->PrintVector();
        }
    } else {
        context->AddToVector(line);
    }
}

void BlockState::ProcessEnd(StateContext *context) {
    return;
}