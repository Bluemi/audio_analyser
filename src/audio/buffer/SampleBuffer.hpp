#ifndef __SAMPLE_BUFFER_CLASS__
#define __SAMPLE_BUFFER_CLASS__

#include <sndfile.h>
#include <vector>
#include <fftw3.h>

#include <buffer/Buffer.hpp>
#include <audio/channel/ChannelIterator.hpp>

namespace analyser {
	class Time;
	class Sample;
	class Channel;
	class ChannelBlock;
	class SampleBufferIterator;

	class SampleBuffer
	{
		public:
			static bool load_from_file(const char* path, SampleBuffer* buffer);

			~SampleBuffer();
			SampleBuffer();
			SampleBuffer clone() const;

			void clear();

			using Iterator = SampleBufferIterator;

			Iterator begin() const;
			Iterator end() const;
			Iterator get_iterator_at(const Time& time) const;
			Iterator get_iterator_at_second(double second) const;

			ChannelIterator begin(unsigned int channel_index) const;
			ChannelIterator end(unsigned int channel_index) const;
			ChannelIterator get_iterator_at(unsigned int channel_index, const Time& time) const;
			ChannelIterator get_iterator_at_second(unsigned int channel_index, double second) const;

			// stats
			unsigned int get_samplerate() const;
			unsigned int get_number_of_channels() const;
			bool is_empty() const;

			// Time
			Time get_duration() const;
			Time seconds_to_time(double seconds) const;
			Time number_of_samples_to_time(size_t number_of_samples) const;

			// Sample
			bool get_sample_at(const Time& time, Sample* sample) const;
			bool get_sample(const size_t sample_offset, Sample* sample) const;
			bool get_subsample_at(const Time& time, unsigned int channel_index, float* subsample) const;

			// Channel
			bool get_channel(unsigned int channel_index, Channel* channel) const;

			// Block
			size_t get_block(unsigned int channel_index, const Time& begin_time, const Time& end_time, ChannelBlock* block) const;
		private:
			static size_t loadSamples(SNDFILE *file, float *samples, const sf_count_t frames);

			std::vector<Buffer> channels_;
			unsigned int samplerate_;
			size_t number_of_samples_;
	};

	// Iterator Functions
	SampleBuffer::Iterator operator+(SampleBuffer::Iterator iterator, int step);
	SampleBuffer::Iterator operator-(SampleBuffer::Iterator iterator, int step);
}

#endif
