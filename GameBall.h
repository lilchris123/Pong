#pragma once
#include "visiblegameobject.h"
#include <Box2D\Box2D.h>

class GameBall :
	public VisibleGameObject
{
public:
	GameBall(b2World* world, sf::Vector2f pos);
	virtual ~GameBall();
	void Update(float);

private:
	float velocity;
	float angle;
	float elapsedTimeSinceStart;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
	b2BodyDef ballBodyDef;
	b2Body* ballBody;
	b2CircleShape ballShape;
	b2FixtureDef fixDef;
};