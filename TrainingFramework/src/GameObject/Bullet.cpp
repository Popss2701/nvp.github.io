#include "Bullet.h"



Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime, int dame)
	:SpriteAnimation(model, shader, texture, numFrames, frameTime)
{
	m_iDamege = dame;
}

Bullet::~Bullet()
{
}

void Bullet::Move()
{
	this->Set2DPosition(Get2DPosition().x, Get2DPosition().y + 10);
}

bool Bullet::IsCollide()
{
	return true;
}

void Bullet::SetDame(int add)
{
	m_iDamege += add;
}
