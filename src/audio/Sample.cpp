#include "Sample.hpp"

#include <cmath>

namespace analyser {
	Sample::Sample(float* samples, unsigned int number_of_channels)
		: is_empty_(false), samples_(samples), number_of_channels_(number_of_channels)
	{}

	Sample::Sample()
		: is_empty_(true), samples_(nullptr), number_of_channels_(0)
	{}

	void Sample::set(float* samples, unsigned int number_of_channels)
	{
		is_empty_ = false;
		samples_ = samples;
		number_of_channels_ = number_of_channels;
	}

	void Sample::invalidate() {
		is_empty_ = true;
		samples_ = nullptr;
		number_of_channels_ = 0;
	}

	bool Sample::is_empty() const { return is_empty_; }

	bool Sample::get_subsample(unsigned int channel_number, float* subsample) const
	{
		bool success = false;
		if (channel_number < number_of_channels_) {
			*subsample = samples_[channel_number];
			success = true;
		} else {
			*subsample = NAN;
		}
		return success;
	}

	Sample* Sample::operator->()
	{
		return this;
	}

	const Sample* Sample::operator->() const
	{
		return this;
	}
}
