#include "Channel.hpp"

namespace analyser {
	Channel::Block::Block()
	{}

	Channel::Block::Block(const BufferSection& buffer_section)
		: buffer_section_(buffer_section)
	{}

	float Channel::Block::operator[](size_t index) const
	{
		return *(buffer_section_.get_data() + index);
	}

	bool Channel::Block::get_subsample(size_t index, float* subsample) const
	{
		bool success = (index < buffer_section_.get_size());
		if (success) {
			*subsample = (*this)[index];
		}
		return success;
	}

	const float* Channel::Block::get_samples() const
	{
		return buffer_section_.get_data();
	}

	size_t Channel::Block::get_number_of_samples() const
	{
		return buffer_section_.get_size();
	}

	bool Channel::Block::is_empty() const
	{
		return buffer_section_.is_empty();
	}

	ChannelIterator Channel::Block::begin() const
	{
		return buffer_section_.get_data();
	}

	ChannelIterator Channel::Block::end() const
	{
		return buffer_section_.get_data() + buffer_section_.get_size();
	}

	ChannelIterator Channel::Block::get_iterator_at_sample(size_t index) const
	{
		return buffer_section_.get_data() + index;
	}
}
