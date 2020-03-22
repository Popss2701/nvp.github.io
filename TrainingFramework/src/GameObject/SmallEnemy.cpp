#include "SmallEnemy.h"

SmallEnemy::SmallEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime, int id)
	:Ship(model, shader, texture, numFrames, frameTime)
{
	//SetObjectID(id);
}

SmallEnemy::~SmallEnemy()
{
}

void SmallEnemy::Move(GLint deltatime)
{
	this->Set2DPosition(Get2DPosition().x, Get2DPosition().y + m_fSpeed);
}

void SmallEnemy::SetSpeed()
{
	m_fSpeed += 2;
}

void SmallEnemy::Hitted(int dame)
{
	m_iHp -= dame;
	if (m_iHp <= 0)
	{
		//dead
	}
}