#ifndef __AUDIOFILE_CLASS__
#define __AUDIOFILE_CLASS__

#include <sndfile.h>

#include <time/FrameTime.hpp>
#include <SampleIterator.hpp>
#include <channels/Channels.hpp>

class AudioFile
{
	public:
		static AudioFile fromPath(const char* path);
		~AudioFile();
		float getLoudness_diff(FrameTime offset, FrameTime duration) const;
		float getLoudness_diff(FrameTime offset, FrameTime duration, StereoChannel channel) const;
		float getLoudness_sum(FrameTime offset, FrameTime duration) const;
		float getLoudness_sum(FrameTime offset, FrameTime duration, StereoChannel channel) const;
		void print() const;
		FrameTime getDuration() const;
		size_t getMemSize() const;
		SampleIterator getIteratorFrom(const FrameTime offset_frame, StereoChannel channel) const;
	private:
		AudioFile(SNDFILE *f, float *samp, FrameTime &dur, const unsigned int framert, const unsigned int channelc);
		AudioFile();
		SNDFILE *file;
		float *samples;
		bool valid;
		FrameTime duration;
		unsigned int framerate;
		unsigned int channelCount;
};

#endif
