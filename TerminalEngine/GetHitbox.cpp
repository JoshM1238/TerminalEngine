#include "GetHitbox.h"

// Takes in a sprite and returns its hitbox in the form of an object of the Hitbox struct
GetHitbox::Hitbox GetHitbox::getSpriteHitbox(const std::vector<std::string>& sprite) {

	Hitbox hitbox;

	hitbox.spriteHeight = sprite.size();

	int leftMostX = -1;   // to set the furthest inward edge point
	int rightMostX = -1;   // to set the furthest outward edge point
	int topMostPoint = -1;

	for (int yIndex = 0; yIndex < sprite.size(); yIndex++) {

		int startX = -1;
		int endX = -1;

		std::string rowAsStr = sprite[yIndex];

		for (int i = 0; i < sprite[yIndex].size(); i++) {
			
			if (rowAsStr[i] != ' ' && startX == -1) { startX = i; }

			if (rowAsStr[i] != ' ') { endX = i; }

			if (leftMostX == -1) { leftMostX = startX; }
			if (rightMostX == -1) { rightMostX = endX; }
			if (topMostPoint == -1 && rowAsStr[i] != ' ') { topMostPoint = yIndex; }
	
		}

		if (startX < leftMostX && startX != -1) { leftMostX = startX; }
		if (endX > rightMostX) { rightMostX = endX; }
		
		hitbox.rowStartX.push_back(startX);
		hitbox.rowEndX.push_back(endX);
		hitbox.solidRowLength.push_back(endX - startX);
	}

	hitbox.leftMostPoint = leftMostX;
	hitbox.rightMostPoint = rightMostX;
	hitbox.topMostPoint = topMostPoint;
	hitbox.bottomMostPoint = sprite.size();

	return hitbox;
}
