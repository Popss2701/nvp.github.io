#pragma once
#include "Ship.h"
#include "Bullet.h"

class MediumEnemy :
	public Ship
{
public:
	MediumEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	virtual ~MediumEnemy();
	int GetNumBullet() { return m_iNumBullet; }
	void Move(GLfloat deltatime);
	void IncreaseSpeed();
private:
	float m_fSpeed = 50;
	int m_iNumBullet = 5;
};

