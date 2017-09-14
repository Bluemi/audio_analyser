#include "Time.hpp"

Time::Time(size_t frameCount, unsigned int framerate)
	: frameCount(frameCount), framerate(framerate)
{}

FrameTime Time::toFrameTime() const
{
	return FrameTime::fromFrameCount(frameCount);
}

SecondsTime Time::toSecondsTime() const
{
	return SecondsTime(frameCount / (float)framerate);
}

Time Time::fromFrameTime(const FrameTime &frameTime, unsigned int framerate)
{
	return Time(frameTime.getFrameCount(), framerate);
}

Time Time::fromSecondsTime(const SecondsTime &secondsTime, unsigned int framerate)
{
	return Time(secondsTime.getSeconds() * framerate, framerate);
}
