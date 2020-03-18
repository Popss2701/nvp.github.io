#include "Player.h"

extern GLint screenWidth;
extern GLint screenHeight;

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;
	m_numFrames = numFrames;
	m_frameTime = frameTime;
	m_currentFrame = 0;
	m_currentTime = 0.0f;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Move(int key)
{
	if ((key == 38 || key == 87)&&Get2DPosition().y > 26)
	{
		Set2DPosition(Get2DPosition().x, Get2DPosition().y - 10);
	}
	if ((key == 40 || key == 83)&& Get2DPosition().y < screenHeight - 26)
	{
		Set2DPosition(Get2DPosition().x, Get2DPosition().y + 10);
	}
	if ((key == 37 || key == 65)&& Get2DPosition().x > 26)
	{
		Set2DPosition(Get2DPosition().x - 10, Get2DPosition().y);
	}
	if ((key == 39 || key == 68)&& Get2DPosition().x < screenWidth - 26)
	{
		Set2DPosition(Get2DPosition().x + 10, Get2DPosition().y);
	}
}