#include "FrameTime.hpp"

FrameTime FrameTime::fromSeconds(float seconds, unsigned int framerate)
{
	return FrameTime(seconds * framerate);
}

FrameTime FrameTime::fromSecondsTime(const SecondsTime &secondsTime, unsigned int framerate)
{
	return FrameTime(secondsTime.getSeconds() * framerate);
}

FrameTime FrameTime::fromFrameCount(size_t frameCount)
{
	return FrameTime(frameCount);
}

FrameTime::FrameTime(size_t frameCount)
	: frameCount(frameCount)
{ }

SecondsTime FrameTime::toSecondsTime(unsigned int framerate) const
{
	return SecondsTime(frameCount / (float)framerate);
}

float FrameTime::getSeconds(unsigned int framerate) const
{
	return frameCount / (float)framerate;
}

size_t FrameTime::getFrameCount() const
{
	return frameCount;
}

size_t FrameTime::getSampleCount(unsigned int channelCount) const
{
	return frameCount * channelCount;
}
