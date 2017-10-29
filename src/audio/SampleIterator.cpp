#include "SampleIterator.hpp"

template <typename SampleType>
const unsigned int SampleIterator<SampleType>::STEREO_CHANNEL_NUMBER = 2;

template <typename SampleType>
SampleIterator<SampleType>::SampleIterator(SampleType *samples, size_t frame_offset, size_t frame_size, StereoChannel channel)
	: samples(samples), iter(frame_offset), size(frame_size), channel(channel)
{
	if (iter >= size)
		iter = size-1;
}

template <typename SampleType>
SampleType SampleIterator<SampleType>::get() const
{
	return samples[iter * STEREO_CHANNEL_NUMBER + channel];
}

template <typename SampleType>
void SampleIterator<SampleType>::operator++()
{
	iter += STEREO_CHANNEL_NUMBER;
	if (iter >= size)
		iter = size-1;
}

template <typename SampleType>
void SampleIterator<SampleType>::operator--()
{
	iter -= STEREO_CHANNEL_NUMBER;
	if (iter < 0)
		iter = 0;
}

template <typename SampleType>
SampleIterator<SampleType> SampleIterator<SampleType>::operator+(const int i) const
{
	return SampleIterator<SampleType>(samples, iter+STEREO_CHANNEL_NUMBER*i, size, channel);
}

template <typename SampleType>
size_t SampleIterator<SampleType>::getArrayAccessPoint() const
{
	return iter*STEREO_CHANNEL_NUMBER + channel;
}

template class SampleIterator<float>;
template class SampleIterator<short>;
