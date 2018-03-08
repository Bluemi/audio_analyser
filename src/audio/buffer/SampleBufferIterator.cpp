#include "SampleBufferIterator.hpp"

#include <audio/sample/Sample.hpp>

namespace analyser {
	SampleBufferIterator::SampleBufferIterator() : offset_(0) {}

	SampleBufferIterator::SampleBufferIterator(std::vector<float*> channels, size_t initial_offset)
		: channels_(channels), offset_(initial_offset)
	{ }

	float SampleBufferIterator::get_subsample(const unsigned int channel_index) const
	{
		return *(channels_[channel_index] + offset_);
	}

	bool SampleBufferIterator::operator==(const SampleBufferIterator& other_iterator) const
	{
		return offset_ == other_iterator.offset_;
	}

	bool SampleBufferIterator::operator!=(const SampleBufferIterator& other_iterator) const
	{
		return ! (*this == other_iterator);
	}

	bool SampleBufferIterator::operator<(const SampleBufferIterator& other_iterator) const
	{
		return this->offset_ < other_iterator.offset_;
	}

	bool SampleBufferIterator::operator>(const SampleBufferIterator& other_iterator) const
	{
		return this->offset_ > other_iterator.offset_;
	}

	bool SampleBufferIterator::operator<=(const SampleBufferIterator& other_iterator) const
	{
		return this->offset_ <= other_iterator.offset_;
	}

	bool SampleBufferIterator::operator>=(const SampleBufferIterator& other_iterator) const
	{
		return this->offset_ >= other_iterator.offset_;
	}

	const Sample SampleBufferIterator::operator*() const
	{
		std::vector<float> samples(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			samples[i] = *(channels_[i] + offset_);
		}
		return Sample(samples);
	}

	const Sample SampleBufferIterator::operator->() const
	{
		return *(*this);
	}

	void SampleBufferIterator::operator++(int)
	{
		offset_++;
	}

	void SampleBufferIterator::operator++()
	{
		offset_++;
	}

	void SampleBufferIterator::operator--(int)
	{
		offset_--;
	}

	void SampleBufferIterator::operator--()
	{
		offset_--;
	}

	void SampleBufferIterator::operator+=(int step)
	{
		offset_ += step;
	}

	void SampleBufferIterator::operator-=(int step)
	{
		offset_ -= step;
	}

	Sample SampleBufferIterator::operator[](int index) const
	{
		std::vector<float> samples(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			samples[i] = *(channels_[i] + index + offset_);
		}
		return Sample(samples);
	}

	SampleBufferIterator operator+(SampleBufferIterator iterator, int step)
	{
		iterator += step;
		return iterator;
	}

	SampleBufferIterator operator-(SampleBufferIterator iterator, int step)
	{
		iterator -= step;
		return iterator;
	}
}
