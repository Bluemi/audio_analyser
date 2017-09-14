#include "SecondsTime.hpp"

SecondsTime::SecondsTime(float seconds)
	: seconds(seconds)
{}

float SecondsTime::getSeconds() const
{
	return seconds;
}

std::string SecondsTime::toString() const
{
	const int hours = (int)seconds / 3600;
	const int minutes = ((int)seconds / 60) % 60;
	const int secs = (int)seconds % 60;
	const int millis = (int)(seconds * 1000) % 1000;
	return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(secs) + "." + std::to_string(millis);
}
