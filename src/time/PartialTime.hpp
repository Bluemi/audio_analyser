#ifndef __PARTIALTIME_CLASS__
#define __PARTIALTIME_CLASS__

#include <variant>

namespace analyser {
	class Time;

	class PartialTime
	{
		public:
			PartialTime(double seconds);
			PartialTime(size_t number_of_samples);
			PartialTime(const Time& time);

			Time to_time(unsigned int samplerate) const;
		private:
			std::variant<double, size_t> time_value_;
	};
}

#endif
