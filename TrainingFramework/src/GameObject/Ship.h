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
	//Ship();
	Ship(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	virtual ~Ship();
	void Shoot();
	void Explode();
	void SetHp(int hp) { m_iHp = hp; }
	int GetHp() { return m_iHp; }
	std::list<std::shared_ptr<Ship>>	m_listShip;
protected:
	int m_iHp;
	bool m_bIsActive;
private:
	
	

};

