#pragma once

#include <chrono>

class Time
{
public:
	Time();
	virtual ~Time();

	double GetTime();

	void StartTimeMeasure();
	void EndTimeMeasure();
	double GetTimeMeasure();

private:
	std::chrono::steady_clock::time_point time_measure_point_1;
	std::chrono::steady_clock::time_point time_measure_point_2;
	std::chrono::steady_clock::time_point time_starting_point;
};