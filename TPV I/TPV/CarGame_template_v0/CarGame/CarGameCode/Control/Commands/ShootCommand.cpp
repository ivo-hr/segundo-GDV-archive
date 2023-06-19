#include "ShootCommand.h"

bool ShootCommand::parse(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        if (key == SDLK_s) {
            cout << "Le di a la s" << endl;
            return true;
        }
    }
    return false;
}

void ShootCommand::execute()
{
	game->CarShoots();
}
