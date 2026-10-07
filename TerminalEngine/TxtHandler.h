#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <cctype>

class TxtHandler {

private:
	struct ConfigVars {

		std::string pathToSprite;
		std::array<int, 2> spawnPoint;
		const bool screenConfined;
		int hitPoints = 1;
		int objectLayer = 1;
	};

public:

	bool isUnsignedInt(const std::string& value);
	bool isSignedInt(const std::string& value);
	bool isInt(const std::string& value);
	bool isBool(const std::string& line);
	bool isValidPath(const std::string& path);
	bool isVectorOfInt(const std::string& line);
	bool isVectorOfStr(const std::string& line);

	std::vector<std::string> parseSprite(std::string filePath);

	ConfigVars parseObjectConfig(std::string pathToConfig);

};
