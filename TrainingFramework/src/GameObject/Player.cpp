#include "Player.h"
#include "ResourceManagers.h"

extern GLint screenWidth;
extern GLint screenHeight;

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	:Ship( model,  shader, texture, numFrames, frameTime)
{
	m_iHp = 100;
	for (int i = 0; i < m_iNumBullet; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("1laser2");
		auto bullet = std::make_shared<Bullet>(model, shader, texture, 2, 0.2f);
		bullet->SetSize(20, 20);
		bullet->Set2DPosition(Get2DPosition());
		bullet->SetSpeed(1000);
		bullet->SetDame(5);
		m_listBullet.push_back(bullet);
	}
}

Player::~Player()
{
}

void Player::Move(int key)
{
	if ((key == 38 || key == 87)&&Get2DPosition().y > 0)
	{
		Set2DPosition(Get2DPosition().x, Get2DPosition().y - 10);//up
	}
	if ((key == 40 || key == 83)&& Get2DPosition().y < screenHeight)
	{
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + 10);//donw
	}
	if ((key == 37 || key == 65)&& Get2DPosition().x > 0)
	{
		Set2DPosition(Get2DPosition().x - 10, Get2DPosition().y);//left
	}
	if ((key == 39 || key == 68)&& Get2DPosition().x < screenWidth )
	{
		Set2DPosition(Get2DPosition().x + 10, Get2DPosition().y);//right
	}
}

bool Player::IsCollide(std::list<std::shared_ptr<Bullet>>	m_listBullet, std::list<std::shared_ptr<Ship>>	m_listShip)
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


