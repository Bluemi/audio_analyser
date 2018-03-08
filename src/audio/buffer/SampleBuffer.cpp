#include "SampleBuffer.hpp"

#include <cmath>
#include <cstdlib>

#include <time/Time.hpp>
#include <audio/sample/Sample.hpp>

namespace analyser {
	bool SampleBuffer::load_from_file(const char* path, SampleBuffer* buffer)
	{
		SF_INFO info;
		info.format = 0;

		buffer->clear();

		// open audio file
		SNDFILE* file = sf_open(path, SFM_READ, &info);
		bool success = false;
		if (file != nullptr)
		{
			const size_t number_of_samples = info.frames;
			const size_t number_of_channels = info.channels;
			const size_t number_of_subsamples = number_of_samples * number_of_channels;
			float* samples = (float*) malloc(number_of_subsamples * sizeof(float));
			if (loadSamples(file, samples, number_of_samples) != (size_t) number_of_samples)
			{
				// ERROR
			}

			// fill channels with data
			for (unsigned int channel_index = 0; channel_index < (unsigned int)number_of_channels; channel_index++) {
				Buffer channel(number_of_samples);
				for (size_t i = 0; i < (size_t)number_of_samples; i++) {
					channel.get_data()[i] = samples[i*number_of_channels + channel_index];
				}
				buffer->channels_.push_back(channel);
			}

			// set buffer properties
			buffer->samplerate_ = info.samplerate;
			buffer->number_of_samples_ = number_of_samples;
			sf_close(file);
			free(samples);
			success = true;
		}
		return success;
	}

	size_t SampleBuffer::loadSamples(SNDFILE *file, float *samples, const sf_count_t frames)
	{
		return sf_readf_float(file, samples, frames);
	}

	SampleBuffer::SampleBuffer()
		: channels_(), samplerate_(0), number_of_samples_(0)
	{}

	SampleBuffer::~SampleBuffer()
	{}

	SampleBuffer SampleBuffer::clone() const
	{
		SampleBuffer buffer(*this);
		for (unsigned int i = 0; i < channels_.size(); i++) {
			buffer.channels_[i] = channels_[i].clone();
		}
		return buffer;
	}

	void SampleBuffer::clear()
	{
		channels_.clear();
		samplerate_ = 0;
		number_of_samples_ = 0;
	}

	SampleBuffer::Iterator SampleBuffer::begin() const
	{
		std::vector<float*> channels(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels[i] = channels_[i].get_data();
		}
		return SampleBuffer::Iterator(channels, 0);
	}

	SampleBuffer::Iterator SampleBuffer::end() const
	{
		std::vector<float*> channels(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels[i] = channels_[i].get_data();
		}
		return SampleBuffer::Iterator(channels, number_of_samples_);
	}

	SampleBuffer::Iterator SampleBuffer::get_iterator_at(const Time& time) const
	{
		std::vector<float*> channels(channels_.size());
		for (unsigned int i = 0; i < channels_.size(); i++) {
			channels[i] = channels_[i].get_data() + time.get_number_of_samples();
		}
		return SampleBuffer::Iterator(channels, number_of_samples_);
	}

	SampleBuffer::Iterator SampleBuffer::get_iterator_at_second(double seconds) const
	{
		return get_iterator_at(seconds_to_time(seconds));
	}

	ChannelIterator SampleBuffer::begin(unsigned int channel_index) const
	{
		return channels_[channel_index].get_data();
	}

	ChannelIterator SampleBuffer::end(unsigned int channel_index) const
	{
		return channels_[channel_index].get_data();
	}

	ChannelIterator SampleBuffer::get_iterator_at(unsigned int channel_index, const Time& time) const
	{
		return channels_[channel_index].get_data() + time.get_number_of_samples();
	}

	ChannelIterator SampleBuffer::get_iterator_at_second(unsigned int channel_index, double second) const
	{
		return get_iterator_at(channel_index, seconds_to_time(second));
	}

	unsigned int SampleBuffer::get_samplerate() const {
		return samplerate_;
	}

	unsigned int SampleBuffer::get_number_of_channels() const {
		return channels_.size();
	}

	bool SampleBuffer::is_empty() const {
		return channels_.empty();
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
		bool success = true;
		if (sample_offset < number_of_samples_) {
			std::vector<float> samples(channels_.size());
			for (unsigned int i = 0; i < channels_.size(); i++) {
				samples[i] = *(channels_[i].get_data() + sample_offset);
			}
			*sample = Sample(samples);
		} else {
			success = false;
			sample->invalidate();
		}
		return success;
	}

	bool SampleBuffer::get_subsample_at(const Time& time, unsigned int channel_index, float* subsample) const
	{
		bool success = true;
		if ((time.get_number_of_samples() >= number_of_samples_) || (channel_index>= channels_.size())) {
			success = false;
		} else {
			*subsample = *(channels_[channel_index].get_data() + time.get_number_of_samples());
		}

		return success;
	}

	bool SampleBuffer::get_channel(unsigned int channel_index, Channel* channel) const
	{
		bool success = false;

		// if this buffer is empty channels_.size() will be 0
		if (channel_index < channels_.size()) {
			success = true;
			*channel = Channel(channels_[channel_index], samplerate_);
		}

		return success;
	}

	size_t SampleBuffer::get_block(unsigned int channel_index, const Time& begin_time, const Time& end_time, Channel::Block* block) const
	{
		size_t number_of_copied_samples = 0;

		if ((channel_index < channels_.size()) && (begin_time <= end_time) && (begin_time.get_number_of_samples() < number_of_samples_)) {
			size_t end_index = std::min(end_time.get_number_of_samples(), number_of_samples_);
			BufferSection buffer_section = channels_[channel_index].get_section(begin_time.get_number_of_samples(), end_index);
			*block = Channel::Block(buffer_section);
			number_of_copied_samples = end_index - begin_time.get_number_of_samples();
		}
		return number_of_copied_samples;
	}
}
