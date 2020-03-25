#pragma once
#include "SpriteAnimation.h"
#include "Bullet.h"

class Ship :
	public SpriteAnimation
{
public:
	//Ship();
	Ship(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	virtual ~Ship();
	void Shoot(GLfloat deltaTime, ShipTypes ship, int iNumShot);
	void SetHp(int hp) { m_iHp = hp; }
	int GetHp() { return m_iHp; }
	void Respawn(GLfloat deltatime);
	void SetDead();
	void SetActive();
	bool GetIsActive() { return m_IsActive; }
	void Hitted(int dame);
	void DameUp(int add);
	std::vector < std::shared_ptr<Bullet>> GetListBullet() { return m_listBullet; };
protected:
	int m_iHp;
	float m_fTimeRespawn = 0;
	bool m_IsActive = false;
	std::vector < std::shared_ptr<Bullet>> m_listBullet;
	float m_fTimeShoot = 0;
	int m_iBulletTurn = 0;
private:
	
	

};

