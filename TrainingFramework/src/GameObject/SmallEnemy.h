#pragma once
#include "Ship.h"

class SmallEnemy :
	public Ship
{
public:
	SmallEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime, int id);
	virtual ~SmallEnemy();
	void Move(GLint deltatime);
	void SetSpeed();
	void Hitted(int dame);
private:
	float m_fSpeed = 1;
};

