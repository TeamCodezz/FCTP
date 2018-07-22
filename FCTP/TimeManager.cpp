#include "TimeManager.h"

Time::Time()
{
	time_starting_point = std::chrono::steady_clock::now();
}

Time::~Time()
{

}

double Time::GetTime()
{
	std::chrono::duration<double> duration = std::chrono::steady_clock::now() - time_starting_point;
	return duration.count();
}

void Time::StartTimeMeasure()
{
	time_measure_point_1 = std::chrono::steady_clock::now();
}

void Time::EndTimeMeasure()
{
	time_measure_point_2 = std::chrono::steady_clock::now();
}

double Time::GetTimeMeasure()
{
	std::chrono::duration<double> duration = time_measure_point_2 - time_measure_point_1;
	return duration.count();
}