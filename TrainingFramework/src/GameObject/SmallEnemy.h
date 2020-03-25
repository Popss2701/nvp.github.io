#pragma once
#include "Ship.h"

class SmallEnemy :
	public Ship
{
public:
	SmallEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	virtual ~SmallEnemy();
	void Move(GLfloat deltatime);
	void IncreaseSpeed();
private:
	float m_fSpeed = 80;
	float m_fTimeChangeDirection = 0;
};

