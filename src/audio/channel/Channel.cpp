#include "Channel.hpp"

#include <time/Time.hpp>
#include <time/PartialTime.hpp>
#include <buffer/BufferSection.hpp>
#include <audio/channel/ChannelBlock.hpp>

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
		return buffer_.get_size();
	}

	unsigned int Channel::get_samplerate() const
	{
		return samplerate_;
	}

	Time Channel::get_duration() const
	{
		return Time::from_number_of_samples(get_number_of_samples(), samplerate_);
	}

	Time Channel::seconds_to_time(double seconds) const
	{
		return Time::from_seconds(seconds, samplerate_);
	}

	Time Channel::number_of_samples_to_time(size_t number_of_samples) const
	{
		return Time::from_number_of_samples(number_of_samples, samplerate_);
	}

	ChannelIterator Channel::begin() const
	{
		return buffer_.get_data();
	}

	ChannelIterator Channel::end() const
	{
		return buffer_.get_data() + get_number_of_samples();
	}

	ChannelIterator Channel::get_iterator_at(const PartialTime& time) const
	{
		return get_iterator_at_sample(time.to_time(samplerate_).get_number_of_samples());
	}

	ChannelIterator Channel::get_iterator_at_sample(const size_t offset) const
	{
		return buffer_.get_data() + offset;
	}

	size_t Channel::get_block(const PartialTime& begin_time, const PartialTime& end_time, ChannelBlock* block) const
	{
		const Time b_time = begin_time.to_time(samplerate_);
		const Time e_time = end_time.to_time(samplerate_);
		size_t number_of_copied_samples = 0;
		if (b_time <= get_duration()) {
			size_t end_index = std::min(e_time.get_number_of_samples(), 				// normal end index
										get_duration().get_number_of_samples());		// index if end would be out of bounds

			BufferSection buffer_section = buffer_.get_section(b_time.get_number_of_samples(), end_index);
			*block = ChannelBlock(buffer_section);
			number_of_copied_samples = end_index - b_time.get_number_of_samples();
		}
		return number_of_copied_samples;
	}

	bool Channel::get_subsample_at(const PartialTime& time, float* subsample)
	{
		Time t = time.to_time(samplerate_);
		bool success = true;
		if (t > get_duration()) {
			success = false;
		} else {
			*subsample = *(buffer_.get_data() + t.get_number_of_samples());
		}
		return success;
	}
}
