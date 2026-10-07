#include "GameClock.h"
#include <chrono>


// Checks the time elapsed between two points against a target elapsed time
bool GameClock::checkElapsedMills(const Clock::time_point& pointA, const Clock::time_point& pointB, const long long& targetMills) {

	long long millsElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(pointB - pointA).count();
	if (millsElapsed >= targetMills) return true;

	return false;
}

// Returns the timepoint at which this was called
long long GameClock::now() {
	std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch()).count();
}
