#pragma once
#include "Ship.h"
class SmallEnemy :
	public Ship
{
public:
	SmallEnemy();
	virtual ~SmallEnemy();
	void SetSprite(std::shared_ptr<SpriteAnimation> obj);
};

