#include "Channel.hpp"

namespace analyser {
	Channel::Channel()
		: buffer_(), samplerate_(0)
	{}

	Channel::Channel(const Buffer& buffer, unsigned int samplerate)
		: buffer_(buffer), samplerate_(samplerate)
	{}

	Channel::~Channel() 
	{}

	void Channel::set_all(const Buffer& buffer, unsigned int samplerate)
	{
		buffer_ = buffer;
		samplerate_ = samplerate;
	}

	bool Channel::is_empty() const
	{
		return buffer_.is_empty();
	}

	size_t Channel::get_number_of_samples() const
	{
		return buffer_.get_number_of_samples();
	}

	unsigned int Channel::get_samplerate() const
	{
		return samplerate_;
	}

	Time Channel::get_duration() const
	{
		return Time::from_number_of_samples(get_number_of_samples(), samplerate_);
	}

	Time Channel::seconds_to_time(float seconds) const
	{
		return Time::from_seconds(seconds, samplerate_);
	}

	Time Channel::number_of_samples_to_time(size_t number_of_samples) const
	{
		return Time::from_number_of_samples(number_of_samples, samplerate_);
	}

	Channel::Iterator Channel::begin() const
	{
		return Channel::Iterator(buffer_.get_samples(), 0);
	}

	Channel::Iterator Channel::end()
	{
		return Channel::Iterator(buffer_.get_samples(), get_number_of_samples());
	}

	Channel::Iterator Channel::get_iterator_at(const Time& time)
	{
		return get_iterator_at_sample(time.get_number_of_samples());
	}

	Channel::Iterator Channel::get_iterator_at_sample(const size_t offset)
	{
		return Channel::Iterator(buffer_.get_samples(), offset);
	}

	size_t Channel::get_block(const Time& start, const Time& duration, Block* block) const
	{
		size_t number_of_copied_samples = 0;
		if (start <= get_duration()) {
			size_t end_index = std::min(start.get_number_of_samples() + duration.get_number_of_samples(), 	// normal end index
										get_duration().get_number_of_samples());							// index if end would be out of bounds

			Buffer buffer = buffer_.clone_from_to(start.get_number_of_samples(), end_index);
			*block = Block(buffer);
			number_of_copied_samples = end_index - start.get_number_of_samples();
		}
		return number_of_copied_samples;
	}

	bool Channel::get_subsample_at(const Time& time, float* subsample)
	{
		bool success = true;
		if (time > get_duration()) {
			success = false;
		} else {
			*subsample = *(buffer_.get_samples() + time.get_number_of_samples());
		}
		return success;
	}

	bool Channel::get_subsample_at_seconds(double seconds, float* subsample)
	{
		return get_subsample_at(this->seconds_to_time(seconds), subsample);
	}
}