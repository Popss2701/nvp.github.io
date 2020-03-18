#pragma once
#include "BaseObject.h"
enum ShipTypes
{
	INVALID = 0,
	Small,
	Medium,
	Big,
	Boss,
};

class Ship :
	public BaseObject
{
public:
	Ship();
	virtual ~Ship();
	void PopList();
	void Move();
	void Shoot();
	void Explode();
	void SetHp(int hp) { m_iHp = hp; }
	int GetHp() { return m_iHp; }
	void SetIsActive(){}
	virtual void SetSprite() = 0;
	virtual bool IsCollide() = 0;

private:
	std::list<std::shared_ptr<Ship>>	m_listShip;
	int m_iHp;
	bool m_bIsActive;

};

