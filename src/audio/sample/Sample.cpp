#include "Sample.hpp"

#include <cmath>

namespace analyser {
	Sample::Sample(std::vector<float> samples)
		: samples_(samples)
	{}

	Sample::Sample() {}

	void Sample::invalidate() {
		samples_.clear();
	}

	bool Sample::is_empty() const { return samples_.empty(); }

	bool Sample::get_subsample(unsigned int channel_index, float* subsample) const
	{
		bool success = false;
		if (channel_index < get_number_of_channels()) {
			*subsample = samples_[channel_index];
			success = true;
		} else {
			*subsample = NAN;
		}
		return success;
	}

	unsigned int Sample::get_number_of_channels() const {
		return samples_.size();
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
