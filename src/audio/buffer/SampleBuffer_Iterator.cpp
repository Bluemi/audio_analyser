#include "SampleBuffer.hpp"

namespace analyser {
	SampleBuffer::Iterator::Iterator() : offset_(0) {}

	SampleBuffer::Iterator::Iterator(std::vector<float*> channels, size_t initial_offset)
		: channels_(channels), offset_(initial_offset)
	{ }

	float SampleBuffer::Iterator::get_subsample(const unsigned int channel_index) const
	{
		return *(channels_[channel_index] + offset_);
	}

	void SampleBuffer::Iterator::set_subsample(const unsigned int channel_index, const float sample)
	{
		*(channels_[channel_index] + offset_) = sample;
	}

	bool SampleBuffer::Iterator::operator==(const SampleBuffer::Iterator& other_iterator) const
	{
		return offset_ == other_iterator.offset_;
	}

	bool SampleBuffer::Iterator::operator!=(const SampleBuffer::Iterator& other_iterator) const
	{
		return ! (*this == other_iterator);
	}

	bool SampleBuffer::Iterator::operator<(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->offset_ < other_iterator.offset_;
	}

	bool SampleBuffer::Iterator::operator>(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->offset_ > other_iterator.offset_;
	}

	bool SampleBuffer::Iterator::operator<=(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->offset_ <= other_iterator.offset_;
	}

	bool SampleBuffer::Iterator::operator>=(const SampleBuffer::Iterator& other_iterator) const
	{
		return this->offset_ >= other_iterator.offset_;
	}

	const Sample SampleBuffer::Iterator::operator*() const
	{
		std::vector<float> samples(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			samples[i] = *(channels_[i] + offset_);
		}
		return Sample(samples);
	}

	const Sample SampleBuffer::Iterator::operator->() const
	{
		return *(*this);
	}

	void SampleBuffer::Iterator::operator++(int)
	{
		offset_++;
	}

	void SampleBuffer::Iterator::operator++()
	{
		offset_++;
	}

	void SampleBuffer::Iterator::operator--(int)
	{
		offset_--;
	}

	void SampleBuffer::Iterator::operator--()
	{
		offset_--;
	}

	void SampleBuffer::Iterator::operator+=(int step)
	{
		offset_ += step;
	}

	void SampleBuffer::Iterator::operator-=(int step)
	{
		offset_ -= step;
	}

	Sample SampleBuffer::Iterator::operator[](int index) const
	{
		std::vector<float> samples(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			samples[i] = *(channels_[i] + index + offset_);
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
