#pragma once
#include "SpriteAnimation.h"

enum LaserType {
	Invalid = 0,
	Laser1,
	Laser2,
};
class Bullet :
	public SpriteAnimation
{
public:
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime, int dame);
	virtual ~Bullet();
	bool IsCollide();
	void SetDame(int add);
	int GetDame() { return m_iDamege; };
	void Move();
private:
	int m_iDamege;

};

