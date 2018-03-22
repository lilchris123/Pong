#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <list>

class MainMenu
{
public:
	// enum type for various possible return values
	enum MenuResult { Nothing, Exit, Play};
	//
	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		MenuResult action;
	};
	
	// Show function that takes in reference or our window, and returns an MenuResult enum type
	MenuResult Show(sf::RenderWindow& window);

	private:
		MenuResult GetMenuResponse(sf::RenderWindow& window);
		MenuResult HandleClick(int x, int y);
		std::list<MenuItem> menuItems;

};