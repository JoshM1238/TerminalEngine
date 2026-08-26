#pragma once

#include "Windows.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <array>

#include "ObjectManager.h"

class Screen {

public:

	void printScreen();   // clear the necessary objects and reprint them in their new positions

	void frameRate(const int& milPerFrame);   // set frames per second (usefull because the terminal looks bad at extremely high frame rates)

	struct ScreenDimensions {

		int horizontalFrame;   // the number of spaces on the sides of the screen before the actual playable screen starts and ends
		int verticalFrame;   // the number of lines on the bottom and top of the screen before the playable screen starts and ends
		int playableScreenWidth;   // the width of the screen after accounting for the set side frames
		int playableScreenHeight;   // the height of the screen after accounting for the set vertical frames
		int playableScreenStart;
		int playableScreenEnd;
		int playableScreenTop;
		int playableScreenBottom;
		int trueScreenStart;
		int trueScreenEnd;
		int trueScreenTop;
		int trueScreenBottom;
		int trueScreenWidth;
		int trueScreenHeight;
	};

	struct ScreenFrame {
		int sideFrameWidth;
		int verticalFrameHeight;
	};

	// To check and/or set screen size. Do this before ever using getScreenWidth() or getScreenHeight()
	static ScreenDimensions getScreenSize(const ScreenFrame& frame = {0, 0});

	void hideCursor();
	void showCursor();
};