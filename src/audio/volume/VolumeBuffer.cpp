#include "VolumeBuffer.hpp"

#include <time/Time.hpp>

namespace analyser {
	VolumeBuffer::VolumeBuffer()
		: number_of_volumes_(0), block_size_(0)
	{}

	VolumeBuffer::VolumeBuffer(unsigned int number_of_channels, size_t number_of_volumes, size_t block_size, unsigned int samplerate)
		: channels_(number_of_channels), number_of_volumes_(number_of_volumes), block_size_(block_size), samplerate_(samplerate)
	{
		for (unsigned int i = 0; i < number_of_channels; i++) {
			channels_[i] = Buffer(number_of_volumes);
		}
	}

	float* VolumeBuffer::get_volumes(unsigned int channel_index) const
	{
		return channels_[channel_index].get_data();
	}

	float VolumeBuffer::get_volume_at(unsigned int channel_index, const Time& time) const
	{
		return get_volume(channel_index, time.get_number_of_samples() / block_size_);
	}

	float VolumeBuffer::get_volume(unsigned int channel_index, size_t volume_index) const
	{
		return channels_[channel_index].get_data()[volume_index];
	}

	size_t VolumeBuffer::get_number_of_volumes() const
	{
		return number_of_volumes_;
	}

	unsigned int VolumeBuffer::get_number_of_channels() const
	{
		return channels_.size();
	}

	size_t VolumeBuffer::get_block_size() const
	{
		return block_size_;
	}

	Time VolumeBuffer::seconds_to_time(double seconds) const
	{
		return Time::from_seconds(seconds, samplerate_);
	}

	Time VolumeBuffer::number_of_samples_to_time(size_t number_of_samples) const
	{
		return Time::from_number_of_samples(number_of_samples, samplerate_);
	}
}
