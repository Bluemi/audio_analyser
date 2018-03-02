#include "FrequencyBlock.hpp"

namespace analyser {
	FrequencyBlock::FrequencyBlock() {}

	FrequencyBlock::FrequencyBlock(const BufferSection& buffer_section)
		: buffer_section_(buffer_section)
	{}

	float* FrequencyBlock::get_frequencies() const
	{
		return buffer_section_.get_data();
	}

	size_t FrequencyBlock::get_size() const
	{
		return buffer_section_.get_size();
	}
}
