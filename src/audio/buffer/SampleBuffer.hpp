#ifndef __SAMPLE_BUFFER_CLASS__
#define __SAMPLE_BUFFER_CLASS__

#include <sndfile.h>
#include <vector>
#include <fftw3.h>

#include <time/Time.hpp>
#include <audio/sample/Sample.hpp>
#include <audio/channel/Channel.hpp>
#include <buffer/Buffer.hpp>

namespace analyser {
	class SampleBuffer
	{
		public:
			static bool load_from_file(const char* path, SampleBuffer* buffer);

			~SampleBuffer();
			SampleBuffer();
			SampleBuffer clone() const;

			void clear();

			class Iterator
			{
				public:
					Iterator();
					Iterator(const Iterator& original) = default;
					Iterator(std::vector<float*> channels, size_t initial_offset);
					Iterator& operator=(const Iterator& original) = default;

					float get_subsample(const unsigned int channel_index) const;
					void set_subsample(const unsigned int channel_index, const float sample);
					bool operator==(const SampleBuffer::Iterator& iterator) const;
					bool operator!=(const SampleBuffer::Iterator& iterator) const;
					bool operator<(const SampleBuffer::Iterator& iterator) const;
					bool operator>(const SampleBuffer::Iterator& iterator) const;
					bool operator<=(const SampleBuffer::Iterator& iterator) const;
					bool operator>=(const SampleBuffer::Iterator& iterator) const;

					const Sample operator*() const;
					const Sample operator->() const;
					void operator++(int);
					void operator++();
					void operator--(int);
					void operator--();
					void operator+=(int step);
					void operator-=(int step);
					Sample operator[](int index) const;
				private:
					std::vector<float*> channels_;
					size_t offset_;
			};

			Iterator begin() const;
			Iterator end() const;
			Iterator get_iterator_at(const Time& time) const;
			Iterator get_iterator_at_second(double second) const;

			using ChannelIterator = float*;

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
			size_t get_block(unsigned int channel_index, const Time& begin_time, const Time& end_time, Channel::Block* block) const;
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
