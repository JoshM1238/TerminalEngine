#include "ObjectManager.h"

std::unordered_map<int, ObjectManager::Object> ObjectManager::objectList;
std::vector<int> ObjectManager::printOrder;
long long ObjectManager::printOrderRefreshRate = 100;   // defualts to 100 milliseconds per refresh
long long ObjectManager::lastPrintOrderRefresh = 0;

void ObjectManager::refreshPrintOrder() {

	std::vector<int> order;   // will store the keys of the objectList unordered map in the order that their objects should be printed
	order.reserve(objectList.size());

	for (const auto& element : objectList) {
		order.push_back(element.first);
	}

	std::sort(order.begin(), order.end(), [](int firstKey, int secondKey) {

		int firstY = objectList.at(firstKey).coordsXY[1];
		int secondY = objectList.at(secondKey).coordsXY[1];

		if (firstY == secondY) {
			int firstX = objectList.at(firstKey).coordsXY[0];
			int secondX = objectList.at(secondKey).coordsXY[0];
			return firstX < secondX;
		}

		return firstY < secondY;

		}
	);

	printOrder = order;
	lastPrintOrderRefresh = GameClock::now();


	return;
}


// Sets the time in milliseconds between each automatic print order refresh
// Refresh rate defaults to 100
void ObjectManager::setPrintOrderRefreshRate(int rateInMils){
	printOrderRefreshRate = rateInMils;
	return;
}

// Returns a bool value representing whether or not it is time to refresh the print order
// The returned value is based on the interval set by the setPrintOrderRefreshRate() function
bool ObjectManager::isTimeToRefreshPrintOrder(){
	return GameClock::now() - lastPrintOrderRefresh >= printOrderRefreshRate;
}
