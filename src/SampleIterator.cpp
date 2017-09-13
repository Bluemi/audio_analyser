#include "SampleIterator.hpp"

const unsigned int SampleIterator::STEREO_CHANNEL_NUMBER = 2;

SampleIterator::SampleIterator(float *samples, size_t frame_offset, size_t frame_size, StereoChannel channel)
	: samples(samples), iter(frame_offset), size(frame_size), channel(channel)
{
	if (iter >= size)
		iter = size-1;
}

float SampleIterator::get() const
{
	return samples[iter * STEREO_CHANNEL_NUMBER + channel];
}

void SampleIterator::operator++()
{
	iter += STEREO_CHANNEL_NUMBER;
	if (iter >= size)
		iter = size-1;
}

void SampleIterator::operator--()
{
	iter -= STEREO_CHANNEL_NUMBER;
	if (iter < 0)
		iter = 0;
}

SampleIterator SampleIterator::operator+(const int i) const
{
	return SampleIterator(samples, iter+STEREO_CHANNEL_NUMBER*i, size, channel);
}

size_t SampleIterator::getArrayAccessPoint() const
{
	return iter*2 + channel;
}
