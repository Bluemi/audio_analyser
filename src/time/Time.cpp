#include "Time.hpp"

namespace analyser {
	Time Time::from_number_of_samples(size_t number_of_samples, unsigned int samplerate)
	{
		return Time(number_of_samples, samplerate);
	}

	Time Time::from_seconds(double seconds, unsigned int samplerate)
	{
		return Time(seconds * samplerate, samplerate);
	}

	Time::Time(size_t number_of_samples, unsigned int samplerate)
		: number_of_samples_(number_of_samples), samplerate_(samplerate)
	{}

	unsigned int Time::get_samplerate() const
	{
		return samplerate_;
	}

	size_t Time::get_number_of_samples() const
	{
		return number_of_samples_;
	}

	double Time::get_seconds() const
	{
		return number_of_samples_ / (double)samplerate_;
	}
}
