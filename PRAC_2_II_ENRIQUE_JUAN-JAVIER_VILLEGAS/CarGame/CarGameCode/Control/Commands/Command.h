#ifndef CARGAME_COMMAND_H
#define CARGAME_COMMAND_H

// TODO add includes
#include <string>
#include "../../Logic/Game.h"

class Command {
protected:
    int cost = 0;
    string info_string;
    Game* game;
public:

    Command(){};
    virtual ~Command()=default;
    virtual bool parse(SDL_Event &event)=0;
    virtual void execute()=0;
    void bind(Game *game){
        this->game = game;
        game->appendHelpInfo(info_string);
    }
    string GetInfoString() { return info_string; }
};


#endif //CARGAME_COMMAND_H
