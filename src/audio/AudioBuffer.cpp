#include "AudioBuffer.hpp"

#include <misc/Debug.hpp>
#include <iostream>
#include <cmath>

namespace analyser {
	bool AudioBuffer::load_from_file(const char* path, AudioBuffer* buffer)
	{
		SF_INFO info;
		info.format = 0;

		// open audio file
		SNDFILE* file = sf_open(path, SFM_READ, &info);
		bool success;
		if (file != nullptr)
		{
			const size_t number_of_subsamples = info.frames * info.channels;
			float* samples = (float*)::operator new(sizeof(float) * number_of_subsamples);
			if (loadSamples(file, samples, info.frames) != (size_t) info.frames)
			{
				Debug::out << Debug::warn << "AudioBuffer::AudioBuffer(): info.frames(" << info.frames << "differs with the result of READ_FUNCTION" << Debug::endl;
			}

			// free old buffer
			if (!buffer->is_empty()) {
				buffer->delete_samples();
			}

			// set buffer properties
			buffer->samples_ = samples;
			buffer->empty_ = false;
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

	size_t AudioBuffer::loadSamples(SNDFILE *file, float *samples, const sf_count_t frames)
	{
		return sf_readf_float(file, samples, frames);
	}

	AudioBuffer::AudioBuffer()
		: samples_(nullptr), empty_(true), number_of_channels_(0), samplerate_(0), number_of_samples_(0)
	{}

	void AudioBuffer::delete_samples()
	{
		delete samples_;
	}

	AudioBuffer::~AudioBuffer()
	{
		if (!empty_)
		{
			delete_samples();
		}
	}

	AudioBuffer::Iterator AudioBuffer::begin() const
	{
		return AudioBuffer::Iterator(samples_, 0, number_of_channels_);
	}

	AudioBuffer::Iterator AudioBuffer::end() const
	{
		return AudioBuffer::Iterator(samples_, number_of_samples_, number_of_channels_);
	}

	AudioBuffer::Iterator AudioBuffer::get_iterator_at(const Time& time) const
	{
		size_t sample_position = time.get_number_of_samples();
		return Iterator(samples_, sample_position, number_of_channels_);
	}

	AudioBuffer::Iterator AudioBuffer::get_iterator_at_second(double seconds) const
	{
		return get_iterator_at(seconds_to_time(seconds));
	}

	unsigned int AudioBuffer::get_samplerate() const {
		return samplerate_;
	}

	unsigned int AudioBuffer::get_number_of_channels() const {
		return number_of_channels_;
	}

	bool AudioBuffer::is_empty() const {
		return empty_;
	}

	Time AudioBuffer::get_duration() const {
		return Time::from_number_of_samples(number_of_samples_, samplerate_);
	}

	Time AudioBuffer::seconds_to_time(double seconds) const
	{
		return Time::from_seconds(seconds, samplerate_);
	}

	Time AudioBuffer::number_of_samples_to_time(size_t number_of_samples) const
	{
		return Time::from_number_of_samples(number_of_samples, samplerate_);
	}

	bool AudioBuffer::get_sample_at(const Time& time, Sample* sample) const
	{
		return get_sample(time.get_number_of_samples(), sample);
	}

	bool AudioBuffer::get_sample(const size_t sample_offset, Sample* sample) const
	{
		bool success;
		if (sample_offset < number_of_samples_) {
			float* samples = samples_ + (sample_offset * number_of_channels_);
			sample->set(samples, number_of_channels_);
			success = true;
		} else {
			success = false;
			sample->invalidate();
		}
		return success;
	}

	bool AudioBuffer::get_subsample_at(const Time& time, unsigned int number_of_channel, float* subsample) const
	{
		bool success = true;
		if (time.get_number_of_samples() >= number_of_samples_) {
			success = false;
		} else if (number_of_channel >= number_of_channels_) {
			success = false;
		} else {
			*subsample = *(samples_ + (number_of_channels_ * time.get_number_of_samples() + number_of_channel));
		}

		return success;
	}

	bool AudioBuffer::get_channel(unsigned int channel_index, Channel* channel) const
	{
		bool success = true;

		// if this buffer is empty number_of_channels_ will be 0
		if (channel_index >= number_of_channels_) {
			success = false;
		} else {
			float* samples = (float*)::operator new(sizeof(float) * number_of_samples_);
			channel->set_all(samples, number_of_samples_, samplerate_);
		}

		return success;
	}
}
