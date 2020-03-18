#pragma once
#include "SpriteAnimation.h"
enum ShipTypes
{
	INVALID = 0,
	Small,
	Medium,
	Big,
	Boss,
};

class Ship :
	public SpriteAnimation
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
	//virtual bool IsCollide() = 0;
protected:
	int m_iHp;
	bool m_bIsActive;
private:
	std::list<std::shared_ptr<Ship>>	m_listShip;
	

};

