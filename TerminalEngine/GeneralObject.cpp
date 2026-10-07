#include "GeneralObject.h"

// Initializes all values of the Object struct for the passed in object
ObjectManager::Object& GeneralObject::initializeObject(
	const std::vector<std::string>& objectSprite, 
	const std::array<int, 2>& spawnPoint, 
	const bool screenConfined, 
	int hitPoints,
	int objectLayer) {

	ObjectManager::Object object;
	const Screen::ScreenDimensions& screen = Screen::getScreenSize();

	object.objectSprite = objectSprite;
	object.hitbox = GetHitbox::getSpriteHitbox(objectSprite);
	object.hasMoved = true;   // initialize to true so that it is printed the first time
	object.screenConfined = screenConfined;   // is the object confined to the dimensions of the screen? For instance, the player object probably is
	object.hitPoints = hitPoints;
	object.objectLayer = objectLayer;

	if (spawnPoint[0] > screen.playableScreenEnd) { object.spawnPoint[0] = screen.playableScreenEnd; }
	else if (spawnPoint[0] < screen.playableScreenStart) { object.spawnPoint[0] = screen.playableScreenStart; }
	else { object.spawnPoint[0] = spawnPoint[0]; }

	if (spawnPoint[1] > screen.playableScreenBottom) { object.spawnPoint[1] = screen.playableScreenBottom; }
	else if (spawnPoint[1] < screen.playableScreenTop) { object.spawnPoint[1] = screen.playableScreenTop; }
	else { object.spawnPoint[1] = spawnPoint[1]; }

	object.coordsXY = spawnPoint;   // initialize to the set spawn point. Will change as object moves
	object.previousCoordsXY = spawnPoint;   // also temporarily initialize the previous coords to the spawn point

	// Find the largest key in the object list so that a new unique key can be created for the new object
	int newKey = 0;
	for (const auto& element : ObjectManager::objectList) {
		if (element.first >= newKey) { newKey = element.first + 1; }
	}

	object.objectID = newKey;
	ObjectManager::objectList.insert({ newKey, object });   // add the new object to the object list with a unique key
	ObjectManager::refreshPrintOrder();

	return ObjectManager::objectList.at(newKey);
}


// Removes passed in object from the print order and object list
void GeneralObject::deleteObject(const ObjectManager::Object& object) {

	for (int i = 0; i < ObjectManager::printOrder.size(); i++) {
		if (ObjectManager::printOrder[i] == object.objectID) { 
			ObjectManager::printOrder.erase(ObjectManager::printOrder.begin() + i);
			break;
		}
	}

	ObjectManager::objectList.erase(object.objectID);

	return;
}





void GeneralObject::moveObject(ObjectManager::Object& object, const std::array<int, 2>& movement, const Screen::ScreenDimensions& screen) {

	int xAmount = movement[0];   // the first element of the movement array is how much the object should move on the X axis
	int yAmount = movement[1];   // the second element of the movement array is how much the object should move on the y axis

	int& posX = object.coordsXY[0];
	int& posY = object.coordsXY[1];
	int newXPos = posX + xAmount;
	int newYPos = posY + yAmount;

	int maxX = screen.playableScreenEnd - 1 - object.hitbox.rightMostPoint;
	int minX = screen.playableScreenStart - object.hitbox.leftMostPoint;
	int maxY = screen.playableScreenBottom - 1 - object.hitbox.bottomMostPoint;
	int minY = screen.playableScreenTop - object.hitbox.topMostPoint;

	if (xAmount != 0 || yAmount != 0) { 
		object.hasMoved = true;
		if (ObjectManager::isTimeToRefreshPrintOrder()) { ObjectManager::refreshPrintOrder(); }
	}

	else { 
		object.hasMoved = false; 
		return;
	}

	if (object.screenConfined) {

		object.previousCoordsXY = { posX, posY };

		if (newXPos > maxX) { posX = maxX; }
		else if (newXPos < minX) { posX = minX; }
		else { posX = newXPos; }

		if (newYPos > maxY) { posY = maxY; }
		else if (newYPos < minY) { posY = minY; }
		else { posY = newYPos; }
	}


	else {
		
		// Standard behavior is that, if an object leaves the screen, it will be deleted
		// This might change in a later version of this engine to allow objects to leave and then return to the screen
		if (newXPos > maxX || newXPos < minX || newYPos > maxY || newYPos < minY) {
			deleteObject(object);
		}

		else {
			object.previousCoordsXY = { posX, posY };
			posX = newXPos;
			posY = newYPos;
		}
	}

	return;
}



