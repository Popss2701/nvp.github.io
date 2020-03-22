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
#include <cstdlib>
#include <ctime>
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
#define NUMSMALL 1

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
	m_Player = std::make_shared<Player>(model, shader, texture, 2, 0.1f);
	m_Player->Set2DPosition(240, 650);
	m_Player->SetSize(52, 52);
	m_listSpriteAnimations.push_back(m_Player);
	
	static int IdSmall = 1;
	for (int i = 0; i<NUMSMALL;i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("1enemy_small");
		auto Enemy = std::make_shared<SmallEnemy>(model, shader, texture, 2, 0.1f, IdSmall);
		Enemy->Set2DPosition(rand() % screenWidth, 50);
		Enemy->SetSize(52, 52);
		m_listSmallEnemy.push_back(Enemy);
		IdSmall++;
	}

	texture = ResourceManagers::GetInstance()->GetTexture("1explosion");
	auto explosion = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 0.1f);
	explosion->SetSize(50, 50);
	m_listSpriteAnimations.push_back(explosion);
	

	//text game title
	
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "0", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//sound
	//ResourceManagers::GetInstance()->AddSound("bossbg");
	ResourceManagers::GetInstance()->PlaySound("bg1");
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
		m_Player->Move(key);
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (bIsPressed)
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
	CheckCollide();
	m_Player->Update(deltaTime);
	

	for (auto obj : m_listSmallEnemy)
	{
		obj->Update(deltaTime);
		obj->Move(deltaTime);
		if (obj->Get2DPosition().y > screenHeight)
		{
			// m_listSmallEnemy.erase()

		}
	}

	Vector2 oldPos1 = m_listSprite2D[0]->Get2DPosition();
	Vector2 oldPos2 = m_listSprite2D[1]->Get2DPosition();
	float deltaMove = 100 * deltaTime;
	if (oldPos1.y > screenHeight * 3 / 2)
	{
		m_listSprite2D[0]->Set2DPosition(oldPos1.x, oldPos2.y + deltaMove - screenHeight);
	}
	else
	{
		m_listSprite2D[0]->Set2DPosition(oldPos1.x, oldPos1.y + deltaMove);
	}
	if (oldPos2.y > screenHeight * 3 / 2)
	{
		m_listSprite2D[1]->Set2DPosition(oldPos2.x, oldPos1.y + deltaMove - screenHeight);
	}
	else
	{
		m_listSprite2D[1]->Set2DPosition(oldPos2.x, oldPos2.y + deltaMove);
	}
}

void GSPlay::Draw()
{
	for (auto bg : m_listSprite2D)
	{
		bg->Draw();
	}

	m_Player->Draw();

	for (auto obj : m_listSmallEnemy)
	{
		obj->Draw();
	}

	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_score->Draw();
}

bool GSPlay::IsCollided(Vector2 locA, Vector2 sizeA, Vector2 locB, Vector2 sizeB)
{
	if (locA.x>locB.x)
	{
		return IsCollided(locB, sizeB, locA, sizeA);
	}
	if ((locA.y+sizeA.y>=locB.x||locB.y+sizeB.y>=locA.y)&&locA.x+sizeA.x>=locB.x)
	{
		return true;
	}
	else { return false; }
}

void GSPlay::SetNewPostionForBullet()
{
}

void GSPlay::CheckCollide()
{
	for (auto obj : m_listSmallEnemy)
	{
		if (IsCollided(obj->Get2DPosition(), obj->Get2DSize(), m_Player->Get2DPosition(), m_Player->Get2DSize()))
		{
			for (auto it : m_listSpriteAnimations) 
			{ 
				it->Set2DPosition(obj->Get2DPosition());
				it->Draw();

			}
		}
	}
}
