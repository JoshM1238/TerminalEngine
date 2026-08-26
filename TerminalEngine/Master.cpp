#include "Master.h"
#include "Screen.h"
#include "PlayerObject.h"
#include "GameClock.h"
#include "Controller.h"
#include "GetHitbox.h"
#include "GeneralObject.h"

#include <iostream>
#include <vector>










// ********** STOPPED HERE **********
// ********** OBJECT CLEARING FROM THE SCREEN IS NOT WORKING PROPERLY. FIX THAT NEXT **********

// ADD A CLASS TO PROCESS CONFIG FILES
// MOVE OBJECT PRINTING AND CLEARING TO THEIR OWN FUNCTIONS IN THE SCREEN CLASS, AND THEN JUST CALL THOSE FUNCTIONS IN THE PRINTSCREEN FUNCTION
// ADD LAYERS, AND MAKE IT SO THAT OBJECTS THAT PASS OVER EACH OTHER SO NOT GET CLEARED**

void Master::run(){

	bool isRunning = true;
	int frameCount = 0;
	std::array<int, 2> playerSpawnpoint{ 15, 15 };   // ********** MOVE THIS TO THE PLAYER CONFIG FILE LATER **********
	Screen screen;
	PlayerObject playerObject;
	GeneralObject object;
	Controller control;
	
	Controller::Controls movementButtons = control.setControls('W', 'S', 'A', 'D');   // ********** MOVE THESE SETTINGS INTO A CONFIG FILE LATER **********

	auto lastMoveTime = GameClock::Clock::now();

	const int frameDelay = 0;
	const int moveRate = 25;

	screen.hideCursor();

	std::vector<std::string> playerSprite = {   // ***** MOVE THIS INTO A SPRITE FILE AFTER CREATING A GET SPRITE CLASS *****
		"  *  ",
		" *** ",
		"*****"
	};










	// ********** THIS NEEDS REMOVED AFTER TESTING**********
	std::vector<std::string> enemySprite = {
		"    *    ",
		"   * *   ",
		"***   ***",
		" **   ** ",
		"*       *"
	};

	std::array<int, 2> enemySpawn{ 30, 7 };
	ObjectManager::Object& enemy = object.initializeObject(enemySprite, enemySpawn, true);
	// ********** THIS NEEDS REMOVED AFTER TESTING**********








	ObjectManager::Object& player = playerObject.initPlayerObject(playerSprite, playerSpawnpoint);

	// ***************TEMPORARY TEST CODE***************
	while (isRunning) {

		// Temporary: (Only print 100000000000 frames)
		if (frameCount >= 10) {
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
		// ********** OBJECT CLEARING FROM THE SCREEN IS NOT WORKING PROPERLY. FIX THAT NEXT **********
		// ALSO FIX HOW OBJECTS ARE BEING INITIALIZED (LOOK AT HOW THE PLAYER OBJECT IS CURRENTLY CREATED ABOVE. IT IS INCORRECT)

		// ADD A CLASS TO PROCESS CONFIG FILES
		// MOVE OBJECT PRINTING AND CLEARING TO THEIR OWN FUNCTIONS IN THE SCREEN CLASS, AND THEN JUST CALL THOSE FUNCTIONS IN THE PRINTSCREEN FUNCTION
		// ADD LAYERS, AND MAKE IT SO THAT OBJECTS THAT PASS OVER EACH OTHER SO NOT GET CLEARED**


















	}


	screen.showCursor();
}