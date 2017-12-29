#include "AudioBuffer.hpp"

namespace analyser {
	AudioBuffer::Iterator::Iterator()
		: samples_(nullptr), number_of_channels_(0)
	{}

	AudioBuffer::Iterator::Iterator(float* samples, size_t initial_offset, unsigned int number_of_channels)
		: samples_(samples + initial_offset * number_of_channels), number_of_channels_(number_of_channels)
	{}

	float AudioBuffer::Iterator::get_subsample(const unsigned int channel_index) const
	{
		return *(this->samples_ + channel_index);
	}

	void AudioBuffer::Iterator::set_subsample(const unsigned int channel_index, const float sample)
	{
		*(this->samples_ + channel_index) = sample;
	}

	bool AudioBuffer::Iterator::operator==(const AudioBuffer::Iterator& other_iterator) const
	{
		return this->samples_ == other_iterator.samples_;
	}

	bool AudioBuffer::Iterator::operator!=(const AudioBuffer::Iterator& other_iterator) const
	{
		return this->samples_ != other_iterator.samples_;
	}

	bool AudioBuffer::Iterator::operator<(const AudioBuffer::Iterator& other_iterator) const
	{
		return this->samples_ < other_iterator.samples_;
	}

	bool AudioBuffer::Iterator::operator>(const AudioBuffer::Iterator& other_iterator) const
	{
		return this->samples_ > other_iterator.samples_;
	}

	bool AudioBuffer::Iterator::operator<=(const AudioBuffer::Iterator& other_iterator) const
	{
		return this->samples_ <= other_iterator.samples_;
	}

	bool AudioBuffer::Iterator::operator>=(const AudioBuffer::Iterator& other_iterator) const
	{
		return this->samples_ >= other_iterator.samples_;
	}

	const Sample AudioBuffer::Iterator::operator*() const
	{
		return Sample(samples_, this->number_of_channels_);
	}

	const Sample AudioBuffer::Iterator::operator->() const
	{
		return *(*this);
	}

	Sample AudioBuffer::Iterator::operator++(int)
	{
		Sample sample = *(*this);
		samples_ += number_of_channels_;
		return sample;
	}


	Sample AudioBuffer::Iterator::operator++()
	{
		samples_ += number_of_channels_;
		return *(*this);
	}

	Sample AudioBuffer::Iterator::operator--(int)
	{
		Sample sample = *(*this);
		samples_ -= number_of_channels_;
		return sample;
	}

	Sample AudioBuffer::Iterator::operator--()
	{
		samples_ -= number_of_channels_;
		return *(*this);
	}


	void AudioBuffer::Iterator::operator+=(int step)
	{
		samples_ += (number_of_channels_ * step);
	}

	void AudioBuffer::Iterator::operator-=(int step)
	{
		samples_ -= (number_of_channels_ * step);
	}

	Sample AudioBuffer::Iterator::operator[](int index) const
	{
		float* samples = samples_ + (number_of_channels_ * index);
		return Sample(samples, number_of_channels_);
	}

	AudioBuffer::Iterator operator+(AudioBuffer::Iterator iterator, int step)
	{
		iterator += step;
		return iterator;
	}

	AudioBuffer::Iterator operator+(int step, AudioBuffer::Iterator iterator)
	{
		iterator += step;
		return iterator;
	}

	AudioBuffer::Iterator operator-(AudioBuffer::Iterator iterator, int step)
	{
		iterator -= step;
		return iterator;
	}
}
