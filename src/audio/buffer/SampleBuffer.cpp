#include "SampleBuffer.hpp"

#include <iostream>
#include <cmath>

namespace analyser {
	bool SampleBuffer::load_from_file(const char* path, SampleBuffer* buffer)
	{
		SF_INFO info;
		info.format = 0;

		// open audio file
		SNDFILE* file = sf_open(path, SFM_READ, &info);
		bool success;
		if (file != nullptr)
		{
			const size_t number_of_subsamples = info.frames * info.channels;
			buffer->buffer_.allocate(number_of_subsamples);
			if (loadSamples(file, buffer->buffer_.get_data(), info.frames) != (size_t) info.frames)
			{
				//Debug::out << Debug::warn << "SampleBuffer::SampleBuffer(): info.frames(" << info.frames << "differs with the result of READ_FUNCTION" << Debug::endl;
			}

			// set buffer properties
			buffer->number_of_channels_ = info.channels;
			buffer->samplerate_ = info.samplerate;
			buffer->number_of_samples_ = info.frames;
			sf_close(file);
			success = true;
		} else {
			success = false;
		}
		return success;
	}

	size_t SampleBuffer::loadSamples(SNDFILE *file, float *samples, const sf_count_t frames)
	{
		return sf_readf_float(file, samples, frames);
	}

	SampleBuffer::SampleBuffer()
		: buffer_(), number_of_channels_(0), samplerate_(0), number_of_samples_(0)
	{}

	SampleBuffer::~SampleBuffer()
	{}

	SampleBuffer SampleBuffer::clone() const
	{
		SampleBuffer buffer(*this);
		buffer.buffer_ = buffer_.clone();
		return buffer;
	}

	void SampleBuffer::clear()
	{
		buffer_.clear();
		number_of_channels_ = 0;
		samplerate_ = 0;
		number_of_samples_ = 0;
	}

	SampleBuffer::Iterator SampleBuffer::begin() const
	{
		return SampleBuffer::Iterator(buffer_.get_data(), 0, number_of_channels_);
	}

	SampleBuffer::Iterator SampleBuffer::end() const
	{
		return SampleBuffer::Iterator(buffer_.get_data(), number_of_samples_, number_of_channels_);
	}

	SampleBuffer::Iterator SampleBuffer::get_iterator_at(const Time& time) const
	{
		size_t sample_position = time.get_number_of_samples();
		return Iterator(buffer_.get_data(), sample_position, number_of_channels_);
	}

	SampleBuffer::Iterator SampleBuffer::get_iterator_at_second(double seconds) const
	{
		return get_iterator_at(seconds_to_time(seconds));
	}

	unsigned int SampleBuffer::get_samplerate() const {
		return samplerate_;
	}

	unsigned int SampleBuffer::get_number_of_channels() const {
		return number_of_channels_;
	}

	bool SampleBuffer::is_empty() const {
		return buffer_.is_empty();
	}

	Time SampleBuffer::get_duration() const {
		return Time::from_number_of_samples(number_of_samples_, samplerate_);
	}

	Time SampleBuffer::seconds_to_time(double seconds) const
	{
		return Time::from_seconds(seconds, samplerate_);
	}

	Time SampleBuffer::number_of_samples_to_time(size_t number_of_samples) const
	{
		return Time::from_number_of_samples(number_of_samples, samplerate_);
	}

	bool SampleBuffer::get_sample_at(const Time& time, Sample* sample) const
	{
		return get_sample(time.get_number_of_samples(), sample);
	}

	bool SampleBuffer::get_sample(const size_t sample_offset, Sample* sample) const
	{
		bool success;
		if (sample_offset < number_of_samples_) {
			float* samples = buffer_.get_data() + (sample_offset * number_of_channels_);
			sample->set(samples, number_of_channels_);
			success = true;
		} else {
			success = false;
			sample->invalidate();
		}
		return success;
	}

	bool SampleBuffer::get_subsample_at(const Time& time, unsigned int number_of_channel, float* subsample) const
	{
		bool success = true;
		if (time.get_number_of_samples() >= number_of_samples_) {
			success = false;
		} else if (number_of_channel >= number_of_channels_) {
			success = false;
		} else {
			*subsample = *(buffer_.get_data() + (number_of_channels_ * time.get_number_of_samples() + number_of_channel));
		}

		return success;
	}

	bool SampleBuffer::get_channel(unsigned int channel_index, Channel* channel) const
	{
		bool success = true;

		// if this buffer is empty number_of_channels_ will be 0
		if (channel_index >= number_of_channels_) {
			success = false;
		} else {
			Buffer buffer(number_of_samples_);
			channel->set_all(buffer, samplerate_);
		}

		return success;
	}
}
