#include "Ship.h"
#include "Models.h"



Ship::Ship(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	:SpriteAnimation(model,  shader, texture, numFrames, frameTime)
{
}

Ship::~Ship()
{
}

void Ship::Shoot()
{

}

void Ship::Explode()
{

}


