#include "AudioFile.hpp"

#include <misc/Debug.hpp>
#include <iostream>
#include <cmath>

#include <math/MathFunctions.hpp>

AudioFile AudioFile::fromPath(const char* path)
{
	SF_INFO info;
	info.format = 0;

	SNDFILE *file = sf_open(path, SFM_READ, &info);
	if (file == nullptr)
	{
		Debug::out << Debug::error << "could not read from file \"" << path << "\"" << Debug::endl;
		return AudioFile();
	}

	const unsigned int channelCount = info.channels;
	if (channelCount != 2)
	{
		Debug::out << Debug::warn << "AudioFile::fromPath(): File \"" << path << "\" has only " << channelCount << " channels" << Debug::endl;
	}
	const size_t sampleCount = info.frames * channelCount;
	Time duration = Time::fromFrameCount(info.frames, info.samplerate);
	float *samples = (float*)::operator new(sizeof(float) * sampleCount);
	if (sf_readf_float(file, samples, info.frames) != info.frames)
	{
		Debug::out << Debug::warn << "AudioFile::AudioFile(): info.frames(" << info.frames << ") != sf_readf_float()" << Debug::endl;
	}
	return AudioFile(file, samples, duration, channelCount);
}

AudioFile::AudioFile(SNDFILE *f, float *samp, Time &dur, unsigned int channelc)
	: file(f), samples(samp), valid(true), duration(dur), channelCount(channelc)
{}

AudioFile::AudioFile()
       : valid(false), duration(Time::fromFrameCount(0, 0))
{
       Debug::out << Debug::error << "invalid file created" << Debug::endl;
}

AudioFile::~AudioFile()
{
	if (valid)
	{
		sf_close(file);
		delete samples;
	}
}

float AudioFile::getLoudness_diff(Time offset, Time duration) const
{
	return (getLoudness_diff(offset, duration, StereoChannel::LEFT) + getLoudness_diff(offset, duration, StereoChannel::RIGHT)) / 2.f;
}

float AudioFile::getLoudness_diff(Time offset, Time duration, StereoChannel channel) const
{
	SampleIterator iter = getIteratorFrom(offset, channel);
	float max = iter.get();
	float min = iter.get();
	for (size_t i = 0; i < duration.getFrameCount(); i++, ++iter)
	{
		const float val = iter.get();
		if (val < min)
			min = val;
		if (val > max)
			max = val;
	}
	return max - min;
}

const float LOUDNESS_SUM_SCALE = 0.002f;

float AudioFile::getLoudness_sum(Time offset, Time duration) const
{
	return (getLoudness_sum(offset, duration, StereoChannel::LEFT) + getLoudness_sum(offset, duration, StereoChannel::RIGHT)) / 2.f;
}

float AudioFile::getLoudness_sum(Time offset, Time duration, StereoChannel channel) const
{
	SampleIterator iter = getIteratorFrom(offset, channel);
	float sum = 0.f;
	SampleIterator last = iter;
	bool next_point_high = last.get() < (iter+1).get();
	SampleIterator last_extrem_point_index = iter;
	for (size_t i = 0; i < duration.getFrameCount(); i++, ++iter)
	{
		if (next_point_high)
		{
			if (last.get() > iter.get())
			{
				sum += std::abs(last_extrem_point_index.get() - iter.get());
				last_extrem_point_index = iter;
				next_point_high = false;
			}
		} else {
			if (last.get() < iter.get())
			{
				sum += std::abs(last_extrem_point_index.get() - iter.get());
				last_extrem_point_index = iter;
				next_point_high = true;
			}
		}

		last = iter;
	}
	return sum / duration.getSeconds() * LOUDNESS_SUM_SCALE;
}

const float LOUDNESS_GRADE_SCALE = 24.f;

float AudioFile::getLoudness_grade(Time offset, Time duration) const
{
	return (getLoudness_grade(offset, duration, StereoChannel::LEFT) + getLoudness_grade(offset, duration, StereoChannel::RIGHT)) / 2.f;
}

const unsigned int PEAK_WIDTH = 10;

float AudioFile::getLoudness_grade(Time offset, Time duration, StereoChannel channel) const
{
	float sum = 0.f;
	SampleIterator iter = getIteratorFrom(offset, channel);
	SampleIterator start = iter;
	for (size_t i = 0; i < PEAK_WIDTH; i++)
	{
		sum += std::abs(iter.get() - (iter+1).get());
	}
	SampleIterator end = start + PEAK_WIDTH;
	float max_sum = sum;
	for (size_t i = 0; i < duration.getFrameCount() - PEAK_WIDTH - 1; i++, ++start, ++end)
	{
		sum -= std::abs(start.get() - (start+1).get());
		sum += std::abs(end.get() - (end+1).get());
		if (sum > max_sum)
			max_sum = sum;
	}
	return max_sum / PEAK_WIDTH * LOUDNESS_GRADE_SCALE;
}

Time AudioFile::toTime(const FrameTime &frameTime) const
{
	return Time::fromFrameTime(frameTime, duration.getFramerate());
}

Time AudioFile::toTime(const SecondsTime &secondsTime) const
{
	return Time::fromSecondsTime(secondsTime, duration.getFramerate());
}

Time AudioFile::secondsToTime(float seconds) const
{
	return Time::fromSeconds(seconds, duration.getFramerate());
}

Time AudioFile::frameCountToTime(size_t frameCount) const
{
	return Time::fromFrameCount(frameCount, duration.getFramerate());
}

void AudioFile::print() const
{
	Debug::out << "duration: " << duration.getSeconds() << Debug::endl;
}

Time AudioFile::getDuration() const
{
	return duration;
}

std::vector<float> AudioFile::getFrequencySubbands(const Time &offset, const Time &duration, int num_of_subbands) const
{
	std::vector<float> frequencies_left = modifiedDiscreteCosineTransformation(getIteratorFrom(offset, StereoChannel::LEFT), duration, FREQUENCIES_SHARE());
	std::vector<float> frequencies_right = modifiedDiscreteCosineTransformation(getIteratorFrom(offset, StereoChannel::RIGHT), duration, FREQUENCIES_SHARE());

	std::vector<float> frequencies(frequencies_left.size());
	for (unsigned int i = 0; i < frequencies.size(); i++)
	{
		frequencies[i] = (std::abs(frequencies_left[i]) + std::abs(frequencies_right[i])) / 2.f;
	}

	return group(frequencies, num_of_subbands);
}

size_t AudioFile::getMemSize() const
{
	return duration.getFrameCount() * channelCount;
}

SampleIterator AudioFile::getIteratorFrom(const Time frame_offset, StereoChannel channel) const
{
	return SampleIterator(samples, frame_offset.getFrameCount(), duration.getFrameCount(), channel);
}
