#include "ChannelBlock.hpp"

namespace analyser {
	ChannelBlock::ChannelBlock()
	{}

	ChannelBlock::ChannelBlock(const BufferSection& buffer_section)
		: buffer_section_(buffer_section)
	{}

	float ChannelBlock::operator[](size_t index) const
	{
		return *(buffer_section_.get_data() + index);
	}

	bool ChannelBlock::get_subsample(size_t index, float* subsample) const
	{
		bool success = (index < buffer_section_.get_size());
		if (success) {
			*subsample = (*this)[index];
		}
		return success;
	}

	const float* ChannelBlock::get_samples() const
	{
		return buffer_section_.get_data();
	}

	size_t ChannelBlock::get_number_of_samples() const
	{
		return buffer_section_.get_size();
	}

	bool ChannelBlock::is_empty() const
	{
		return buffer_section_.is_empty();
	}

	ChannelIterator ChannelBlock::begin() const
	{
		return buffer_section_.get_data();
	}

	ChannelIterator ChannelBlock::end() const
	{
		return buffer_section_.get_data() + buffer_section_.get_size();
	}

	ChannelIterator ChannelBlock::get_iterator_at_sample(size_t index) const
	{
		return buffer_section_.get_data() + index;
	}
}
