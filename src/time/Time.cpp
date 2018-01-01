#include "Time.hpp"

#include <cmath>

namespace analyser {
	Time Time::from_number_of_samples(size_t number_of_samples, unsigned int samplerate)
	{
		return Time(number_of_samples, samplerate);
	}

	Time Time::from_seconds(double seconds, unsigned int samplerate)
	{
		return Time(seconds * samplerate, samplerate);
	}

	size_t Time::seconds_to_number_of_samples(double seconds, unsigned int samplerate)
	{
		return (size_t)std::abs(seconds * samplerate);
	}

	double Time::number_of_samples_to_seconds(size_t number_of_samples, unsigned int samplerate)
	{
		return number_of_samples / (double)samplerate;
	}

	Time::Time(size_t number_of_samples, unsigned int samplerate)
		: number_of_samples_(number_of_samples), samplerate_(samplerate)
	{}

	unsigned int Time::get_samplerate() const
	{
		return samplerate_;
	}

	size_t Time::get_number_of_samples() const
	{
		return number_of_samples_;
	}

	double Time::get_seconds() const
	{
		return number_of_samples_ / (double)samplerate_;
	}
	Time Time::plus_seconds(double seconds) const
	{
		return Time(this->get_number_of_samples() + seconds_to_number_of_samples(seconds, this->samplerate_), this->samplerate_);
	}

	Time Time::minus_seconds(double seconds) const
	{
		long int number_of_samples = this->get_number_of_samples() + seconds_to_number_of_samples(seconds, this->samplerate_);
		if (number_of_samples < 0) {
			return Time(number_of_samples, this->samplerate_);
		}
		return Time(0, this->samplerate_);
	}

	Time Time::plus_number_of_samples(size_t number_of_samples) const
	{
		return Time(this->number_of_samples_ + number_of_samples, this->samplerate_);
	}

	Time Time::minus_number_of_samples(size_t number_of_samples) const
	{
		if (this->number_of_samples_ < number_of_samples) {
			return Time(0, this->samplerate_);
		}
		return Time(this->number_of_samples_ + number_of_samples, this->samplerate_);
	}

	Time Time::operator+(const Time& time) const
	{
		return Time(this->number_of_samples_ + time.number_of_samples_, this->samplerate_);
	}

	Time Time::operator-(const Time& time) const
	{
		if (this->number_of_samples_ < time.number_of_samples_) {
			return Time(0, this->samplerate_);
		}
		return Time(this->number_of_samples_ - time.number_of_samples_, this->samplerate_);
	}

	void Time::operator+=(const Time& time)
	{
		this->number_of_samples_ += time.number_of_samples_;
	}

	void Time::operator-=(const Time& time)
	{
		if (*this >= time) {
			this->number_of_samples_ -= time.number_of_samples_;
		}
	}

	bool Time::operator<(const Time& time) const
	{
		return this->number_of_samples_ < time.number_of_samples_;
	}

	bool Time::operator>(const Time& time) const
	{
		return this->number_of_samples_ > time.number_of_samples_;
	}

	bool Time::operator<=(const Time& time) const
	{
		return this->number_of_samples_ <= time.number_of_samples_;
	}

	bool Time::operator>=(const Time& time) const
	{
		return this->number_of_samples_ >= time.number_of_samples_;
	}

	bool Time::operator==(const Time& time) const
	{
		return (this->number_of_samples_ == time.number_of_samples_) && (this->samplerate_ == this->samplerate_);
	}

	bool Time::operator!=(const Time& time) const
	{
		return !(*this == time);
	}
}
