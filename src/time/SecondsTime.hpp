#ifndef __SECONDSTIME_CLASS__
#define __SECONDSTIME_CLASS__

#include <string>

class SecondsTime
{
	public:
		SecondsTime(float seconds);
		std::string toString() const;
		float getSeconds() const;
	private:
		float seconds;
};

#endif
