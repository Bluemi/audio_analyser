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

			// stats
			unsigned int get_samplerate() const;
			unsigned int get_number_of_channels() const;
			bool is_empty() const;

			// Time ---------------------------------------------------
			Time get_duration() const;
			Time seconds_to_time(double seconds) const;
			Time number_of_samples_to_time(size_t number_of_samples) const;

			// Samples
			Sample get_sample_at(const Time& time) const;
			Sample get_sample(const size_t sample_offset) const;

			// misc ---------------------------------------------------
			/*
			size_t getMemSize() const;
			SampleIterator getIteratorFrom(const Time offset_frame, StereoChannel channel) const;
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
}

#endif
