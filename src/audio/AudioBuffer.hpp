#ifndef __AUDIOFILE_CLASS__
#define __AUDIOFILE_CLASS__

#include <sndfile.h>
#include <vector>
#include <fftw3.h>

#include <time/FrameTime.hpp>
#include <time/Time.hpp>
#include <audio/SampleIterator.hpp>
#include <channels/Channels.hpp>
#include <math/Grouper.hpp>

namespace analyser {
	class AudioBuffer
	{
		public:
			static bool load_from_file(const char* path, AudioBuffer* buffer);
			~AudioBuffer();
			AudioBuffer();

			unsigned int get_samplerate() const;
			unsigned int get_number_of_channels() const;
			bool is_empty() const;
			Time get_duration() const;

			/*
			// Time ---------------------------------------------------
			Time toTime(const FrameTime &frameTime) const;
			Time toTime(const SecondsTime &secondsTime) const;
			Time secondsToTime(float seconds) const;
			Time frameCountToTime(size_t frameCount) const;
			Time getDuration() const;

			// misc ---------------------------------------------------
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
