#include "PartialTime.hpp"

#include <time/Time.hpp>

namespace analyser {
	PartialTime::PartialTime(double seconds)
		: time_value_(seconds)
	{}

	PartialTime::PartialTime(size_t number_of_samples)
		: time_value_(number_of_samples)
	{}

	PartialTime::PartialTime(const Time& time)
		: PartialTime(time.get_number_of_samples())
	{}

	class Overloader {
		public:
			Overloader(unsigned int samplerate)
				: samplerate_(samplerate)
			{}

			Time operator()(double seconds) {
				return Time::from_seconds(seconds, samplerate_);
			}

			Time operator()(size_t number_of_samples) {
				return Time::from_number_of_samples(number_of_samples, samplerate_);
			}
		private:
			unsigned int samplerate_;
	};

	Time PartialTime::to_time(unsigned int samplerate) const
	{
		return std::visit(Overloader(samplerate), time_value_);
	}
}
