#include "Screen.h"


// Deals with clearing and re-printing objects to the screen
void Screen::printScreen() {

	COORD position;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int key : ObjectManager::printOrder) {

		ObjectManager::Object& object = ObjectManager::objectList.at(key);

		if (object.hasMoved) {






			// **********MOVE OBJECT CLEARING TO ITS OWN FUNCTION IN THE SCREEN CLASS, AND THEN JUST CALL THAT HERE**********
			// Clear all non-space characters
			for (size_t row = 0; row < object.objectSprite.size(); row++) {

				if (object.hitbox.rowStartX[row] == -1) { continue; }

				position.X = static_cast<SHORT>(object.previousCoordsXY[0] + object.hitbox.rowStartX[row]);
				position.Y = static_cast<SHORT>(object.previousCoordsXY[1] + row);
				SetConsoleCursorPosition(console, position);

				int rowSize = object.hitbox.rowEndX[row] - object.hitbox.rowStartX[row] + 1;
				std::cout << std::string(rowSize, ' ');
			}




			// **********MOVE OBJECT PRINTING TO ITS OWN FUNCTION IN THE SCREEN CLASS, AND THEN JUST CALL THAT HERE**********
			// Re-prints the sprint, in its new position, without printing any unnecessary space characters
			for (size_t row = 0; row < object.objectSprite.size(); row++) {

				if (object.hitbox.rowStartX[row] == -1) { continue; }

				position.X = static_cast<SHORT>(object.coordsXY[0] + object.hitbox.rowStartX[row]);
				position.Y = static_cast<SHORT>(object.coordsXY[1] + row);

				SetConsoleCursorPosition(console, position);

				std::string& line = object.objectSprite[row];


				// This finds the position of the non-space characters in the row, and prints them at the correct coordinates
				for (size_t i = object.hitbox.rowStartX[row]; i <= object.hitbox.rowEndX[row]; i++) {
					std::cout << line[i];
				}
			}

			object.hasMoved = false;
		}
	}
	
	return;
}


// Wait this long and then print the frame
void Screen::frameRate(const int& milPerFrame) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milPerFrame));
	return;
}


// returns a struct containing the dimensions of the screen
Screen::ScreenDimensions Screen::getScreenSize(const ScreenFrame& frame){

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	Screen::ScreenDimensions screen{};

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);

	// Playable screen dimensions
	screen.playableScreenStart = consoleInfo.srWindow.Left + frame.sideFrameWidth;
	screen.playableScreenEnd = consoleInfo.srWindow.Right - frame.sideFrameWidth;
	screen.playableScreenTop = consoleInfo.srWindow.Top + frame.verticalFrameHeight;
	screen.playableScreenBottom = consoleInfo.srWindow.Bottom - frame.verticalFrameHeight;

	screen.playableScreenWidth = screen.playableScreenEnd - screen.playableScreenStart + 1;
	screen.playableScreenHeight = screen.playableScreenBottom - screen.playableScreenTop + 1;

	// Full screen dimensions
	screen.trueScreenStart = consoleInfo.srWindow.Left;
	screen.trueScreenEnd = consoleInfo.srWindow.Right;
	screen.trueScreenTop = consoleInfo.srWindow.Top;
	screen.trueScreenBottom = consoleInfo.srWindow.Bottom;

	screen.trueScreenWidth = screen.trueScreenEnd - screen.trueScreenStart + 1;
	screen.trueScreenHeight = screen.trueScreenBottom - screen.trueScreenTop + 1;


	return screen;
}

void Screen::hideCursor() {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	GetConsoleCursorInfo(console, &cursor);
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(console, &cursor);

	return;
}

void Screen::showCursor() {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	GetConsoleCursorInfo(console, &cursor);
	cursor.bVisible = TRUE;
	SetConsoleCursorInfo(console, &cursor);

	return;
}

