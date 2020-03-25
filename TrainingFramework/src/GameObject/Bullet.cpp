#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	:SpriteAnimation(model, shader, texture, numFrames, frameTime)
{
}

Bullet::~Bullet()
{
}

void Bullet::Move(GLfloat deltatime, ShipTypes ship)
{
	switch (ship)
	{
	case PLAYER:
		Set2DPosition(Get2DPosition().x, Get2DPosition().y - m_iSpeed * deltatime);
		break;
	case MEDIUM:
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + m_iSpeed * deltatime);
		break;
	case BIG:
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + m_iSpeed * deltatime);
		break;
	default:
		
		break;
	}
}

void Bullet::IncreaseDame(int add)
{
	m_iDamege += add;
}

void Bullet::SetDame(int dame)
{
	m_iDamege = dame;
}

void Bullet::SetActive()
{
	m_IsActive = true;
}

void Bullet::SetDeactive()
{
	m_IsActive = false;
}

void Bullet::SetSpeed(int add)
{
	m_iSpeed = add;
}