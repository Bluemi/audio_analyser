#include "FrequencyBlock.hpp"

namespace analyser {
	FrequencyBlock::FrequencyBlock(const Buffer& buffer, float max_frequency)
		: buffer_(buffer), max_frequency_(max_frequency)
	{}

	float FrequencyBlock::get_frequency(float frequency) const
	{
		unsigned int index = (unsigned int)((frequency / max_frequency_) * buffer_.get_size());
		if (index < buffer_.get_size()) {
			return buffer_[index];
		}
		return 0.f;
	}
}
