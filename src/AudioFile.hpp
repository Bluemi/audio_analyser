#ifndef __AUDIOFILE_CLASS__
#define __AUDIOFILE_CLASS__

#include <sndfile.h>
#include <vector>
#include <fftw3.h>

#include <time/FrameTime.hpp>
#include <time/Time.hpp>
#include <SampleIterator.hpp>
#include <channels/Channels.hpp>

template <typename SampleType>
class AudioFile
{
	public:
		static AudioFile fromPath(const char* path);
		~AudioFile();
		AudioFile();
		// Loudness
		float getLoudness_diff(Time offset, Time duration) const;
		float getLoudness_diff(Time offset, Time duration, StereoChannel channel) const;
		float getLoudness_sum(Time offset, Time duration) const;
		float getLoudness_sum(Time offset, Time duration, StereoChannel channel) const;
		float getLoudness_grade(Time offset, Time duration, StereoChannel channel) const;
		float getLoudness_grade(Time offset, Time duration) const;
		// Time
		Time toTime(const FrameTime &frameTime) const;
		Time toTime(const SecondsTime &secondsTime) const;
		Time secondsToTime(float seconds) const;
		Time frameCountToTime(size_t frameCount) const;
		Time getDuration() const;
		// Frequency
		std::vector<float> getFrequencySubbands(const Time &offset, const Time &duration, int num_of_subbands) const;
		// misc
		void print() const;
		size_t getMemSize() const;
		SampleIterator<SampleType> getIteratorFrom(const Time offset_frame, StereoChannel channel) const;

		static constexpr float FREQUENCIES_SHARE() { return 1.f; };
		static constexpr float SHORT_COEFFICIENT();
	private:
		static sf_count_t loadSamples(SNDFILE *file, SampleType *samples, const sf_count_t frames);

		AudioFile(SNDFILE *f, SampleType *samp, Time &dur, unsigned int channelc);
		SNDFILE *file;
		SampleType *samples;
		bool valid;
		Time duration;
		unsigned int channelCount;
};

#endif
