#pragma once
#include "GameStateBase.h"
#include "GameButton.h"

class Sprite2D;
class Text;

class GSPause:
	public GameStateBase
{
public:
	GSPause();
	~GSPause();

	void Init();
	void Exit();

	void Pause();
	void Resume();
	void MuteUnmute();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_text;
	std::shared_ptr<GameButton> m_mute;
	std::shared_ptr<GameButton> m_sound;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	bool m_IsMute = false;
};