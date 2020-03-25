#include "GSPause.h"
#include "GameButton.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Text.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPause::GSPause()
{
}


GSPause::~GSPause()
{

}


void GSPause::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("1play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 90 - 15, screenHeight/2 - 60 - 15);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//replay button
	texture = ResourceManagers::GetInstance()->GetTexture("1replay");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 30, screenHeight / 2 - 60 - 15);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(button);

	//menu button
	texture = ResourceManagers::GetInstance()->GetTexture("1menu");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 30 + 15, screenHeight / 2 - 60 - 15);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//sound on button
	texture = ResourceManagers::GetInstance()->GetTexture("1soundon");
	m_sound = std::make_shared<GameButton>(model, shader, texture);
	m_sound->Set2DPosition(screenWidth / 2 - 15, screenHeight / 2 + 15);
	m_sound->SetSize(60, 60);
	m_sound->SetOnClick([]() {
		ResourceManagers::GetInstance()->PlaySound("bg1");
		
	});

	//mute button
	texture = ResourceManagers::GetInstance()->GetTexture("1mute");
	m_mute = std::make_shared<GameButton>(model, shader, texture);
	m_mute->Set2DPosition(screenWidth / 2 - 15, screenHeight / 2 + 15);
	m_mute->SetSize(60, 60);
	m_mute->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSound("bg1");
		//GSPause::MuteUnmute();
		
	});

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_text = std::make_shared< Text>(shader, font, "Pause", TEXT_COLOR::RED, 1.0);
	m_text->Set2DPosition(Vector2(screenWidth / 2 - 80, 50));
}

void GSPause::Exit()
{

}


void GSPause::Pause()
{

}

void GSPause::Resume()
{

}


void GSPause::HandleEvents()
{

}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPause::HandleTouchEvents(int x, int y, bool bIsPressed)
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

void GSPause::Update(float deltaTime)
{
}

void GSPause::MuteUnmute()
{
	if(m_IsMute)
	{
		m_IsMute = false;
	}
	else
	{
		m_IsMute = true;
	}
}

void GSPause::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	if (m_IsMute)
	{
		m_sound->Draw();
	}
	else
	{
		m_mute->Draw();
	}
	m_text->Draw();
}
