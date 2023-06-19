//
// Created by eys on 20/8/21.
//

#include "Game.h"
#include <stdlib.h>
#include <time.h>

Game::Game(string name, int width, int height, int roadLength) {
    this->name = name;
    this->roadLength = roadLength;
    this->width = width;
    this->height = height;
    doExit = false;
    font = new Font("../Images/Monospace.ttf", 12);

    numRocks = 15;
}

void Game::startGame() {
    car = new Car(this);
    car->setDimension(CAR_WIDTH, CAR_HEIGHT);
    car->setPosition(car->getWidth(), height / 2.0);

    srand(time(NULL));

    NewRocks(numRocks);
    
    goal = new FinLine(this);
    goal->setDimension(GOAL_WIDTH, getWindowHeight());
    goal->setPosition(roadLength, height / 2.0);
}

void Game::GameMenu(){
    string title = "SandoKart";

    renderText(title, getWindowWidth()/2, getWindowHeight()/2);
    
    string start = "Press 'Space' to start";
    renderText(start, getWindowWidth()/2 - 10, getWindowHeight()/2 + font->getSize());

    string exit = "Press 'Esc' to quit";
    renderText(exit, getWindowWidth() / 2 - 10, getWindowHeight() / 2 + font->getSize() * 2);
}

string Game::getGameName() {
    return name;
}

Game::~Game() {
    cout << "[DEBUG] deleting game" << endl;
}

void Game::update() {
    car->update();

    //cout << ranSp << endl;

    //CheckCollision();

    DeleteRock();
}

vector<Collider*> Game::GetCollisions(GameObject* o) {

    return container->getCollisions(o);

}

bool Game::HasLost(){
    return car->Power() <= 0;
}
void Game::NewRocks(int rocks) {
    
    GameObjectGenerator::generate(this, rocks);

}

void Game::DeleteRock() {

    container->removeDead();

}

void Game::draw() {

    container->draw();
    car->draw();
    goal->draw();
    drawInfo();
}

void Game::drawInfo() {
    int x = font->getSize() / 2;
    int y = font->getSize() / 2;

    SDL_Rect rect = { 0, 0, getWindowWidth(),
                     int(font->getSize() * 1.8) };
    Box(rect, BLACK).render(renderer);

    string s = "Pos: " + to_string(int(car->getX())) + " "
        + to_string(int(car->getY())) 

        + "  " + to_string(int(car->Power())) 
        + "  " + to_string(car->getSpeed())
        + "  " + to_string((int)(roadLength - (car->getX() + CAR_WIDTH / 2)));

    renderText(s, x, y);
}
void Game::MoveCarX(float movX) {
    car->MoveX(movX);
}
void Game::MoveCarY(int movY) {
    car->MoveY(movY);
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

int Game::getWindowWidth() {
    return width;
}

int Game::getWindowHeight() {
    return height;
}

int Game::getRoadLenght() {
    return roadLength;
}

GameObjectContainer* Game::getContainer() {
    return container;
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer = new TextureContainer(renderer);
}

void Game::renderText(string text, int x, int y, SDL_Color color) {
    font->render(renderer, text.c_str(), x, y, color);
}

bool Game::doQuit() {
    return isUserExit();
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer->getTexture(name);
}

Font* Game::GetFont() {
    return font;
}

bool Game::GameEnd() {
    return (SDL_HasIntersection(&car->getCollider(), &goal->getCollider()) || car->Power() < 1);
}

Point2D<int> Game::getOrigin() {
    return { int(-(car->getX() - car->getWidth())), 0 };
}