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

			static size_t seconds_to_number_of_samples(double seconds, unsigned int samplerate);
			static double number_of_samples_to_seconds(size_t number_of_samples, unsigned int samplerate);

			unsigned int get_samplerate() const;
			size_t get_number_of_samples() const;
			double get_seconds() const;

			Time plus_seconds(double seconds) const;
			Time minus_seconds(double seconds) const;

			Time plus_number_of_samples(size_t number_of_samples) const;
			Time minus_number_of_samples(size_t number_of_samples) const;

			Time operator+(const Time& time) const;
			Time operator-(const Time& time) const;

			void operator+=(const Time& time);
			void operator-=(const Time& time);

			bool operator<(const Time& time) const;
			bool operator>(const Time& time) const;
			bool operator<=(const Time& time) const;
			bool operator>=(const Time& time) const;
			bool operator==(const Time& time) const;
			bool operator!=(const Time& time) const;

		private:
			Time(size_t number_of_samples, unsigned int samplerate);
			size_t number_of_samples_;
			unsigned int samplerate_;
	};

}

#endif
