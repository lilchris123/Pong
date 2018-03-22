#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameBall.h"

//start the game
void Game::Start()
{
	//return if gamestate is uninitialized
	if (gameState != Uninitialized)
		return;
	//create the main window
	mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Welcome to Pang!");
	//Box2dWorld
	b2Vec2 gravity(0.0f, -9.8f);
	b2World* world = new b2World(gravity);

	PlayerPaddle* player1 = new PlayerPaddle(world, sf::Vector2f((SCREEN_WIDTH / 2), 700));
	GameBall* ball = new GameBall(world, sf::Vector2f((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15));
	
	gameObjectManager.Add("Paddle1", player1);
	gameObjectManager.Add("Ball", ball);
	//set gameState to showing the splash screen
	gameState = Game::ShowingSplash;
	//while game now exiting continue the gameloop
	while (!IsExiting())
	{
		GameLoop(world);
	}
	mainWindow.close(); //close window
}

GameObjectManager & Game::GetGameObjectManager()
{
	return Game::gameObjectManager;
}

// check if the gamestate is Exiting, if so return true
bool Game::IsExiting()
{
	if (gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::ShowSplashScreen()
{
	SplashScreen splashscreen;
	splashscreen.Show(mainWindow);
	gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(mainWindow);
	switch (result) 
	{
	case MainMenu::Exit:
		gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		gameState = Game::Playing;
		break;
	}
}
void Game::GameLoop(b2World* world)
{
	//create an current event holder
	sf::Event currentEvent;
	// loop through and handel all events
	mainWindow.pollEvent(currentEvent);
		switch (gameState)
		{
		case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
		case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
		case Game::Playing:
		{
			mainWindow.clear(sf::Color::Black);
			world->Step(timeStep, velocityIterations, positionIterations);
			gameObjectManager.UpdateAll();
			gameObjectManager.DrawAll(mainWindow);
			mainWindow.display();

			//check if event is window close event
			if (currentEvent.type == sf::Event::Closed)
				gameState = Game::Exiting;	//set gameState to Exiting

			if (currentEvent.type == sf::Event::KeyPressed)
				if (currentEvent.type == sf::Keyboard::Escape)
					ShowMenu();
		}
		break;
		}
}
//initialize our static variables
Game::GameState Game::gameState = Game::Uninitialized;
sf::RenderWindow Game::mainWindow;
GameObjectManager Game::gameObjectManager;
float Game::timeStep = 1.0f / 30.0f;   //the length of time passed to simulate (seconds)
int Game::velocityIterations = 8;   //how strongly to correct velocity
int Game::positionIterations = 3;   //how strongly to correct position