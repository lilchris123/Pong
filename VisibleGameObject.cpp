#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
{
	isLoaded = false;
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	if (texture.loadFromFile(filename) == false)
	{
		filename = "";
		isLoaded = false;

	}
	else {
		filename = filename;
		sprite.setTexture(texture);
		isLoaded = true;
	}
}

void VisibleGameObject::Update(float elaspedTime)
{

}

sf::Vector2f VisibleGameObject::GetPosition()const
{
	if (isLoaded)
	{
		return sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return sprite;
}

void VisibleGameObject::Draw(sf::RenderWindow &renderWindow)
{
	if (isLoaded)
		renderWindow.draw(sprite);
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (isLoaded)
	{
		sprite.setPosition(x, y);
	}
}

bool VisibleGameObject::IsLoaded() const
{
	return isLoaded;
}

float VisibleGameObject::GetWidth() const
{
	return sprite.getLocalBounds().width;
}

float VisibleGameObject::GetHeight() const
{
	return sprite.getLocalBounds().height;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	return sprite.getGlobalBounds();
}
