#include "Channel.hpp"

namespace analyser {
	Channel::Iterator::Iterator()
		: samples_(nullptr)
	{}

	Channel::Iterator::Iterator(float* samples, size_t initial_offset)
		: samples_(samples + initial_offset)
	{}

	bool Channel::Iterator::operator==(const Channel::Iterator& other_iterator) const
	{
		return this->samples_ == other_iterator.samples_;
	}

	bool Channel::Iterator::operator!=(const Channel::Iterator& other_iterator) const
	{
		return this->samples_ != other_iterator.samples_;
	}

	bool Channel::Iterator::operator<(const Channel::Iterator& other_iterator) const
	{
		return this->samples_ < other_iterator.samples_;
	}

	bool Channel::Iterator::operator>(const Channel::Iterator& other_iterator) const
	{
		return this->samples_ > other_iterator.samples_;
	}

	bool Channel::Iterator::operator<=(const Channel::Iterator& other_iterator) const
	{
		return this->samples_ <= other_iterator.samples_;
	}

	bool Channel::Iterator::operator>=(const Channel::Iterator& other_iterator) const
	{
		return this->samples_ >= other_iterator.samples_;
	}

	float& Channel::Iterator::operator*() const
	{
		return *samples_;
	}

	// iter++
	Channel::Iterator Channel::Iterator::operator++(int)
	{
		Channel::Iterator iterator(samples_, 0);
		samples_++;
		return iterator;
	}

	// ++iter
	Channel::Iterator Channel::Iterator::operator++()
	{
		samples_++;
		return Channel::Iterator(samples_, 0);
	}

	// iter--
	Channel::Iterator Channel::Iterator::operator--(int)
	{
		Channel::Iterator iterator(samples_, 0);
		samples_--;
		return iterator;
	}

	// --iter
	Channel::Iterator Channel::Iterator::operator--()
	{
		samples_--;
		return Channel::Iterator(samples_, 0);
	}

	void Channel::Iterator::operator+=(int step)
	{
		samples_ += step;
	}

	void Channel::Iterator::operator-=(int step)
	{
		samples_ -= step;
	}

	float Channel::Iterator::operator[](int index) const
	{
		return *(samples_ + index);
	}

	Channel::Iterator operator+(Channel::Iterator iterator, int step)
	{
		iterator += step;
		return iterator;
	}

	Channel::Iterator operator-(Channel::Iterator iterator, int step)
	{
		iterator -= step;
		return iterator;
	}
}
