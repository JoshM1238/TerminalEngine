#include "PlayerObject.h"


ObjectManager::Object& PlayerObject::initPlayerObject(const std::vector<std::string>& playerSprite, const std::array<int, 2>& playerSpawnPoint) {

	GeneralObject playerObject;

	// The player object is screen confined by default
	// This may change in a future version of this engine
	

	return playerObject.initializeObject(playerSprite, playerSpawnPoint, true);
}
