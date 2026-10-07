#pragma once

#include <vector>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <chrono>

#include "GetHitbox.h"
#include "GameClock.h"

class ObjectManager {

public:

	struct Object {

		GetHitbox::Hitbox hitbox;
		std::array<int, 2> coordsXY;
		std::array<int, 2> previousCoordsXY;
		std::vector<std::string> objectSprite;
		std::array<int, 2> spawnPoint;
		bool screenConfined;
		bool hasMoved;
		int objectID;
		int hitPoints;
		int objectLayer;
	};

	static std::unordered_map<int, Object> objectList;
	static std::vector<int> printOrder;   // stores the keys of the object list in the order in which objects on the object list should be printed
	static long long printOrderRefreshRate;
	static long long lastPrintOrderRefresh;

	static void refreshPrintOrder();
	static void setPrintOrderRefreshRate(int rateInMils = 100);
	static bool isTimeToRefreshPrintOrder();

};