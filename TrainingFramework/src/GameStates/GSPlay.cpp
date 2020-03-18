#include "GSPlay.h"
#include "GameButton.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
//#include"GameObject/"
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("1bg");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(m_BackGround);
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, - screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(m_BackGround);

	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("1pause");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth -30, 30);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Pause);
	});
	m_listButton.push_back(button);

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("1ship");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	obj->Set2DPosition(240, 650);
	obj->SetSize(52, 52);
	m_listSpriteAnimations.push_back(obj);
	
	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 0", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		if (key == 38 || key == 87)
		{
			for (auto obj : m_listSpriteAnimations)
			{
				obj->Set2DPosition(obj->Get2DPosition().x, obj->Get2DPosition().y - 10);
			}
		}

		if (key == 40 || key == 83)
		{
			for (auto obj : m_listSpriteAnimations)
			{
				obj->Set2DPosition(obj->Get2DPosition().x, obj->Get2DPosition().y + 10);
			}
		}

		if (key == 37 || key == 65)
		{
			for (auto obj : m_listSpriteAnimations)
			{
				obj->Set2DPosition(obj->Get2DPosition().x - 10, obj->Get2DPosition().y);
			}
		}

		if (key == 39 || key == 68)
		{
			for (auto obj : m_listSpriteAnimations)
			{
				obj->Set2DPosition(obj->Get2DPosition().x + 10, obj->Get2DPosition().y);
			}
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!bIsPressed)
	{
		for (auto it : m_listButton)
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
	}
}

void GSPlay::Update(float deltaTime)
{
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Update(deltaTime);
	}

	for (auto bg : m_listSprite2D)
	{
		bg->Update(deltaTime);
		if (bg->Get2DPosition().y > screenHeight * 3 / 2-1)
		{
			bg->Set2DPosition(screenWidth / 2, -screenHeight / 2);
		}
	}
}

void GSPlay::Draw()
{
	for (auto bg : m_listSprite2D)
	{
		bg->Draw();
	}

	for (auto obj : m_listSpriteAnimations)
	{
		obj->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}