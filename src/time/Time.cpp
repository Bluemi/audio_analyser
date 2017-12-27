#include "Time.hpp"

#include <cmath>

namespace analyser {
	Time Time::from_number_of_samples(size_t number_of_samples, unsigned int samplerate)
	{
		return Time(number_of_samples, samplerate);
	}

	Time Time::from_seconds(double seconds, unsigned int samplerate)
	{
		return Time(seconds * samplerate, samplerate);
	}

	size_t Time::seconds_to_number_of_samples(double seconds, unsigned int samplerate)
	{
		return (size_t)std::abs(seconds * samplerate);
	}

	double Time::number_of_samples_to_seconds(size_t number_of_samples, unsigned int samplerate)
	{
		return number_of_samples / (double)samplerate;
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
