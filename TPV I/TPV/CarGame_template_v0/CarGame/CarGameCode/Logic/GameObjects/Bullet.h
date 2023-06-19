#pragma once

#include "GameObject.h"
#include "../../Utils/Vector2D.h"
#include "../../View/Box.h"
#include "../../View/Texture.h"

class Bullet : public GameObject
{
	const int SPEED = 15;

public:
	Bullet(Game* game);
	~Bullet();

	void draw() override;

	void update() override;
};

