#ifndef __AUDIOFILE_CLASS__
#define __AUDIOFILE_CLASS__

#include <sndfile.h>

#include <time/FrameTime.hpp>
#include <time/Time.hpp>
#include <SampleIterator.hpp>
#include <channels/Channels.hpp>

class AudioFile
{
	public:
		static AudioFile fromPath(const char* path);
		~AudioFile();
		AudioFile();
		float getLoudness_diff(Time offset, Time duration) const;
		float getLoudness_diff(Time offset, Time duration, StereoChannel channel) const;
		float getLoudness_sum(Time offset, Time duration) const;
		float getLoudness_sum(Time offset, Time duration, StereoChannel channel) const;
		Time toTime(const FrameTime &frameTime) const;
		Time toTime(const SecondsTime &secondsTime) const;
		Time secondsToTime(float seconds) const;
		Time frameCountToTime(size_t frameCount) const;
		void print() const;
		Time getDuration() const;
		size_t getMemSize() const;
		SampleIterator getIteratorFrom(const Time offset_frame, StereoChannel channel) const;
	private:
		AudioFile(SNDFILE *f, float *samp, Time &dur, unsigned int channelc);
		SNDFILE *file;
		float *samples;
		bool valid;
		Time duration;
		unsigned int channelCount;
};

#endif
