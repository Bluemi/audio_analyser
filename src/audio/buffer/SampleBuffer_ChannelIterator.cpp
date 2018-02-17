#include "SampleBuffer.hpp"

namespace analyser {
	SampleBuffer::ChannelIterator::ChannelIterator()
		: samples_(nullptr), number_of_channels_(0)
	{}

	SampleBuffer::ChannelIterator::ChannelIterator(float* samples, size_t initial_offset, unsigned int channel_number, unsigned int number_of_channels)
		: samples_(samples + (number_of_channels*initial_offset) + channel_number), number_of_channels_(number_of_channels)
	{}

	bool SampleBuffer::ChannelIterator::operator==(const SampleBuffer::ChannelIterator& iterator) const
	{
		return samples_ == iterator.samples_;
	}

	bool SampleBuffer::ChannelIterator::operator!=(const SampleBuffer::ChannelIterator& iterator) const
	{
		return samples_ != iterator.samples_;
	}

	bool SampleBuffer::ChannelIterator::operator<(const SampleBuffer::ChannelIterator& iterator) const
	{
		return samples_ < iterator.samples_;
	}

	bool SampleBuffer::ChannelIterator::operator>(const SampleBuffer::ChannelIterator& iterator) const
	{
		return samples_ > iterator.samples_;
	}

	bool SampleBuffer::ChannelIterator::operator<=(const SampleBuffer::ChannelIterator& iterator) const
	{
		return samples_ <= iterator.samples_;
	}

	bool SampleBuffer::ChannelIterator::operator>=(const SampleBuffer::ChannelIterator& iterator) const
	{
		return samples_ >= iterator.samples_;
	}

	float& SampleBuffer::ChannelIterator::operator*() const
	{
		return *samples_;
	}

	float SampleBuffer::ChannelIterator::operator++(int)
	{
		float f = *samples_;
		samples_ += number_of_channels_;
		return f;
	}

	float SampleBuffer::ChannelIterator::operator++()
	{
		samples_ += number_of_channels_;
		return *samples_;
	}

	float SampleBuffer::ChannelIterator::operator--(int)
	{
		float f = *samples_;
		samples_ -= number_of_channels_;
		return f;
	}

	float SampleBuffer::ChannelIterator::operator--()
	{
		samples_ -= number_of_channels_;
		return *samples_;
	}

	void SampleBuffer::ChannelIterator::operator+=(int step)
	{
		samples_ += (number_of_channels_ * step);
	}

	void SampleBuffer::ChannelIterator::operator-=(int step)
	{
		samples_ -= (number_of_channels_ * step);
	}

	float& SampleBuffer::ChannelIterator::operator[](int index) const
	{
		return *(samples_ + (number_of_channels_ * index));
	}

	// ChannelIterator Functions
	SampleBuffer::ChannelIterator operator+(SampleBuffer::ChannelIterator iterator, int step)
	{
		iterator += step;
		return iterator;
	}

	SampleBuffer::ChannelIterator operator-(SampleBuffer::ChannelIterator iterator, int step)
	{
		iterator -= step;
		return iterator;
	}
}
