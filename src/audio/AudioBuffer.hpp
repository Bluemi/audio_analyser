#ifndef __AUDIOFILE_CLASS__
#define __AUDIOFILE_CLASS__

#include <sndfile.h>
#include <vector>
#include <fftw3.h>

#include <time/Time.hpp>
#include <audio/Sample.hpp>

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
					Iterator(float* samples, size_t initial_offset, unsigned int number_of_channels, size_t number_of_samples);
					Iterator& operator=(const Iterator& original) = default;

					bool is_end() const;

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

					Iterator operator+(const Iterator&) const;
					Iterator operator-(const Iterator&) const;

					Sample operator[](int index) const;
				private:
					float* samples_;
					size_t position_;
					unsigned int number_of_channels_;
					size_t number_of_samples_;
			};

			// stats
			unsigned int get_samplerate() const;
			unsigned int get_number_of_channels() const;
			bool is_empty() const;

			// Time ---------------------------------------------------
			Time get_duration() const;
			Time seconds_to_time(double seconds) const;
			Time number_of_samples_to_time(size_t number_of_samples) const;

			// Samples
			bool get_sample_at(const Time& time, Sample* sample) const;
			bool get_sample(const size_t sample_offset, Sample* sample) const;

			// misc ---------------------------------------------------
			/*
			size_t getMemSize() const;
			Iterator getIteratorFrom(const Time offset_frame, StereoChannel channel) const;
			*/
		private:
			static size_t loadSamples(SNDFILE *file, float *samples, const sf_count_t frames);
			void delete_samples();

			float* samples_;
			bool empty_;
			unsigned int number_of_channels_;
			unsigned int samplerate_;
			size_t number_of_samples_;
	};

	// Iterator Functions
	AudioBuffer::Iterator operator+(AudioBuffer::Iterator iterator, int step);
	AudioBuffer::Iterator operator+(int step, AudioBuffer::Iterator iterator);

	AudioBuffer::Iterator operator-(AudioBuffer::Iterator iterator, int step);
	AudioBuffer::Iterator operator-(int step, AudioBuffer::Iterator iterator);
}

#endif
