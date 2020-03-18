#pragma once
#include "BaseObject.h"

class Player :
	public BaseObject
{
public:
	Player();
	virtual ~Player();
	void Move(int key);
private:
	int m_score;
	int m_hp =100;
	Vector2 m_VecPos;

};

