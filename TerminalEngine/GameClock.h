#pragma once

#include <chrono>

class GameClock {
public:

	using Clock = std::chrono::steady_clock;

	static bool checkElapsedMills(const Clock::time_point& pointA , const Clock::time_point& pointB, const long long& targetMills);
};