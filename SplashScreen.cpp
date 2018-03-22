#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture texture;
	//load splashscreen texture. if fail return
	if (texture.loadFromFile("Pongscreen.png") != true)
		return;
	sf::Sprite sprite(texture);
	sprite.setScale(3,3);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}