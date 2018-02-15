#include "SampleBuffer.hpp"

namespace analyser {
	SampleBuffer::Iterator::Iterator()
		: samples_(nullptr), number_of_channels_(0)
	{}

	SampleBuffer::Iterator::Iterator(float* samples, size_t initial_offset, unsigned int number_of_channels)
		: samples_(samples + initial_offset * number_of_channels), number_of_channels_(number_of_channels)
	{}

	float SampleBuffer::Iterator::get_subsample(const unsigned int channel_index) const
	{
		return *(this->samples_ + channel_index);
	}

	void SampleBuffer::Iterator::set_subsample(const unsigned int channel_index, const float sample)
	{
		*(this->samples_ + channel_index) = sample;
	}

	bool SampleBuffer::Iterator::operator==(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->samples_ == other_iterator.samples_;
	}

	bool SampleBuffer::Iterator::operator!=(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->samples_ != other_iterator.samples_;
	}

	bool SampleBuffer::Iterator::operator<(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->samples_ < other_iterator.samples_;
	}

	bool SampleBuffer::Iterator::operator>(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->samples_ > other_iterator.samples_;
	}

	bool SampleBuffer::Iterator::operator<=(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->samples_ <= other_iterator.samples_;
	}

	bool SampleBuffer::Iterator::operator>=(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->samples_ >= other_iterator.samples_;
	}

	const Sample SampleBuffer::Iterator::operator*() const
	{
		return Sample(samples_, this->number_of_channels_);
	}

	const Sample SampleBuffer::Iterator::operator->() const
	{
		return *(*this);
	}

	Sample SampleBuffer::Iterator::operator++(int)
	{
		Sample sample = *(*this);
		samples_ += number_of_channels_;
		return sample;
	}


	Sample SampleBuffer::Iterator::operator++()
	{
		samples_ += number_of_channels_;
		return *(*this);
	}

	Sample SampleBuffer::Iterator::operator--(int)
	{
		Sample sample = *(*this);
		samples_ -= number_of_channels_;
		return sample;
	}

	Sample SampleBuffer::Iterator::operator--()
	{
		samples_ -= number_of_channels_;
		return *(*this);
	}


	void SampleBuffer::Iterator::operator+=(int step)
	{
		samples_ += (number_of_channels_ * step);
	}

	void SampleBuffer::Iterator::operator-=(int step)
	{
		samples_ -= (number_of_channels_ * step);
	}

	Sample SampleBuffer::Iterator::operator[](int index) const
	{
		float* samples = samples_ + (number_of_channels_ * index);
		return Sample(samples, number_of_channels_);
	}

	SampleBuffer::Iterator operator+(SampleBuffer::Iterator iterator, int step)
	{
		iterator += step;
		return iterator;
	}

	SampleBuffer::Iterator operator-(SampleBuffer::Iterator iterator, int step)
	{
		iterator -= step;
		return iterator;
	}
}
