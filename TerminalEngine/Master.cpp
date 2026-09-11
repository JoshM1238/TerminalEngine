#include "Master.h"
#include "Screen.h"
#include "PlayerObject.h"
#include "GameClock.h"
#include "Controller.h"
#include "GetHitbox.h"
#include "GeneralObject.h"
#include "TxtHandler.h"

#include <iostream>
#include <vector>










// ********** STOPPED HERE **********

// CHANGE THE PRINTORDER FUNCTIONALITY TO UPDATE ON A SET INTERVAL INSTEAD OF UPDATING EVERY TIME AN OBJECT MOVES
// ADD A FUNCTION TO THE SCREEN CLASS TO SET THE OUTPUT FONT
// ADD A FUNCTION TO THE TEXT PARSER CLASS TO PROCESS CONFIG FILES
// USING THE NEW LAYERS IN THE OBJECT, MAKE IT SO THAT BACKGROUND OBJECTS ARE NOT CLEARED WHEN PASSED OVER UNLESS THEY NEED TO BE

void Master::run(){

	bool isRunning = true;
	int frameCount = 0;
	std::array<int, 2> playerSpawnpoint{ 15, 15 };   // ********** MOVE THIS TO THE PLAYER CONFIG FILE LATER **********
	Screen screen;
	PlayerObject playerObject;
	GeneralObject object;
	Controller control;
	TxtHandler parser;
	
	Controller::Controls movementButtons = control.setControls('W', 'S', 'A', 'D');   // ********** MOVE THESE SETTINGS INTO A CONFIG FILE LATER **********

	auto lastMoveTime = GameClock::Clock::now();

	const int frameDelay = 0;
	const int moveRate = 25;

	screen.hideCursor();

	std::vector<std::string> playerSprite = parser.parseSprite("../Sprites/PlayerSprite.txt");
	std::vector<std::string> enemySprite = parser.parseSprite("../Sprites/EnemySprite.txt");


	std::array<int, 2> enemySpawn{ 30, 7 };
	ObjectManager::Object& enemy = object.initializeObject(enemySprite, enemySpawn, true);
	// ********** THIS NEEDS REMOVED AFTER TESTING**********








	ObjectManager::Object& player = playerObject.initPlayerObject(playerSprite, playerSpawnpoint);

	// ***************TEMPORARY TEST CODE***************
	while (isRunning) {

		// Temporary: (Only print 100000000000 frames)
		if (frameCount >= 100000000000000) {
			isRunning = false;
		}

		// Set the screen dimension values in the ScreenDimensions struct
		Screen::ScreenDimensions screenDimensions = Screen::getScreenSize({ 10 });   // the numbers passed in here are the size of the frame of the screen

		GameClock::Clock::time_point currentTime = GameClock::Clock::now();

		std::array<int, 2> movement = control.getInput(movementButtons);

		if (GameClock::checkElapsedMills(lastMoveTime, currentTime, moveRate)){

			object.moveObject(player, movement, screenDimensions);




			lastMoveTime = GameClock::Clock::now();
		}
		
		frameCount++;

		// Generate a new frame every x milliseconds
		screen.frameRate(frameDelay);
		screen.printScreen();

		// ********** STOPPED HERE **********

		// CHANGE THE PRINTORDER FUNCTIONALITY TO UPDATE ON A SET INTERVAL INSTEAD OF UPDATING EVERY TIME AN OBJECT MOVES
		// ADD A FUNCTION TO THE SCREEN CLASS TO SET THE OUTPUT FONT
		// ADD A FUNCTION TO THE TEXT PARSER CLASS TO PROCESS CONFIG FILES
		// USING THE NEW LAYERS IN THE OBJECT, MAKE IT SO THAT BACKGROUND OBJECTS ARE NOT CLEARED WHEN PASSED OVER UNLESS THEY NEED TO BE
















	}


	screen.showCursor();
}