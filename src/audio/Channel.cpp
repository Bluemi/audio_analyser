#include "Channel.hpp"

namespace analyser {
	Channel::Channel()
		: samples_(nullptr), number_of_samples_(0), samplerate_(0)
	{}

	Channel::Channel(float* samples, size_t number_of_samples, unsigned int samplerate)
		: samples_(samples), number_of_samples_(number_of_samples), samplerate_(samplerate)
	{}

	Channel::~Channel() 
	{
		delete samples_;
	}

	void Channel::set_all(float* samples, size_t number_of_samples, unsigned int samplerate)
	{
		samples_ = samples;
		number_of_samples_ = number_of_samples;
		samplerate_ = samplerate;
	}

	bool Channel::is_empty() const
	{
		return samples_ == nullptr;
	}

	unsigned int Channel::get_samplerate() const
	{
		return samplerate_;
	}

	Time Channel::get_duration() const
	{
		return Time::from_number_of_samples(number_of_samples_, samplerate_);
	}

	Time Channel::seconds_to_time(float seconds) const
	{
		return Time::from_seconds(seconds, samplerate_);
	}

	Time Channel::number_of_samples_to_time(size_t number_of_samples) const
	{
		return Time::from_number_of_samples(number_of_samples, samplerate_);
	}

	bool Channel::get_subsample_at(const Time& time, float* subsample)
	{
		bool success = true;
		if (time > get_duration()) {
			success = false;
		} else {
			*subsample = *(samples_ + time.get_number_of_samples());
		}
		return success;
	}

	bool Channel::get_subsample_at_seconds(double seconds, float* subsample)
	{
		return get_subsample_at(this->seconds_to_time(seconds), subsample);
	}
}
