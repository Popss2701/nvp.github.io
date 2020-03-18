#pragma once
#include "BaseObject.h"

enum LaserType {
	Invalid = 0,
	Laser1,
	Laser2,
};
class Bullet :
	public BaseObject
{
public:
	Bullet();
	virtual ~Bullet();
	void PopList();
	bool IsCollide();
private:
	int damege;
	std::list<std::shared_ptr<Bullet>>	m_listBullet;

};

