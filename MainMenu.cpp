#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("mainmenu.png");
	sf::Sprite sprite(texture);

	//setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.left = 170;
	playButton.rect.top = 190;
	playButton.rect.width = 488;
	playButton.rect.height = 80;
	//set the action of button to Play
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 170;
	exitButton.rect.top = 354;
	exitButton.rect.width = 488;
	exitButton.rect.height = 80;
	//set the action of button to Exit
	exitButton.action = Exit;

	//push buttons to the list of menuitems
	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);

	//draw the menu
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}	

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	// list of Menu items iterator to go through the list
	std::list<MenuItem>::iterator it;
	for (it = menuItems.begin(); it != menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = it->rect;
		if (menuItemRect.contains(sf::Vector2i(x,y)))
		{
			return it->action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	
	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			switch (menuEvent.type)
			{
			case sf::Event::MouseButtonPressed:
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			case sf::Event::Closed:
				return Exit;
			}
		}
	}
}