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
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
#define NUMSMALL 5
#define NUMMEDIUM 2
#define NUMBIG 1

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
	
	for (int i = 0; i<NUMSMALL;i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("1enemy_small");
		auto Enemy = std::make_shared<SmallEnemy>(model, shader, texture, 2, 0.1f);
		int x = screenWidth - int(Enemy->Get2DSize().x) + Enemy->Get2DSize().x;
		Enemy->Set2DPosition(rand() % x, - 50 - i * 100);
		Enemy->SetSize(40, 40);
		m_listSmallEnemy.push_back(Enemy);
	}

	for (int i = 0; i<NUMMEDIUM; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("1enemy_medium");
		auto Enemy = std::make_shared<MediumEnemy>(model, shader, texture, 2, 0.1f);
		int x = screenWidth - int(Enemy->Get2DSize().x) + Enemy->Get2DSize().x;
		Enemy->Set2DPosition(rand() % x, -50 - i * 100);
		Enemy->SetSize(52, 52);
		m_listMediumEnemy.push_back(Enemy);
	}

	for (int i = 0; i<NUMBIG; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("1enemy_big");
		auto Enemy = std::make_shared<BigEnemy>(model, shader, texture, 2, 0.1f);
		int x = screenWidth - int(Enemy->Get2DSize().x) + Enemy->Get2DSize().x;
		Enemy->Set2DPosition(rand() % x, -50 - i * 100);
		Enemy->SetSize(65, 65);
		m_listBigEnemy.push_back(Enemy);
	}

	texture = ResourceManagers::GetInstance()->GetTexture("1explosion");
	m_explosion = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 0.1f);
	m_explosion->SetSize(50, 50);

	texture = ResourceManagers::GetInstance()->GetTexture("1blue_power_up");
	auto heal = std::make_shared<SpriteAnimation>(model, shader, texture, 2, 0.1f);
	heal->SetSize(30, 30);
	heal->Set2DPosition(rand() % screenWidth, -50 );
	m_listBuff.push_back(heal);

	texture = ResourceManagers::GetInstance()->GetTexture("1red_power_up");
	auto dameup = std::make_shared<SpriteAnimation>(model, shader, texture, 2, 0.1f);
	dameup->SetSize(30, 30);
	dameup->Set2DPosition(rand() % screenWidth, -50);
	m_listBuff.push_back(dameup);

	//text game title
	
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	m_Hp = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_Hp->Set2DPosition(Vector2(5, 100));

	//sound
	ResourceManagers::GetInstance()->PlaySound("bg2", true);
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

void GSPlay::SpawnBuff(float deltaTime)
{
	m_fTimeSpwnBuff += deltaTime;

	if(m_fTimeSpwnBuff>=5)
	{
		m_listBuff[0]->Set2DPosition(m_listBuff[0]->Get2DPosition().x, m_listBuff[0]->Get2DPosition().y - 100 * deltaTime);
	}
	if (m_fTimeSpwnBuff >= 10)
	{
		m_listBuff[1]->Set2DPosition(m_listBuff[1]->Get2DPosition().x, m_listBuff[1]->Get2DPosition().y - 100 * deltaTime);
	}
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
	//enemy
	for (auto obj : m_listSmallEnemy)
	{
		if (obj->GetIsActive())
		{
			obj->Update(deltaTime);
			obj->Move(deltaTime);
		}
		else
		{
			obj->Respawn(deltaTime);
		}
	}

	for (auto obj : m_listMediumEnemy)
	{
		if (obj->GetIsActive())
		{
			obj->Update(deltaTime);
			obj->Move(deltaTime);
		}
		else
		{
			obj->Respawn(deltaTime);
		}
	}

	for (auto obj : m_listBigEnemy)
	{
		if (obj->GetIsActive())
		{
			obj->Update(deltaTime);
			obj->Move(deltaTime);
		}
		else
		{
			obj->Respawn(deltaTime);
		}
	}

	//bullet
	SetNewPostionForBullet(deltaTime);
	//background
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

	//explosion
	m_explosion->Update(deltaTime);
	//buff
	SpawnBuff(deltaTime);


	//text score
	std::string text = "Hp: " + std::to_string(m_Player->GetHp());
	m_score->setText(text);
	//text hp
	text = "Score: " + std::to_string(m_iScore);
	m_score->setText(text);
}

void GSPlay::Draw()
{
	for (auto bg : m_listSprite2D)
	{
		bg->Draw();
	}

	for (auto obj : m_Player->GetListBullet())
	{
		if (obj->GetIsActive())
		{
			obj->Draw();
		}
	}

	m_Player->Draw();

	for (auto obj : m_listMediumEnemy)
	{
		if (obj->GetIsActive())
		{
			for (auto bullet : obj->GetListBullet())
			{
				if (bullet->GetIsActive())
				{
					bullet->Draw();
				}
				obj->Draw();
			}
		}
	}

	for (auto obj : m_listBigEnemy)
	{
		if (obj->GetIsActive())
		{
			for (auto bullet : obj->GetListBullet())
			{
				if (bullet->GetIsActive())
				{
					bullet->Draw();
				}
				obj->Draw();
			}
		}
	}

	for (auto obj : m_listSmallEnemy)
	{
		obj->Draw();
	}

	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_score->Draw();
	m_Hp->Draw();
	for (auto obj : m_listBuff)
	{
		obj->Draw();
	}
}

void GSPlay::SetNewPostionForBullet(GLfloat deltaTime)
{
	m_Player->Shoot(deltaTime, ShipTypes::PLAYER, m_Player->GetNumBullet());
	for (auto obj : m_listMediumEnemy)
	{
		obj->Shoot(deltaTime, ShipTypes::MEDIUM, obj->GetNumBullet());
	}

	for (auto obj : m_listBigEnemy)
	{
		obj->Shoot(deltaTime, ShipTypes::BIG, obj->GetNumBullet());
	}
}

bool GSPlay::IsCollided(std::shared_ptr<SpriteAnimation> objA, std::shared_ptr<SpriteAnimation> objB)
{
	if (objA->Get2DPosition().x + objA->Get2DSize().x >= objB->Get2DPosition().x&&
		objA->Get2DPosition().x <= objB->Get2DPosition().x + objB->Get2DPosition().x&&
		objA->Get2DPosition().y + objA->Get2DSize().y >= objB->Get2DPosition().y&&
		objA->Get2DPosition().y <= objB->Get2DPosition().y + objB->Get2DSize().y)
	{

		return true;
	}
	return false;
}

void GSPlay::CheckCollide()
{
	for (auto obj : m_listSmallEnemy)
	{
		if (IsCollided(obj, m_Player))
		{
			obj->Set2DPosition(rand() % screenWidth, 0);
			obj->SetDead();
			m_Player->Hitted(10);
			m_explosion->Set2DPosition(obj->Get2DPosition());
			m_explosion->Draw();
			m_iScore += 5;
		}
	}


	/*for (auto obj : m_listMediumEnemy)
	{
		if (IsCollided(obj, m_Player))
		{
			obj->Set2DPosition(rand() % screenWidth, 0);
			obj->SetDead();
			m_Player->Hitted(10);
			m_explosion->Set2DPosition(obj->Get2DPosition());
			m_explosion->Draw();
			m_iScore += 10;
		}
	}

	for (auto obj : m_listBigEnemy)
	{
		if (IsCollided(obj, m_Player))
		{
			obj->Set2DPosition(rand() % screenWidth, 0);
			obj->SetDead();
			m_Player->Hitted(10);
			m_explosion->Set2DPosition(obj->Get2DPosition());
			m_explosion->Draw();
			m_iScore += 15;
		}
	}*/

	/*for (auto obj1 : m_listSmallEnemy)
	{
		for (auto obj2: m_Player->GetListBullet())
		if (IsCollided(obj1, obj2))
		{
			obj1->Hitted(obj2->GetDame());
			if (obj1->GetHp() <= 0)
			{
				m_explosion->Set2DPosition(obj1->Get2DPosition());
				m_explosion->Draw();
				m_iScore += 5;
				obj1->Set2DPosition(rand() % screenWidth, -50);
			}
		}
	}

	for (auto obj1 : m_listMediumEnemy)
	{
		for (auto obj2 : m_Player->GetListBullet())
			if (IsCollided(obj1, obj2))
			{
				obj1->Hitted(obj2->GetDame());
				if (obj1->GetHp() <= 0)
				{
					m_explosion->Set2DPosition(obj1->Get2DPosition());
					m_explosion->Draw();
					m_iScore += 10;
					obj1->Set2DPosition(rand() % screenWidth, -50);
				}
			}
	}

	for (auto obj1 : m_listBigEnemy)
	{
		for (auto obj2 : m_Player->GetListBullet())
			if (IsCollided(obj1, obj2))
			{
				obj1->Hitted(obj2->GetDame());
				if (obj1->GetHp() <= 0)
				{
					m_explosion->Set2DPosition(obj1->Get2DPosition());
					m_explosion->Draw();
					m_iScore += 15;
					obj1->Set2DPosition(rand() % screenWidth, -50);
				}
			}
	}*/
	
}
