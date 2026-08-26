#pragma once

#include "GeneralObject.h"
#include "ObjectManager.h"


class PlayerObject {

public:
	
	ObjectManager::Object& initPlayerObject(const std::vector<std::string>& playerSprite, const std::array<int, 2>& playerSpawnPoint);

};