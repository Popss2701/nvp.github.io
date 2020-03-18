#include "Player.h"
#include"SpriteAnimation.h"


Player::Player()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("1ship");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 2, 0.1f);
	obj->Set2DPosition(50, 100);
	obj->SetSize(52, 52);
}


Player::~Player()
{
}

void Player::Move(int key)
{
	if (key == 38 || key == 87)
	{
		m_VecPos.y -= 10;
	}

	if (key == 40 || key == 83)
	{
		m_VecPos.y += 10;
	}

	if (key == 37 || key == 65)
	{
		m_VecPos.x -= 10;
	}

	if (key == 39 || key == 68)
	{
		m_VecPos.x += 10;
	}
}