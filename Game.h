#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "PlayerPaddle.h"
#include "GameObjectManager.h"
#include <Box2D\Box2D.h>


class Game
{

public:
	static void Start();
	const static signed int SCREEN_WIDTH = 1024;
	const static signed int SCREEN_HEIGHT = 768;
	static GameObjectManager& GetGameObjectManager();
private:
	static bool IsExiting();
	static void GameLoop(b2World* world);

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState {Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting};

	static GameState gameState;
	static sf::RenderWindow mainWindow;
	
	static GameObjectManager gameObjectManager;

	static float timeStep;
	static int velocityIterations;
	static int positionIterations;
};
