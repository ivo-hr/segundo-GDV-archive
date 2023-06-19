#pragma once
#include "Command.h"

class NextStateCommand : public Command {

public:
    const string INFO_STRING = "[ESC] to quit";

    NextStateCommand() {
        info_string = INFO_STRING;
    };
    ~NextStateCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};

