#ifndef __TIME_CLASS__
#define __TIME_CLASS__

#include "SecondsTime.hpp"
#include "FrameTime.hpp"

class Time
{
	public:
		Time(size_t frameCount, unsigned int framerate);
		
		FrameTime toFrameTime() const;
		SecondsTime toSecondsTime() const;

		static Time fromFrameTime(const FrameTime &frameTime, unsigned int framerate);
		static Time fromSecondsTime(const SecondsTime &secondsTime, unsigned int framerate);
	private:
		size_t frameCount;
		unsigned int framerate;
};

#endif
