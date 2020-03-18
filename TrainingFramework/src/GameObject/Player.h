#pragma once
#include "Ship.h"

class Player :
	public Ship
{
public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	Player();
	virtual ~Player();
	void Move(int key);
private:
	


};

