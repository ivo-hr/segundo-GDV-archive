#include "GameObjectGenerator.h"

Point2D<int> GameObjectGenerator::generateRandomPosition(Game* game, GameObject* o)
{
	return Point2D<int> (rand() % (game->getRoadLenght() - o->getWidth()) + o->getWidth() / 2,
		rand() % (game->getWindowHeight() - o->getHeight() / 2 - 22) + (o->getHeight() / 2 + 22));
}

void GameObjectGenerator::addInRandomPosition(Game* game, GameObject* o)
{

	o->setDimension(game->getTexture(rockTexture)->getW(), game->getTexture(rockTexture)->getH());
		//Pregunta como coño hacer esto para todos los objetos no simplemente llamando a rock texture

	Vector2D<int> punto = generateRandomPosition(game, o);

	o->setPosition(punto.getX(), punto.getY());

	game->getContainer()->add(o);
}