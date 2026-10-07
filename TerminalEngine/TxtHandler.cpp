#include "TxtHandler.h"

// ********** FINISH WRITING THE CONFIG PARSER **********
// SEE PARSEOBJECTCONFIG() FOR NEXT STEPS


// Checks whether or not a passed in string is an unsigned integer
bool TxtHandler::isUnsignedInt(const std::string& value){

	if (value.empty()) { return false; }

	for (size_t i = 0; i < value.size(); i++) {
		if (!std::isdigit(value[i])) { return false; }
	}

	return true;
}


// Check whether or not a passed in string is a signed integer
bool TxtHandler::isSignedInt(const std::string& value) {
	
	if (value.empty()) { return false; }
	if (value.size() == 1) { return false; }
	if (value[0] != '-') { return false; }

	for (size_t i = 1; i < value.size(); i++) {
		if (!std::isdigit(value[i])) { return false; }
	}

	return true;
}


// Checks whether or not a passed in value is an integer, regardless of whether or not it is signed
bool TxtHandler::isInt(const std::string& value) {

	if (value.empty()) { return false; }

	for (size_t i = 0; i < value.size(); i++) {
		if (i == 0 && value[i] == '-') { continue; }
		if (!std::isdigit(value[i])) { return false; }
	}

	return true;
}



// Returns true if the passed in value is either "true" or "false". This function is not case sensitive
bool TxtHandler::isBool(const std::string& line) {
	size_t valueStart = line.find_first_not_of(' ');
	if (valueStart == std::string::npos) { return false; }
	size_t valueEnd = line.find_last_not_of(' ');

	std::string subline = line.substr(valueStart, valueEnd - valueStart);
	
	for (char& c : subline) {
		c = std::tolower(c);
	}

	return (subline == "true" || subline == "false");
}



// Tests whether a path is valid by opening the location file
bool TxtHandler::isValidPath(const std::string& path) {
	
	std::ifstream file(path);
	if (!file.is_open()) { return false;}
	file.close();
	return true;
}


// Verifies that a passed in string can be converted into a valid vector (or array) of ints
bool TxtHandler::isVectorOfInt(const std::string& line) {

	if (line.find(',') == std::string::npos) { return false; }

	std::vector<size_t> commasPos;
	for (size_t i = 0; i < line.size(); i++){
		if (line[i] == ',') { 
			commasPos.push_back(i);
			continue; 
		}

		if (!isdigit(line[i]) && line[i] != ' ') { return false; }
	}

	std::string firstSection = line.substr(0, commasPos[0]);
	size_t firstValueStart = firstSection.find_first_not_of(' ');
	size_t firstValueEnd = firstSection.find_last_not_of(' ');

	if (firstValueStart == std::string::npos || firstValueEnd == std::string::npos) { return false; }

	std::string firstValue = firstSection.substr(firstValueStart, firstValueEnd - firstValueStart + 1);

	if (!TxtHandler::isInt(firstValue)) { return false; }

	for (size_t i = 0; i + 1 < commasPos.size(); i++) {
		
		size_t spacesToNext = commasPos[i + 1] - commasPos[i];
		if (spacesToNext < 2) { return false; }
		
		std::string subLine = line.substr(commasPos[i] + 1, spacesToNext - 1);

		size_t valueStart = subLine.find_first_not_of(' ');
		size_t valueEnd = subLine.find_last_not_of(' ');
		if (valueStart == std::string::npos) { return false; }
		if (!TxtHandler::isInt(subLine.substr(valueStart, valueEnd - valueStart + 1))) { return false; }
	}
	
	std::string lastSection = line.substr(commasPos.back() + 1);
	size_t lastValueStart = lastSection.find_first_not_of(' ');
	size_t lastValueEnd = lastSection.find_last_not_of(' ');
	if (lastValueStart == std::string::npos || lastValueEnd == std::string::npos) { return false; }
	std::string lastValue = lastSection.substr(lastValueStart, lastValueEnd - lastValueStart + 1);

	if (!TxtHandler::isInt(lastValue)) { return false; }

	return true;
}



// Returns whether or not a given string can be converted into a vector/array of strings
bool TxtHandler::isVectorOfStr(const std::string& line) {

	std::vector<size_t> commasPos;
	for (size_t i = 0; i < line.size(); i++) {
		if (line[i] == ',') {
			commasPos.push_back(i);
		}
	}

	// Checks the front of the string
	if (commasPos.empty()) { return false; }
	if (commasPos[0] == 0) { return false; }

	if (line.substr(0, commasPos[0]).find_first_not_of(' ') == std::string::npos) { return false; }

	// Checks the middle of the string
	for (size_t i = 0; i < commasPos.size() - 1; i++) {
		if (line.substr(commasPos[i] + 1, commasPos[i + 1] - commasPos[i] - 1).find_first_not_of(' ') == std::string::npos) { 
			return false; 
		}
	}

	// Check the end of the string
	if (line.substr(commasPos.back() + 1).find_first_not_of(' ') == std::string::npos) { return false; }

	return true;
}



// Parses a sprite, line-by-line, from a text file
std::vector<std::string> TxtHandler::parseSprite(std::string filePath){

	std::ifstream file(filePath);

	if (!file.is_open()) { std::cerr << "Error: Failed to open sprite file at " << filePath; }

	std::string line;
	std::vector<std::string> sprite;

	while (std::getline(file, line)) {
		sprite.push_back(line);
	}

	return sprite;
}




// THE IDEA BEHIND THIS FUNCTION IS THAT, USING THE ABOVE FUNCTIONS WHEN NECESSARY, A PATH TO A CONFIG FILE WILL BE PASSED IN
// AND, IF THE CONFIG IS IN THE PROPER FORMAT, AND HAS VALID VALUES, A STRUCT CONTAINING ALL OF THE VALUES NEEDED FOR AN OBJECT'S
// CONFIG WILL BE RETURNED. THE RETURNED STRUCT WILL THEN BE USED TO INITIALIZE THE OBJECT USING THE INITIALIZEOBJECT() FUNCTION
// IN THE GENEREALOBJECT{} CLASS.
// THIS FUNCTION REMAINS INCOMPLETE, AND NEEDS HEAVY REVISION DUE TO THE FACT THAT, WHAT EXISTS SO FAR, WAS WRITEN BEFORE THE ABOVE
// SUPPORTING FUNCTIONS.
TxtHandler::ConfigVars TxtHandler::parseObjectConfig(std::string pathToConfig) {
	
	std::string line;

	std::vector<std::string> settings;
	std::ifstream expectedSettings("../Configs/ExpectedSettings.txt");

	if (!expectedSettings.is_open()) { std::cerr << "Error: failed to open config file at '/Configs/ExpectedSettings.txt' "; }

	while (std::getline(expectedSettings, line)) {
		settings.push_back(line);
	}

	expectedSettings.close();

	std::ifstream file(pathToConfig);

	if (!file.is_open()) { std::cerr << "Error: failed to open config file at " << pathToConfig; }

	for (auto& setting : settings) {

		while (std::getline(file, line)) {

			int start = line.find(setting);
			if (start == std::string::npos) { continue; }

			int colonPos = line.find(":");
			if (colonPos == std::string::npos) { std::cerr << "Error: issue with config setting: " << setting; }
			int valueStart = colonPos + 1;

			std::string value = line.substr(valueStart);

		}
	}

}
