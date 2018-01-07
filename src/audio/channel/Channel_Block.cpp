#include "Channel.hpp"

namespace analyser {
	Channel::Block::Block()
	{}

	Channel::Block::Block(const Buffer& buffer)
		: buffer_(buffer)
	{}

	float& Channel::Block::operator[](size_t index) const
	{
		return *(buffer_.get_samples() + index);
	}

	bool Channel::Block::set_subsample(size_t index, float subsample)
	{
		bool success = (index < buffer_.get_number_of_samples());
		if (success) {
			*(buffer_.get_samples() + index) = subsample;
		}
		return success;
	}

	bool Channel::Block::get_subsample(size_t index, float* subsample) const
	{
		bool success = (index < buffer_.get_number_of_samples());
		if (success) {
			*subsample = (*this)[index];
		}
		return success;
	}

	float* Channel::Block::get_samples() const
	{
		return buffer_.get_samples();
	}

	size_t Channel::Block::get_number_of_samples() const
	{
		return buffer_.get_number_of_samples();
	}

	bool Channel::Block::is_empty() const
	{
		return buffer_.is_empty();
	}

	Channel::Iterator Channel::Block::begin() const
	{
		return Channel::Iterator(buffer_.get_samples(), 0);
	}

	Channel::Iterator Channel::Block::end() const
	{
		return Channel::Iterator(buffer_.get_samples(), buffer_.get_number_of_samples());
	}

	Channel::Iterator Channel::Block::get_iterator_at_sample(size_t index) const
	{
		return Channel::Iterator(buffer_.get_samples(), index);
	}
}
