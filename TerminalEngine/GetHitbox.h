#pragma once

#include <vector>
#include <string>

class GetHitbox {

public:

	struct Hitbox {

		std::vector<int> rowStartX;
		std::vector<int> rowEndX;
		std::vector<int> solidRowLength;
		int leftMostPoint;
		int rightMostPoint;
		int topMostPoint;
		int bottomMostPoint;
		int spriteHeight;
	};

	static Hitbox getSpriteHitbox(const std::vector<std::string>& sprite);
};