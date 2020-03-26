#pragma once 
#include "Sprite2D.h"

class GameButton : public Sprite2D
{
public:
	GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	void SetActive() { m_IsActive = true; }
	void SetDeactive() { m_IsActive = false; }

private:
	void	(*m_pBtClick)();
	bool	m_isHandle;
	bool m_IsActive = false;
};
