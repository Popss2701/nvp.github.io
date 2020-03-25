#pragma once
#include "Ship.h"
#include "Bullet.h"

class Boss :
	public Ship
{
public:
	Boss(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	virtual ~Boss();
	void Move(GLfloat deltatime);
	int GetNumBullet() { return m_iNumBullet; }
	void IncreaseSpeed();
private:
	float m_fSpeed = 50;
	int m_iNumBullet = 9;
};

