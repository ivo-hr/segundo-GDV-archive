#pragma once
#include <string>

class Game;

class State {

protected:

	Game* game;

public:

	State(Game* game) : game(game) {};

	virtual ~State() {};

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void next() = 0;
	virtual std::string GetStateName() = 0;
};
