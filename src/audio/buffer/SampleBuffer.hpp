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
	 * An SampleBuffer holds the samples of an Audiofile and provides functions to access the containing samples, blocks of samples or channels.
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

					/**
					 * \brief Checks if two iterators are equal
					 *
					 * @param iterator The iterator to check with
					 * @return true if both iterators have the same current element
					 */
					bool operator==(const SampleBuffer::Iterator& iterator) const;

					/**
					 * \brief Checks if two iterators are unequal
					 *
					 * @param iterator The iterator to check with
					 * @return false if both iterators have the same current element
					 */
					bool operator!=(const SampleBuffer::Iterator& iterator) const;

					/**
					 * \brief Checks if the left-hand iterators current element comes before the element of the right-hand iterator
					 *
					 * @param iterator The iterator to check with
					 * @return true if the current element of the left-hand iterator comes before the element of the right-hand iterator
					 */
					bool operator<(const SampleBuffer::Iterator& iterator) const;

					/**
					 * \brief Checks if the left-hand iterators current element comes after the element of the right-hand iterator
					 *
					 * @param iterator The iterator to check with
					 * @return true if the current element of the left-hand iterator comes after the element of the right-hand iterator
					 */
					bool operator>(const SampleBuffer::Iterator& iterator) const;

					/**
					 * \brief Checks if the left-hand iterators current element comes before the element of the right-hand iterator or are same
					 *
					 * @param iterator The iterator to check with
					 * @return true if the current element of the left-hand iterator comes before the element of the right-hand iterator or they point to the same element
					 */
					bool operator<=(const SampleBuffer::Iterator& iterator) const;

					/**
					 * \brief Checks if the left-hand iterators current element comes after the element of the right-hand iterator or are same
					 *
					 * @param iterator The iterator to check with
					 * @return true if the current element of the left-hand iterator comes after the element of the right-hand iterator or they point to the same element
					 */
					bool operator>=(const SampleBuffer::Iterator& iterator) const;

					/**
					 * \brief gets the sample at the current iterator position
					 *
					 * @return The Sample at the current iterator position
					 */
					const Sample operator*() const;

					/**
					 * \brief gets the sample at the current iterator position and calls one of the samples functions
					 *
					 * @return The Sample at the current iterator position
					 */
					const Sample operator->() const;

					/**
					 * \brief Increments the iterator by one
					 *
					 * @return The Sample at the current iterator position before increase
					 */
					Sample operator++(int);

					/**
					 * \brief Increments the iterator by one
					 *
					 * @return The Sample at the current iterator position after increase
					 */
					Sample operator++();

					/**
					 * \brief Decrements the iterator by one
					 *
					 * @return The Sample at the current iterator position after decrease
					 */
					Sample operator--(int);

					/**
					 * \brief Decrements the iterator by one
					 *
					 * @return The Sample at the current iterator position before decrease
					 */
					Sample operator--();

					/**
					 * \brief Increments the iterator by a given step
					 *
					 * @param step The iterator is increased by `step` steps
					 */
					void operator+=(int step);

					/**
					 * \brief Decrements the iterator by a given step
					 *
					 * @param step The iterator is decreased by `step` steps
					 */
					void operator-=(int step);

					/**
					 * \brief Gets the element `index` steps ahead of the current position
					 *
					 * @param index The index to access
					 */
					Sample operator[](int index) const;
				private:
					float* samples_;
					unsigned int number_of_channels_;
			};

			/**
			 * \brief Gets an iterator pointing to the first element of this buffer
			 *
			 * @return The iterator pointing to the first element
			 */
			Iterator begin() const;

			/**
			 * \brief Gets an iterator pointing to the past-the-end element of this buffer
			 *
			 * Be aware that dereferencing an end iterator will result in undefined behaviour
			 *
			 * @return The iterator pointing to the past-the-end element
			 */
			Iterator end() const;

			/**
			 * \brief Gets an iterator pointing to the element at the given time
			 *
			 * @param time The Time the iterator starts from
			 * @return The iterator pointing to the element at the given time
			 */
			Iterator get_iterator_at(const Time& time) const;

			/**
			 * \brief Gets an iterator pointing to the element at the given second
			 *
			 * @param time The Time the iterator starts from
			 * @return The iterator pointing to the element at the given second
			 */
			Iterator get_iterator_at_second(double second) const;

			// stats
			/**
			 * \brief Gets the samplerate of this buffer
			 *
			 * @return The samplerate of this buffer
			 */
			unsigned int get_samplerate() const;

			/**
			 * \brief Gets the number of channels of this buffer
			 *
			 * @return The number of channels of this buffer
			 */
			unsigned int get_number_of_channels() const;

			/**
			 * \brief Gets if this buffer is empty
			 *
			 * @return true if no samples are loaded. You should not use this buffer. false if samples are loaded
			 */
			bool is_empty() const;

			// Time
			/**
			 * \brief Gets the duration of this buffer
			 *
			 * @return The duration of this buffer
			 */
			Time get_duration() const;

			/**
			 * \brief converts a number of seconds into a Time object
			 *
			 * @param seconds The number of seconds to convert
			 * @return The seconds converted into a Time object
			 */
			Time seconds_to_time(double seconds) const;

			/**
			 * \brief converts a number of samples into a Time object
			 *
			 * @param number_of_samples The number of samples to convert
			 * @return The samples converted into a Time object
			 */
			Time number_of_samples_to_time(size_t number_of_samples) const;

			// Sample
			/**
			 * \brief Gets a sample at a given time
			 *
			 * @param time The Time from where to get the Sample
			 * @param sample The sample into which the asked sample is loaded
			 * @return true if loading was successful, false otherwise
			 */
			bool get_sample_at(const Time& time, Sample* sample) const;

			/**
			 * \brief Gets a sample at a given sample offset
			 *
			 * @param sample_offset The sample offset from where to get the Sample
			 * @param sample The sample into which the asked sample is loaded
			 * @return true if loading was successful, false otherwise
			 */
			bool get_sample(const size_t sample_offset, Sample* sample) const;

			/**
			 * \brief Gets a subsample at a given time
			 *
			 * Gets a subsample at a given time. This method checks against bounds and returns false if out of bounds
			 *
			 * @param time The Time from where to get the Sample
			 * @param number_of_channel The channel number from where to get the subsample
			 * @param subsample The subsample into which the asked subsample is loaded. If false is returned this will be NaN
			 * @return true if loading was successful, false otherwise
			 */
			bool get_subsample_at(const Time& time, unsigned int number_of_channel, float* subsample) const;

			// Channel
			/**
			 * \brief Loads a channel
			 *
			 * Loads Channel into the given out parameter. The channel has own independent memory, so changing the channel will not affect the samples in this buffer.
			 *
			 * @param channel_index The index of the channel to get
			 * @param channel The channel in which the samples are loaded
			 * @return true if loading was successful, false otherwise
			 */
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
	/**
	 * \brief Gets a iterator incremented by `step`
	 *
	 * @param iterator The iterator to increase
	 * @param step The iterator is increased by `step` steps
	 */
	SampleBuffer::Iterator operator+(SampleBuffer::Iterator iterator, int step);

	/**
	 * \brief Gets a iterator decremented by `step`
	 *
	 * @param iterator The iterator to decrease
	 * @param step The iterator is decreased by `step` steps
	 */
	SampleBuffer::Iterator operator-(SampleBuffer::Iterator iterator, int step);
}

#endif
