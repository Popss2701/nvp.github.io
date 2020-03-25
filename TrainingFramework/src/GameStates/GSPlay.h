#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Player.h"
#include "Bullet.h"
#include "SmallEnemy.h"
#include "MediumEnemy.h"
#include "BigEnemy.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	void SpawnBuff(float deltaTime);
	bool IsCollided(std::shared_ptr<SpriteAnimation> objA, std::shared_ptr<SpriteAnimation> objB);
	void CheckCollide();
	void SetNewPostionForBullet(GLfloat deltaTime);

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Text>  m_Hp;
	int m_iScore = 0;
	float m_fTimeSpwnBuff = 0;
	std::shared_ptr<SpriteAnimation>  m_explosion;
	std::vector < std::shared_ptr<SmallEnemy>> m_listSmallEnemy;
	std::vector < std::shared_ptr<MediumEnemy>> m_listMediumEnemy;
	std::vector < std::shared_ptr<BigEnemy>> m_listBigEnemy;
	std::vector < std::shared_ptr<SmallEnemy>> m_listBossEnemy;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listBuff;
	std::list<std::shared_ptr<GameButton>>	m_listButton;

};

