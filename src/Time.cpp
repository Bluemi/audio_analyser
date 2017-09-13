#include "Time.hpp"

Time Time::fromSeconds(const float seconds, const unsigned int framerate)
{
	return Time(seconds*framerate);
}

Time Time::fromFramecount(const float framecount)
{
	return Time(framecount);
}

Time::Time(const size_t framecount)
	: framecount(framecount)
{ }

float Time::getSeconds(const unsigned int framerate) const
{
	return framecount / (float)framerate;
}

size_t Time::getFramecount() const
{
	return framecount;
}

size_t Time::getSampleCount(unsigned int channelcount) const
{
	return framecount * channelcount;
}
