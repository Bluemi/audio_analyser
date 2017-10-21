#include "AudioFile.hpp"

#include <misc/Debug.hpp>
#include <iostream>
#include <cmath>

#include <math/MathFunctions.hpp>

template <typename SampleType>
AudioFile<SampleType> AudioFile<SampleType>::fromPath(const char* path)
{
	SF_INFO info;
	info.format = 0;

	SNDFILE *file = sf_open(path, SFM_READ, &info);
	if (file == nullptr)
	{
		Debug::out << Debug::error << "could not read from file \"" << path << "\"" << Debug::endl;
		return AudioFile<SampleType>();
	}

	const unsigned int channelCount = info.channels;
	if (channelCount != 2)
	{
		Debug::out << Debug::warn << "AudioFile::fromPath(): File \"" << path << "\" has only " << channelCount << " channels" << Debug::endl;
	}
	const size_t sampleCount = info.frames * channelCount;
	Time duration = Time::fromFrameCount(info.frames, info.samplerate);
	SampleType *samples = (SampleType*)::operator new(sizeof(SampleType) * sampleCount);
	if (loadSamples(file, samples, info.frames) != info.frames)
	{
		Debug::out << Debug::warn << "AudioFile::AudioFile(): info.frames(" << info.frames << "differs with the result of READ_FUNCTION" << Debug::endl;
	}
	return AudioFile<SampleType>(file, samples, duration, channelCount);
}

template<>
sf_count_t AudioFile<float>::loadSamples(SNDFILE *file, float *samples, const sf_count_t frames)
{
	return sf_readf_float(file, samples, frames);
}

template<>
sf_count_t AudioFile<short>::loadSamples(SNDFILE *file, short *samples, const sf_count_t frames)
{
	return sf_readf_short(file, samples, frames);
}

template <typename SampleType>
AudioFile<SampleType>::AudioFile(SNDFILE *f, SampleType *samp, Time &dur, unsigned int channelc)
	: file(f), samples(samp), valid(true), duration(dur), channelCount(channelc)
{}

template <typename SampleType>
AudioFile<SampleType>::AudioFile()
       : valid(false), duration(Time::fromFrameCount(0, 0))
{
       Debug::out << Debug::error << "invalid file created" << Debug::endl;
}

template <typename SampleType>
AudioFile<SampleType>::~AudioFile()
{
	if (valid)
	{
		sf_close(file);
		delete samples;
	}
}

template <typename SampleType>
float AudioFile<SampleType>::getLoudness_diff(Time offset, Time duration) const
{
	return (getLoudness_diff(offset, duration, StereoChannel::LEFT) + getLoudness_diff(offset, duration, StereoChannel::RIGHT)) / 2.f;
}

template <typename SampleType>
float AudioFile<SampleType>::getLoudness_diff(Time offset, Time duration, StereoChannel channel) const
{
	SampleIterator<SampleType> iter = getIteratorFrom(offset, channel);
	SampleType max = iter.get();
	SampleType min = iter.get();
	for (size_t i = 0; i < duration.getFrameCount(); i++, ++iter)
	{
		const SampleType val = iter.get();
		if (val < min)
			min = val;
		if (val > max)
			max = val;
	}
	return (max - min) * SHORT_COEFFICIENT();
}

const float LOUDNESS_SUM_SCALE = 0.002f;

template <typename SampleType>
float AudioFile<SampleType>::getLoudness_sum(Time offset, Time duration) const
{
	return (getLoudness_sum(offset, duration, StereoChannel::LEFT) + getLoudness_sum(offset, duration, StereoChannel::RIGHT)) / 2.f;
}

template <typename SampleType>
float AudioFile<SampleType>::getLoudness_sum(Time offset, Time duration, StereoChannel channel) const
{
	SampleIterator<SampleType> iter = getIteratorFrom(offset, channel);
	float sum = 0.f;
	SampleIterator<SampleType> last = iter;
	bool next_point_high = last.get() < (iter+1).get();
	SampleIterator<SampleType> last_extrem_point_index = iter;
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
	return (sum / duration.getSeconds() * LOUDNESS_SUM_SCALE) * SHORT_COEFFICIENT();
}

const float LOUDNESS_GRADE_SCALE = 24.f;

template <typename SampleType>
float AudioFile<SampleType>::getLoudness_grade(Time offset, Time duration) const
{
	return (getLoudness_grade(offset, duration, StereoChannel::LEFT) + getLoudness_grade(offset, duration, StereoChannel::RIGHT)) / 2.f;
}

const unsigned int PEAK_WIDTH = 10;

template <typename SampleType>
float AudioFile<SampleType>::getLoudness_grade(Time offset, Time duration, StereoChannel channel) const
{
	SampleType sum = 0.f;
	SampleIterator<SampleType> iter = getIteratorFrom(offset, channel);
	SampleIterator<SampleType> start = iter;
	for (size_t i = 0; i < PEAK_WIDTH; i++)
	{
		sum += std::abs(iter.get() - (iter+1).get());
	}
	SampleIterator<SampleType> end = start + PEAK_WIDTH;
	SampleType max_sum = sum;
	for (size_t i = 0; i < duration.getFrameCount() - PEAK_WIDTH - 1; i++, ++start, ++end)
	{
		sum -= std::abs(start.get() - (start+1).get());
		sum += std::abs(end.get() - (end+1).get());
		if (sum > max_sum)
			max_sum = sum;
	}
	return (max_sum / PEAK_WIDTH * LOUDNESS_GRADE_SCALE) * SHORT_COEFFICIENT();
}

template <typename SampleType>
Time AudioFile<SampleType>::toTime(const FrameTime &frameTime) const
{
	return Time::fromFrameTime(frameTime, duration.getFramerate());
}

template <typename SampleType>
Time AudioFile<SampleType>::toTime(const SecondsTime &secondsTime) const
{
	return Time::fromSecondsTime(secondsTime, duration.getFramerate());
}

template <typename SampleType>
Time AudioFile<SampleType>::secondsToTime(float seconds) const
{
	return Time::fromSeconds(seconds, duration.getFramerate());
}

template <typename SampleType>
Time AudioFile<SampleType>::frameCountToTime(size_t frameCount) const
{
	return Time::fromFrameCount(frameCount, duration.getFramerate());
}

template <typename SampleType>
void AudioFile<SampleType>::print() const
{
	Debug::out << "duration: " << duration.getSeconds() << Debug::endl;
	int i = 0;
	for (SampleIterator<SampleType> iter = getIteratorFrom(secondsToTime(2), StereoChannel::RIGHT); i < 100; i++)
	{
		std::cout << (iter+i).get() << std::endl;
	}
}

template <typename SampleType>
Time AudioFile<SampleType>::getDuration() const
{
	return duration;
}

template <typename SampleType>
std::vector<float> AudioFile<SampleType>::getFrequencySubbands(const Time &offset, const Time &duration, int num_of_subbands) const
{
	std::vector<float> frequencies_left = modifiedDiscreteCosineTransformation(getIteratorFrom(offset, StereoChannel::LEFT), duration, FREQUENCIES_SHARE());
	std::vector<float> frequencies_right = modifiedDiscreteCosineTransformation(getIteratorFrom(offset, StereoChannel::RIGHT), duration, FREQUENCIES_SHARE());

	std::vector<float> frequencies(frequencies_left.size());
	for (unsigned int i = 0; i < frequencies.size(); i++)
	{
		frequencies[i] = ((std::abs(frequencies_left[i]) + std::abs(frequencies_right[i])) / 2.f) * SHORT_COEFFICIENT();
	}

	return group(frequencies, num_of_subbands);
}

template <typename SampleType>
size_t AudioFile<SampleType>::getMemSize() const
{
	return duration.getFrameCount() * channelCount;
}

template <typename SampleType>
SampleIterator<SampleType> AudioFile<SampleType>::getIteratorFrom(const Time frame_offset, StereoChannel channel) const
{
	return SampleIterator<SampleType>(samples, frame_offset.getFrameCount(), duration.getFrameCount(), channel);
}

template<>
constexpr float AudioFile<float>::SHORT_COEFFICIENT()
{
	return 1.f;
}

template<>
constexpr float AudioFile<short>::SHORT_COEFFICIENT()
{
	return 1.f/65000.f;
}

template class AudioFile<float>;
template class AudioFile<short>;
