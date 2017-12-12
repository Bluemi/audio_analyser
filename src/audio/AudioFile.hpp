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

class AudioFile
{
	public:
		static AudioFile fromPath(const char* path);
		~AudioFile();
		AudioFile();

		// Loudness -----------------------------------------------
		float getLoudness_diff(Time offset, Time duration) const;
		float getLoudness_diff(Time offset, Time duration, StereoChannel channel) const;
		float getLoudness_sum(Time offset, Time duration) const;
		float getLoudness_sum(Time offset, Time duration, StereoChannel channel) const;
		float getLoudness_grade(Time offset, Time duration, StereoChannel channel) const;
		float getLoudness_grade(Time offset, Time duration) const;

		// Time ---------------------------------------------------
		Time toTime(const FrameTime &frameTime) const;
		Time toTime(const SecondsTime &secondsTime) const;
		Time secondsToTime(float seconds) const;
		Time frameCountToTime(size_t frameCount) const;
		Time getDuration() const;

		// Frequency - Subbands -----------------------------------
		// calculates the loudness of <num_of_subbands> frequency Subbands from 0 Hz to 22050 Hz
		// std::vector<float> getFrequencySubbands(const Time &offset, const Time &duration, int num_of_subbands) const;
		// calculates the loudness of <bounds.size()-1> subbands
		// each sector will be restricted by bounds[n] and bounds[n+1]
		std::vector<float> getFrequencySubbands(const Time &offset, const Time &duration, Grouper* grouper) const;

		std::vector<float> getScaledFrequencySubbands(const Time &offset, const Time &duration) const;

		// misc ---------------------------------------------------
		void print() const;
		size_t getMemSize() const;
		SampleIterator getIteratorFrom(const Time offset_frame, StereoChannel channel) const;

		static constexpr float FREQUENCIES_SHARE() { return 1.f; };
	private:
		static sf_count_t loadSamples(SNDFILE *file, float *samples, const sf_count_t frames);

		AudioFile(SNDFILE *f, float* samp, Time &dur, unsigned int channelc, unsigned int srate);
		SNDFILE *file;
		float* samples;
		bool valid;
		Time duration;
		unsigned int channelCount;
		unsigned int samplerate;
};

#endif
