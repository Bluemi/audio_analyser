#include "AudioBuffer.hpp"

namespace analyser {
	AudioBuffer::Iterator::Iterator()
		: samples_(nullptr), position_(0), number_of_channels_(0), number_of_samples_(0)
	{}

	AudioBuffer::Iterator::Iterator(float* samples, size_t initial_offset, unsigned int number_of_channels, size_t number_of_samples)
		: samples_(samples), position_(initial_offset * number_of_channels), number_of_channels_(number_of_channels), number_of_samples_(number_of_samples)
	{}

	bool AudioBuffer::Iterator::is_end() const
	{
		return (position_ >= number_of_samples_);
	}

	float AudioBuffer::Iterator::get_subsample(const int channel_index) const
	{
		return *(this->samples_ + (this->position_ * this->number_of_channels_ + channel_index));
	}

	bool AudioBuffer::Iterator::operator==(const AudioBuffer::Iterator& iterator2) const
	{
		bool equal = true;
		if (this->samples_ != iterator2.samples_) {
			equal = false;
		} else if (this->position_ != iterator2.position_) {
			if ((!this->is_end()) || (!iterator2.is_end())) {
				equal = false;
			}
		}

		return equal;
	}

	bool AudioBuffer::Iterator::operator!=(const AudioBuffer::Iterator& other_iterator) const
	{
		return !(*this == other_iterator);
	}

	bool AudioBuffer::Iterator::operator<(const AudioBuffer::Iterator& iterator) const
	{
		return this->position_ < iterator.position_;
	}

	bool AudioBuffer::Iterator::operator>(const AudioBuffer::Iterator& iterator) const
	{
		return this->position_ > iterator.position_;
	}

	bool AudioBuffer::Iterator::operator<=(const AudioBuffer::Iterator& iterator) const
	{
		return this->position_ <= iterator.position_;
	}

	bool AudioBuffer::Iterator::operator>=(const AudioBuffer::Iterator& iterator) const
	{
		return this->position_ >= iterator.position_;
	}

	const Sample AudioBuffer::Iterator::operator*() const
	{
		float* samples = this->samples_ + (this->position_ * this->number_of_channels_);
		return Sample(samples, this->number_of_channels_);
	}

	const Sample AudioBuffer::Iterator::operator->() const
	{
		float* samples = this->samples_ + (this->position_ * this->number_of_channels_);
		return Sample(samples, this->number_of_channels_);
	}

	Sample AudioBuffer::Iterator::operator++(int)
	{
		Sample sample = *(*this);
		position_++;
		return sample;
	}


	Sample AudioBuffer::Iterator::operator++()
	{
		position_++;
		return *(*this);
	}

	Sample AudioBuffer::Iterator::operator--(int)
	{
		Sample sample = *(*this);
		position_--;
		return sample;
	}

	Sample AudioBuffer::Iterator::operator--()
	{
		position_--;
		return *(*this);
	}


	void AudioBuffer::Iterator::operator+=(int step)
	{
		position_ += step;
	}

	void AudioBuffer::Iterator::operator-=(int step)
	{
		position_ -= step;
	}

	AudioBuffer::Iterator AudioBuffer::Iterator::operator+(const AudioBuffer::Iterator& summand) const
	{
		AudioBuffer::Iterator iterator(*this);
		iterator.position_ += summand.position_;
		return iterator;
	}

	AudioBuffer::Iterator AudioBuffer::Iterator::operator-(const AudioBuffer::Iterator& minuend) const
	{
		AudioBuffer::Iterator iterator(*this);
		iterator.position_ -= minuend.position_;
		return iterator;
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
