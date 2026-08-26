#pragma once

#include "Windows.h"
#include "PlayerObject.h"

#include <array>

class Controller {
public:

	struct Controls {
		char up;
		char down;
		char left;
		char right;
	};

	Controls setControls(const char up, const char down, const char left, const char right);

	std::array<int, 2> getInput(const Controls& control);
};