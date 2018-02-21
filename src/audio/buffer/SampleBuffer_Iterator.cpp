#include "SampleBuffer.hpp"

namespace analyser {
	SampleBuffer::Iterator::Iterator() {}

	SampleBuffer::Iterator::Iterator(std::vector<float*> channels, size_t initial_offset)
		: channels_(channels)
	{
		for (auto iter = channels_.begin(); iter != channels_.end(); ++iter) {
			*iter += initial_offset;
		}
	}

	float SampleBuffer::Iterator::get_subsample(const unsigned int channel_index) const
	{
		return *(channels_[channel_index]);
	}

	void SampleBuffer::Iterator::set_subsample(const unsigned int channel_index, const float sample)
	{
		*(channels_[channel_index]) = sample;
	}

	bool SampleBuffer::Iterator::operator==(const SampleBuffer::Iterator& other_iterator) const
	{
		bool equal = true;
		for (unsigned int i = 0; i < channels_.size(); i++) {
			if (other_iterator.channels_[i] != channels_[i]) {
				equal = false;
				break;
			}
		}
		return equal;
	}

	bool SampleBuffer::Iterator::operator!=(const SampleBuffer::Iterator& other_iterator) const
	{
		return ! (*this == other_iterator);
	}

	bool SampleBuffer::Iterator::operator<(const SampleBuffer::Iterator& other_iterator) const
	{
		if (channels_.size() == 0) return false;
		return this->channels_[0] < other_iterator.channels_[0];
	}

	bool SampleBuffer::Iterator::operator>(const SampleBuffer::Iterator& other_iterator) const
	{
		if (channels_.size() == 0) return false;
		return this->channels_[0] > other_iterator.channels_[0];
	}

	bool SampleBuffer::Iterator::operator<=(const SampleBuffer::Iterator& other_iterator) const
	{
		if (channels_.size() == 0) return false;
		return this->channels_[0] <= other_iterator.channels_[0];
	}

	bool SampleBuffer::Iterator::operator>=(const SampleBuffer::Iterator& other_iterator) const
	{
		if (channels_.size() == 0) return false;
		return this->channels_[0] >= other_iterator.channels_[0];
	}

	const Sample SampleBuffer::Iterator::operator*() const
	{
		std::vector<float> samples(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			samples[i] = *channels_[i];
		}
		return Sample(samples);
	}

	const Sample SampleBuffer::Iterator::operator->() const
	{
		return *(*this);
	}

	Sample SampleBuffer::Iterator::operator++(int)
	{
		Sample sample = *(*this);
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels_[i]++;
		}
		return sample;
	}


	Sample SampleBuffer::Iterator::operator++()
	{
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels_[i]++;
		}
		return *(*this);
	}

	Sample SampleBuffer::Iterator::operator--(int)
	{
		Sample sample = *(*this);
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels_[i]--;
		}
		return sample;
	}

	Sample SampleBuffer::Iterator::operator--()
	{
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels_[i]--;
		}
		return *(*this);
	}


	void SampleBuffer::Iterator::operator+=(int step)
	{
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels_[i] += step;
		}
	}

	void SampleBuffer::Iterator::operator-=(int step)
	{
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels_[i] -= step;
		}
	}

	Sample SampleBuffer::Iterator::operator[](int index) const
	{
		std::vector<float> samples(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			samples[i] = *(channels_[i] + index);
		}
		return Sample(samples);
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
