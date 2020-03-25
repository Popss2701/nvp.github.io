#include "SmallEnemy.h"

extern int screenHeight;
extern int screenWidth;

SmallEnemy::SmallEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	:Ship(model, shader, texture, numFrames, frameTime)
{
	SetHp(5);
}

SmallEnemy::~SmallEnemy()
{
}

void SmallEnemy::Move(GLfloat deltatime)
{
	float deltaMove = m_fSpeed * deltatime;
	m_fTimeChangeDirection += deltatime;
	int change = (GetObjectID()+int(m_fTimeChangeDirection)) % 5;
	switch (change)
	{
	case 0:
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + deltaMove);
		break;
	case 1:
		Set2DPosition(Get2DPosition().x - deltaMove, Get2DPosition().y);
		break;
	case 2:
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + deltaMove);
		break;
	case 3:
		Set2DPosition(Get2DPosition().x + deltaMove, Get2DPosition().y);
		break;
	case 4:
		m_fTimeChangeDirection = 0;
		break;
	}
	if (Get2DPosition().y > screenHeight)
	{	
		Set2DPosition(rand() % screenWidth, -100 /*int(obj->Get2DSize().y)*/);
		SetDead();
	}
}

void SmallEnemy::IncreaseSpeed()
{

	m_fSpeed += 20;
}

