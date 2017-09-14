#ifndef __FRAMETIME_CLASS__
#define __FRAMETIME_CLASS__

#include <cstring>

#include "SecondsTime.hpp"

class FrameTime
{
	public:
		static FrameTime fromSeconds(float seconds, unsigned int framerate);
		static FrameTime fromSecondsTime(const SecondsTime &secondsTime, unsigned int framerate);
		static FrameTime fromFrameCount(size_t frameCount);

		SecondsTime toSecondsTime(unsigned int framerate) const;
		float getSeconds(unsigned int framerate) const;
		size_t getFrameCount() const;
		size_t getSampleCount(unsigned int channelCount) const;
	private:
		FrameTime(size_t frameCount);
		size_t frameCount;
};

#endif
