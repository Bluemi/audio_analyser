#include "Channel.hpp"

namespace analyser {
	Channel::Block::Block()
	{}

	Channel::Block::Block(const Buffer& buffer)
		: buffer_(buffer)
	{}

	float& Channel::Block::operator[](size_t index) const
	{
		return *(buffer_.get_data() + index);
	}

	bool Channel::Block::set_subsample(size_t index, float subsample)
	{
		bool success = (index < buffer_.get_size());
		if (success) {
			*(buffer_.get_data() + index) = subsample;
		}
		return success;
	}

	bool Channel::Block::get_subsample(size_t index, float* subsample) const
	{
		bool success = (index < buffer_.get_size());
		if (success) {
			*subsample = (*this)[index];
		}
		return success;
	}

	float* Channel::Block::get_samples() const
	{
		return buffer_.get_data();
	}

	size_t Channel::Block::get_number_of_samples() const
	{
		return buffer_.get_size();
	}

	bool Channel::Block::is_empty() const
	{
		return buffer_.is_empty();
	}

	ChannelIterator Channel::Block::begin() const
	{
		return buffer_.get_data();
	}

	ChannelIterator Channel::Block::end() const
	{
		return buffer_.get_data() + buffer_.get_size();
	}

	ChannelIterator Channel::Block::get_iterator_at_sample(size_t index) const
	{
		return buffer_.get_data() + index;
	}

	void Channel::Block::manipulate(std::function<void(float&, size_t, size_t)> function)
	{
		float* samples = buffer_.get_data();
		for (size_t i = 0; i < buffer_.get_size(); i++) {
			function(*samples, i, buffer_.get_size());
			samples++;
		}
	}
}
