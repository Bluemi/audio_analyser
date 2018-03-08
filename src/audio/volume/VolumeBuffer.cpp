#include "VolumeBuffer.hpp"

namespace analyser {
	VolumeBuffer::VolumeBuffer()
		: number_of_volumes_(0)
	{}

	VolumeBuffer::VolumeBuffer(unsigned int number_of_channels, size_t number_of_volumes)
		: channels_(number_of_channels), number_of_volumes_(number_of_volumes)
	{
		for (unsigned int i = 0; i < number_of_channels; i++) {
			channels_[i] = Buffer(number_of_volumes);
		}
	}

	float* VolumeBuffer::get_volumes(unsigned int channel_index) const
	{
		return channels_[channel_index].get_data();
	}

	size_t VolumeBuffer::get_number_of_volumes() const
	{
		return number_of_volumes_;
	}
}
