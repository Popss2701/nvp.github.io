#pragma once
#include "Ship.h"
#include "Bullet.h"


class Player :
	public Ship
{
public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	virtual ~Player();
	bool IsCollide(std::list<std::shared_ptr<Bullet>>	m_listBullet, std::list<std::shared_ptr<Ship>>	m_listShip);
	int GetNumBullet() { return m_iNumBullet; }
	void Move(int key);
	void Heal();
private:
	int m_iNumBullet = 10;
};

