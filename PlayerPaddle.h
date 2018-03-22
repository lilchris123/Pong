#pragma once
#include "VisibleGameObject.h"
#include <Box2D\Box2D.h>

class PlayerPaddle : public VisibleGameObject
{
public:
	PlayerPaddle(b2World* world, sf::Vector2f pos); //constructor
	~PlayerPaddle(); //deconstructor

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	float GetVelocity()const;
private:
	float velocity;
	float maxVelocity;
	b2BodyDef paddleBodyDef;
	b2Body* paddleBody;
	b2PolygonShape boxShape;
	b2FixtureDef  fixDef;
	
};