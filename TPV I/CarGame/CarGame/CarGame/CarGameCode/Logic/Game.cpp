//
// Created by eys on 20/8/21.
//

#include "Game.h"
#include "GameObjectGenerator.h"

Game::Game(string name, int width, int height, int roadLength) {
    this->name = name;
    this->roadLength = roadLength;
    this->width = width;
    this->height = height;
    doExit = false;
    font = new Font("../Images/Monospace.ttf", 12);

    infoBar = new Infobar(this);
}

void Game::startGame() {
    if (gameObjects != nullptr)
        delete gameObjects;
    gameObjects = new GameObjectContainer();

    GoodObject::reset();
    BadObject::reset();

    car = new Car(this);

    road = new Road(this);
    road->setDimension(getWindowWidth(), getWindowHeight());
    road->setLength(roadLength + car->getWidth());
    car->setPosition(car->getWidth(), road->getHeight() / 2);

    GameObjectGenerator::generate(this, 1, 1);

}

string Game::getGameName() {
    return name;
}

Game::~Game() {
    delete car;
    delete font;
    delete textureContainer;
    cout << "[DEBUG] deleting game" << endl;
}

void Game::update(){
    car->update();
}

void Game::draw(){
    car->draw();

    gameObjects->draw();
    drawInfo();
}


void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

int Game::getWindowWidth(){
    return width;
}

int Game::getWindowHeight() {
    return height;
}

SDL_Renderer *Game::getRenderer() {
    return renderer;
}

void Game::setRenderer(SDL_Renderer *_renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if(renderer == nullptr)
        throw string("Renderer is null");

    textureContainer = new TextureContainer(renderer);
}

void Game::renderText(string text, int x, int y, SDL_Color color){
    font->render(renderer, text.c_str(), x, y, color);
}


void Game::renderText(vector<string> texts, int x, int y, SDL_Color color) {
    int inc = font->getSize() * 1.5;
    for (auto s : texts) {
        renderText(s, x, y, BLACK);
        y += inc;
    }
}

void Game::drawInfo()
{

    infoBar->drawInfo();
}

bool Game::doQuit() {
    return isUserExit();
}

Texture *Game::getTexture(TextureName name) {
    return textureContainer->getTexture(name);
}

Point2D<int> Game::getOrigin() {
    return {int(-(car->getX() - car->getWidth())), 0};
}

void Game::setVerticalMove(int dir)
{   
    car->setVerticalMove(dir);
}
bool Game::addObject(GameObject* object) {
    if (gameObjects->hasCollision(object))
        return false;
    gameObjects->add(object);
    return true;
}

bool Game::isRebased(GameObject* object)
{
    // TODO
    return false;
}