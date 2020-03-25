#include "MediumEnemy.h"
#include "ResourceManagers.h"

extern int screenHeight;
extern int screenWidth;

MediumEnemy::MediumEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	:Ship(model, shader, texture, numFrames, frameTime)
{
	SetHp(15);
	for (int i = 0; i < m_iNumBullet; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("1laser2");
		auto bullet = std::make_shared<Bullet>(model, shader, texture, 2, 0.2f);
		bullet->SetSize(30, 30);
		bullet->Set2DPosition(Get2DPosition());
		bullet->SetSpeed(100);
		bullet->SetDame(10);
		m_listBullet.push_back(bullet);
	}
}

MediumEnemy::~MediumEnemy()
{
}

void MediumEnemy::Move(GLfloat deltatime)
{
	float deltaMove = m_fSpeed * deltatime;
	Set2DPosition(Get2DPosition().x, Get2DPosition().y + deltaMove);
	if (Get2DPosition().y > screenHeight)
	{
		Set2DPosition(rand() % screenWidth, -100 /*int(obj->Get2DSize().y)*/);
		SetDead();
	}
}

void MediumEnemy::IncreaseSpeed()
{
	m_fSpeed += 20;
}

