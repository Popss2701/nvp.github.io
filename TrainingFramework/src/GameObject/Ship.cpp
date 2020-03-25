#include "Ship.h"
#include "ResourceManagers.h"

Ship::Ship(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	:SpriteAnimation(model,  shader, texture, numFrames, frameTime)
{
}

Ship::~Ship()
{
}

void Ship::Respawn(GLfloat deltatime)
{
	if (!m_IsActive)
	{
		m_fTimeRespawn += deltatime;
		if (m_fTimeRespawn >= 1.5)
		{
			m_IsActive = true;
			m_fTimeRespawn = 0;
		}
	}
}

void Ship::SetDead()
{
	m_IsActive = false;
}

void Ship::SetActive()
{
	m_IsActive = true;
}

void Ship::Hitted(int dame)
	{
		m_iHp -= dame;
		if (m_iHp <= 0)
		{
			//dead
			m_iHp = 0;
			m_IsActive = false;
		}
	}

void Ship::Shoot(GLfloat deltaTime, ShipTypes ship, int iNumShot)
{
	float timePerShop;
	m_fTimeShoot += deltaTime;
	switch (ship)
	{
	case INVALID:
		break;
	case PLAYER:
		timePerShop = 0.2;
		if (m_fTimeShoot >= timePerShop)
		{
			m_listBullet[m_iBulletTurn]->SetActive();
			m_iBulletTurn = (m_iBulletTurn + 1) % iNumShot;
			m_fTimeShoot = 0;
			ResourceManagers::GetInstance()->PlaySound("laser");
		}
		break;
	case SMALL:
		break;
	case MEDIUM:
		timePerShop = 2;
		if (m_fTimeShoot >= timePerShop)
		{
			m_listBullet[m_iBulletTurn]->SetActive();
			m_iBulletTurn = (m_iBulletTurn + 1) % iNumShot;
			m_fTimeShoot = 0;
		}
		break;
	case BIG:
		timePerShop = 2;
		if (m_fTimeShoot >= timePerShop)
		{
			m_listBullet[m_iBulletTurn]->SetActive();
			m_iBulletTurn = (m_iBulletTurn + 1) % iNumShot;
			m_fTimeShoot = 0;
		}
		break;
	case BOSS:
		timePerShop = 2;
		if (m_fTimeShoot >= timePerShop)
		{
			m_listBullet[m_iBulletTurn]->SetActive();
			m_iBulletTurn = (m_iBulletTurn + 1) % iNumShot;
			m_fTimeShoot = 0;
		}
		break;
	default:
		break;
	}

	for (auto obj : m_listBullet)
	{
		if (obj->GetIsActive())
		{
			obj->Update(deltaTime);
			obj->Move(deltaTime, ship);
		}
		else
		{
			obj->Set2DPosition(Get2DPosition());
		}
		if (obj->Get2DPosition().y <= 0)
		{
			obj->SetDeactive();
			obj->Set2DPosition(Get2DPosition());
		}
	}
}

void Ship::DameUp(int add)
{
	for (auto obj : m_listBullet)
	{
		obj->IncreaseDame(add);
	}
}