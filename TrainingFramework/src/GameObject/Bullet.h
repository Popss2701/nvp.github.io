#pragma once
#include "SpriteAnimation.h"

enum ShipTypes
{
	INVALID = 0,
	PLAYER,
	SMALL,
	MEDIUM,
	BIG,
	BOSS,
};
class Bullet :
	public SpriteAnimation
{
public:
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	virtual ~Bullet();
	void IncreaseDame(int add);
	void SetSpeed(int add);
	void SetDame(int dame);
	int GetDame() { return m_iDamege; };
	void Move(GLfloat deltatime, ShipTypes ship);
	void SetActive();
	void SetDeactive();
	bool GetIsActive() { return m_IsActive; }
private:
	int m_iDamege = 5;
	bool m_IsActive = false;
	float m_fTimeRespawn = 0;
	int m_iSpeed;
};

