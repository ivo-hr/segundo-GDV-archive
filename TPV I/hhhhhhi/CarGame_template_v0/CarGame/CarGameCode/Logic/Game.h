//
// Created by eys on 20/8/21.
//

#ifndef CARGAME_GAME_H
#define CARGAME_GAME_H

#include <iostream>
#include <string>
#include <vector>

#include "../View/TextureContainer.h"
#include "../View/Texture.h"
#include "../View/Box.h"
#include "../View/Font.h"

#include "GameObjectGenerator.h"
#include "GameObjectContainer.h"
#include "GameObjects/Car.h"
#include "GameObjects/FinLine.h"


using namespace std;

class Game {


private:
    string name;
    bool doExit;
    int roadLength;
    int width, height;
    Car* car = nullptr;
    FinLine* goal = nullptr;
    int numRocks;

    TextureContainer* textureContainer;
    GameObjectContainer* container;
    SDL_Renderer* renderer = nullptr;
    Font* font;
public:
    const unsigned int CAR_WIDTH = 100;
    const unsigned int CAR_HEIGHT = 50;
    const unsigned int ROCK_WIDTH = 50; //
    const unsigned int ROCK_HEIGHT = 50;
    const unsigned int GOAL_WIDTH = 50; //

    Game(string name, int width, int height, int roadLength);
    ~Game();

    
    void startGame();
    void update();
    void NewRocks(int rocks);
    void DeleteRock();
    void draw();

    void MoveCarX(float movX);
    void MoveCarY(int movY);
    void setUserExit();
    bool isUserExit();
    bool doQuit();
    vector<Collider*> GetCollisions(GameObject* o);
    bool HasLost();

    int getWindowWidth();
    int getWindowHeight();
    int getRoadLenght();
    GameObjectContainer* getContainer();

    Point2D<int> getOrigin();

    string getGameName();

    void GameMenu();
    bool GameEnd();

    void setRenderer(SDL_Renderer* renderer);
    void loadTextures();
    Texture* getTexture(TextureName name);
    SDL_Renderer* getRenderer();
    void renderText(string text, int x, int y, SDL_Color color = { 0,0,0 });
    Font* GetFont();

    void drawInfo();

};


#endif //CARGAME_GAME_H
