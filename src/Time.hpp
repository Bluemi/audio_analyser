#ifndef __TIME_CLASS__
#define __TIME_CLASS__

#include <cstring>

class Time
{
	public:
		static Time fromSeconds(const float seconds, const unsigned int framerate);
		static Time fromFramecount(const float framecount);

		float getSeconds(const unsigned int framerate) const;
		size_t getFramecount() const;
		size_t getSampleCount(unsigned int channelcount) const;
	private:
		Time(const size_t framecount);
		size_t framecount;
};

#endif
