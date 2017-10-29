#ifndef __SAMPLEITERATOR_CLASS__
#define __SAMPLEITERATOR_CLASS__

/*
	A Frame contains 2 samples. One Sample for left and one for right.

	+---------------------+
	|        Frame        |
	+----------+----------+
	| Sample L | Sample R |
	+----------+----------+
*/

#include <cstring>

#include <channels/Channels.hpp>

template <typename SampleType>
class SampleIterator
{
	public:
		SampleIterator(SampleType *samples, size_t frame_offset, size_t frame_size, StereoChannel channel);
		SampleIterator(const SampleIterator&) = default;
		SampleIterator& operator=(const SampleIterator&) = default;

		SampleType get() const;
		void operator++();
		void operator--();
		SampleIterator operator+(const int i) const;

		static const unsigned int STEREO_CHANNEL_NUMBER;
	private:
		size_t getArrayAccessPoint() const;
		SampleType *samples;
		// the index of the current frame
		size_t iter;
		// the number of frames
		size_t size;
		StereoChannel channel;
};

#endif
