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
	/**
	 * \brief Represents an AudioFile
	 *
	 * An SampleBuffer holds the samples of an Audiofile and provides functions to access the containing samples.
	 */
	class SampleBuffer
	{
		public:
			/**
			 * \brief Loads samples from an audiofile into a buffer.
			 *
			 * Loads samples from an audiofile given by `path` into the given buffer. Returns whether loading was successful or not.
			 * @param path Path to file to load
			 * @param buffer Buffer into which the samples are loaded
			 * @return true if loading was successful, false if not
			 */
			static bool load_from_file(const char* path, SampleBuffer* buffer);

			/**
			 * \brief Destructs the Audiobuffer
			 *
			 * Releases the contained sampels if not hold by another buffer.
			 */
			~SampleBuffer();

			/**
			 * \brief Creates an empty buffer
			 */
			SampleBuffer();

			/**
			 * \brief Clones the audiobuffer
			 *
			 * Performs a deep copy of the samples. The new buffer will have independent samples
			 */
			SampleBuffer clone() const;

			/**
			 * \brief An Iterator over the buffer
			 *
			 * This random access iterator can be used to iterate over the samples of the buffer.
			 * You can access samples as well as subsamples.
			 */
			class Iterator
			{
				public:
					/**
					 * \brief Creates an empty Iterator
					 *
					 * This Iterator points to no data. You should not try to access samples of this iterator.
					 */
					Iterator();

					/**
					 * \brief copy constructor
					 *
					 * Performs a memberwise copy of this iterator.
					 * @param original The iterator to copy from
					 */
					Iterator(const Iterator& original) = default;

					/**
					 * \brief Creates an new iterator to iterator over the samples
					 *
					 * @param samples The samples to iterator over
					 * @param initial_offset The offset to start with
					 * @param number_of_channels The number of channels of the SampleBuffer
					 */
					Iterator(float* samples, size_t initial_offset, unsigned int number_of_channels);

					/**
					 * \brief Assigns the righthand iterator to the lefthand.
					 *
					 * @param original The iterator to copy from
					 */
					Iterator& operator=(const Iterator& original) = default;

					/**
					 * \brief Gets the subsample at the current iterator position
					 *
					 * @param channel_index The channelindex from which you want to get the sample
					 * @return The subsample at the current iterator position and specified channel
					 */
					float get_subsample(const unsigned int channel_index) const;

					/**
					 * \brief Sets the subsample at the current iterator position
					 *
					 * @param channel_index The channelindex from which you want to set the sample
					 */
					void set_subsample(const unsigned int channel_index, const float sample);

					bool operator==(const SampleBuffer::Iterator& iterator) const;
					bool operator!=(const SampleBuffer::Iterator& iterator) const;

					bool operator<(const SampleBuffer::Iterator& iterator) const;
					bool operator>(const SampleBuffer::Iterator& iterator) const;
					bool operator<=(const SampleBuffer::Iterator& iterator) const;
					bool operator>=(const SampleBuffer::Iterator& iterator) const;

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
	SampleBuffer::Iterator operator+(SampleBuffer::Iterator iterator, int step);

	SampleBuffer::Iterator operator-(SampleBuffer::Iterator iterator, int step);
}

#endif
