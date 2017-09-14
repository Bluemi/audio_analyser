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

unsigned int Time::getFramerate() const
{
	return framerate;
}

size_t Time::getFrameCount() const
{
	return frameCount;
}

float Time::getSeconds() const
{
	return frameCount / (float)framerate;
}

Time Time::fromFrameTime(const FrameTime &frameTime, unsigned int framerate)
{
	return Time(frameTime.getFrameCount(), framerate);
}

Time Time::fromSecondsTime(const SecondsTime &secondsTime, unsigned int framerate)
{
	return Time(secondsTime.getSeconds() * framerate, framerate);
}

Time Time::fromFrameCount(size_t frameCount, unsigned int framerate)
{
	return Time(frameCount, framerate);
}

Time Time::fromSeconds(float seconds, unsigned int framerate)
{
	return Time(seconds * framerate, framerate);
}
