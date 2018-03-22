#include "GameBall.h"
#include "Game.h"
#include <cassert>


GameBall::GameBall(b2World* world, sf::Vector2f pos): elapsedTimeSinceStart(0.0f)
{
	Load("paddle.png");
	assert(IsLoaded());
	GetSprite().setTextureRect(sf::IntRect(sf::Vector2i(112, 14), sf::Vector2i(27, 24)));

	GetSprite().setOrigin(15, 15);

	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(pos.x, pos.y);
	ballBody = world->CreateBody(&ballBodyDef);
	ballShape.m_radius = 2;

	fixDef.shape = &ballShape;
	ballBody->CreateFixture(&fixDef);
	
}

GameBall::~GameBall()
{
}

void GameBall::Update(float elapsedTime)
{
	elapsedTimeSinceStart += elapsedTime;
	
	//Delay game from starting until 3 seconds have passed
	if (elapsedTimeSinceStart < 3.0f)
		return;
	//ballBody->ApplyForce(b2Vec2(0, 50), ballBody->GetWorldCenter(),true);
	GetSprite().setPosition(ballBody->GetPosition().x, ballBody->GetPosition().y);

}

float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}
