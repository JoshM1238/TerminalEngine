#include "TxtHandler.h"

std::vector<std::string> TxtHandler::parseSprite(std::string filePath){

	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "Error: Failed to open sprite file";
	}

	std::string line;
	std::vector<std::string> sprite;

	while (std::getline(file, line)) {
		sprite.push_back(line);
	}

	return sprite;
}
