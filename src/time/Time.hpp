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
		unsigned int getFramerate() const;
		size_t getFrameCount() const;
		float getSeconds() const;

		static Time fromFrameTime(const FrameTime &frameTime, unsigned int framerate);
		static Time fromSecondsTime(const SecondsTime &secondsTime, unsigned int framerate);

		static Time fromFrameCount(size_t frameCount, unsigned int framerate);
		static Time fromSeconds(float seconds, unsigned int framerate);
	private:
		size_t frameCount;
		unsigned int framerate;
};

#endif
