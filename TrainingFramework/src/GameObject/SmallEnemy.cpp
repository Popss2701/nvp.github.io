#include "SmallEnemy.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"

SmallEnemy::SmallEnemy()
{
	
}


SmallEnemy::~SmallEnemy()
{
}

void SmallEnemy::SetSprite(std::shared_ptr<SpriteAnimation> obj)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("1enemy_small");
	obj = std::make_shared<SpriteAnimation>(model, shader, texture, 2, 0.1f);
	obj->Set2DPosition(50,100);
	obj->SetSize(52, 52);
}
