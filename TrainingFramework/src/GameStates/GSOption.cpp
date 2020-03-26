#include "GSOption.h"
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

GSOption::GSOption()
{
}


GSOption::~GSOption()
{

}


void GSOption::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 600);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);
	
	//sound on button
	texture = ResourceManagers::GetInstance()->GetTexture("1soundon");
	auto sound = std::make_shared<GameButton>(model, shader, texture);
	sound->Set2DPosition(screenWidth / 2 - 15, screenHeight / 2 + 15);
	sound->SetSize(60, 60);
	sound->SetOnClick([]() {
		ResourceManagers::GetInstance()->PlaySound("bg1");
	});
	m_listButton.push_back(sound);

	//mute button
	texture = ResourceManagers::GetInstance()->GetTexture("1mute");
	auto mute = std::make_shared<GameButton>(model, shader, texture);
	mute->Set2DPosition(screenWidth / 2 - 15, screenHeight / 2 + 15);
	mute->SetSize(60, 60);
	mute->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSound("bg1");
		
	});
	m_listButton.push_back(mute);

	
	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_text = std::make_shared< Text>(shader, font, "Setting", TEXT_COLOR::RED, 1.0);
	m_text->Set2DPosition(Vector2(screenWidth/2-80, 50));
}

void GSOption::Exit()
{

}


void GSOption::Pause()
{

}

void GSOption::Resume()
{

}


void GSOption::HandleEvents()
{

}

void GSOption::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSOption::Update(float deltaTime)
{
}

void GSOption::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_text->Draw();
}
