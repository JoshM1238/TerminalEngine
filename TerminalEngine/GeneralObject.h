#pragma once

#include <array>
#include <vector>
#include <string>
#include <algorithm>

#include "ObjectManager.h"
#include "GetHitbox.h"
#include "Screen.h"

class GeneralObject {

private:

public:

	void setPrintOrder();

	// Initializes all of the members of the Object struct
	ObjectManager::Object& initializeObject(const std::vector<std::string>& objectSprite, 
		const std::array<int, 
		2>& spawnPoint, 
		const bool screenConfined, 
		int hitPoints = 1,
		int objectLayer = 1);

	void deleteObject(const ObjectManager::Object& object);

	void moveObject(ObjectManager::Object& object, const std::array<int, 2>& movement, const Screen::ScreenDimensions& screen);
};