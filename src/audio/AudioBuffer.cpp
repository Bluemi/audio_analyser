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

	/*
	SampleIterator AudioBuffer::getIteratorFrom(const Time frame_offset, StereoChannel channel) const
	{
		return SampleIterator(samples, frame_offset.getFrameCount(), duration.getFrameCount(), channel);
	}
	*/
}
