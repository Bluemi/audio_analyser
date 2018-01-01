#ifndef __AUDIOFILE_CLASS__
#define __AUDIOFILE_CLASS__

#include <sndfile.h>
#include <vector>
#include <fftw3.h>

#include <time/Time.hpp>
#include <audio/Sample.hpp>
#include <audio/Channel.hpp>
#include <audio/Buffer.hpp>

namespace analyser {
	class AudioBuffer
	{
		public:
			static bool load_from_file(const char* path, AudioBuffer* buffer);
			~AudioBuffer();
			AudioBuffer();

			// Iterator
			class Iterator
			{
				public:
					Iterator();
					Iterator(const Iterator& original) = default;
					Iterator(float* samples, size_t initial_offset, unsigned int number_of_channels);
					Iterator& operator=(const Iterator& original) = default;

					float get_subsample(const unsigned int channel_index) const;
					void set_subsample(const unsigned int channel_index, const float sample);

					bool operator==(const AudioBuffer::Iterator& iterator) const;
					bool operator!=(const AudioBuffer::Iterator& iterator) const;

					bool operator<(const AudioBuffer::Iterator& iterator) const;
					bool operator>(const AudioBuffer::Iterator& iterator) const;
					bool operator<=(const AudioBuffer::Iterator& iterator) const;
					bool operator>=(const AudioBuffer::Iterator& iterator) const;

					const Sample operator*() const;
					const Sample operator->() const;

					Sample operator++(int);
					Sample operator++();

					Sample operator--(int);
					Sample operator--();

					void operator+=(int step);
					void operator-=(int step);

					Sample operator[](int index) const;
				private:
					float* samples_;
					unsigned int number_of_channels_;
			};

			Iterator begin() const;
			Iterator end() const;
			Iterator get_iterator_at(const Time& time) const;
			Iterator get_iterator_at_second(double second) const;

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
			bool get_subsample_at(const Time& time, unsigned int number_of_channel, float* subsample) const;

			// Channel
			bool get_channel(unsigned int channel_index, Channel* channel) const;
		private:
			static size_t loadSamples(SNDFILE *file, float *samples, const sf_count_t frames);

			Buffer buffer_;
			bool empty_;
			unsigned int number_of_channels_;
			unsigned int samplerate_;
			size_t number_of_samples_;
	};

	// Iterator Functions
	AudioBuffer::Iterator operator+(AudioBuffer::Iterator iterator, int step);

	AudioBuffer::Iterator operator-(AudioBuffer::Iterator iterator, int step);
}

#endif
