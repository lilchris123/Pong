#include "PlayerPaddle.h"
#include "Game.h"
#include <cassert>

PlayerPaddle::PlayerPaddle(b2World* world, sf::Vector2f pos):
	velocity(0), maxVelocity(2600.0f)
{
	Load("paddle.png");
	assert(IsLoaded());
	GetSprite().setTextureRect(sf::IntRect(sf::Vector2i(119, 119), sf::Vector2i(111, 15)));
	
	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);

	//Box2d body
	paddleBodyDef.type = b2_kinematicBody;
	paddleBodyDef.position.Set(pos.x,pos.y);
	paddleBody = world->CreateBody(&paddleBodyDef);
	boxShape.SetAsBox(111/2, 15/2);
	//fixture
	fixDef.shape = &boxShape;
	fixDef.density = 1;
	paddleBody->CreateFixture(&fixDef);

}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const
{
	return paddleBody->GetLinearVelocity().x;
}

void PlayerPaddle::Update(float elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		paddleBody->SetLinearVelocity(b2Vec2(-550.0f, 0.0f));
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		paddleBody->SetLinearVelocity(b2Vec2(550.0f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		paddleBody->SetLinearVelocity(b2Vec2(0.0f,0.0f));
	}
	if (paddleBody->GetLinearVelocity().x > maxVelocity)
		paddleBody->SetLinearVelocity(b2Vec2(maxVelocity, 0));

	if (paddleBody->GetLinearVelocity().x < -maxVelocity)
		paddleBody->SetLinearVelocity(b2Vec2(-maxVelocity,0));
	
	b2Vec2 pos = paddleBody->GetPosition();

	if (pos.x  < GetSprite().getLocalBounds().width / 2
		|| pos.x >(Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2) && paddleBody->GetLinearVelocity().x >0)
	{
		paddleBody->SetLinearVelocity(b2Vec2(-paddleBody->GetLinearVelocity().x,0)) ; // Bounce by current velocity in opposite direction
	}

	GetSprite().setPosition(paddleBody->GetPosition().x, paddleBody->GetPosition().y);
}