#include "Player.h"

extern GLint screenWidth;
extern GLint screenHeight;


Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	:Ship( model,  shader, texture, numFrames, frameTime)
{
	m_iHp = 100;
}

Player::~Player()
{
}

void Player::Move(int key)
{
	if ((key == 38 || key == 87)&&Get2DPosition().y > Get2DSize().x / 2)
	{
		Set2DPosition(Get2DPosition().x, Get2DPosition().y - 10);//right
	}
	if ((key == 40 || key == 83)&& Get2DPosition().y < screenHeight - Get2DSize().x / 2)
	{
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + 10);//left
	}
	if ((key == 37 || key == 65)&& Get2DPosition().x > Get2DSize().y / 2)
	{
		Set2DPosition(Get2DPosition().x - 10, Get2DPosition().y);//up
	}
	if ((key == 39 || key == 68)&& Get2DPosition().x < screenWidth - Get2DSize().y / 2)
	{
		Set2DPosition(Get2DPosition().x + 10, Get2DPosition().y);//down
	}
}

bool Player::Collide(std::list<std::shared_ptr<Bullet>>	m_listBullet, std::list<std::shared_ptr<Ship>>	m_listShip)
{
	for (auto bullet : m_listBullet)
	{

	}
	return true;
}

void Player::Heal()
{
	if (m_iHp < 75)
	{
		m_iHp += 25;
	}
	else {
		m_iHp = 100;
	}
}
void DameUp()
{

}
