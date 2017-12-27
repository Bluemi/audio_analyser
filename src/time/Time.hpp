#ifndef __TIME_CLASS__
#define __TIME_CLASS__

// for size_t
#include <cstddef>

namespace analyser {
	class Time
	{
		public:
			static Time from_number_of_samples(size_t number_of_samples, unsigned int samplerate);
			static Time from_seconds(double seconds, unsigned int samplerate);

			static size_t seconds_to_number_of_samples(float seconds, unsigned int samplerate);
			static float number_of_samples_to_seconds(size_t number_of_samples, unsigned int samplerate);

			unsigned int get_samplerate() const;
			size_t get_number_of_samples() const;
			double get_seconds() const;
		private:
			Time(size_t number_of_samples, unsigned int samplerate);
			size_t number_of_samples_;
			unsigned int samplerate_;
	};

}

#endif
