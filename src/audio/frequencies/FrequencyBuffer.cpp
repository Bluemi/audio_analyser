#include "FrequencyBuffer.hpp"

#include <time/Time.hpp>
#include <time/PartialTime.hpp>
#include <audio/frequencies/FrequencyBlock.hpp>
#include <buffer/Buffer.hpp>

namespace analyser {
	FrequencyBuffer::FrequencyBuffer() {}

	FrequencyBuffer::FrequencyBuffer(unsigned int number_of_channels, size_t number_of_blocks, size_t block_size, unsigned int samplerate)
		: channels_(number_of_channels), number_of_blocks_(number_of_blocks), block_size_(block_size), samplerate_(samplerate)
	{
		for (unsigned int i = 0; i < number_of_channels; i++) {
			channels_[i] = Buffer(number_of_blocks * block_size);
		}
	}

	bool FrequencyBuffer::get_frequency_block(unsigned int channel_index, const PartialTime& time, FrequencyBlock* frequency_block) const
	{
		size_t block_index = time.to_time(samplerate_).get_number_of_samples() / block_size_;
		return get_frequency_block_by_id(channel_index, block_index, frequency_block);
	}

	bool FrequencyBuffer::get_frequency_block_by_id(unsigned int channel_index, size_t block_index, FrequencyBlock* frequency_block) const
	{
		bool success = false;
		if (channel_index < get_number_of_channels() && block_index < number_of_blocks_) {
			success = true;
			size_t block_begin = block_index * block_size_;
			*frequency_block = FrequencyBlock(channels_[channel_index].get_section(block_begin, block_begin + block_size_));
		}
		return success;
	}

	unsigned int FrequencyBuffer::get_number_of_channels() const
	{
		return channels_.size();
	}

	size_t FrequencyBuffer::get_number_of_blocks() const
	{
		return number_of_blocks_;
	}

	size_t FrequencyBuffer::get_block_size() const
	{
		return block_size_;
	}

	float FrequencyBuffer::frequency_to_index(float frequency) const
	{
		return frequency * (2*block_size_) / samplerate_ - 0.5f;
	}

	float FrequencyBuffer::get_frequency_volume(unsigned int channel_index, float frequency) const
	{
		float index = frequency_to_index(frequency);
		int abs_index = (int) index;
		float abs_percentage = 1.f - (index - abs_index);
		float* data = channels_[channel_index].get_data();
		return data[abs_index] * abs_percentage + data[abs_index+1] * (1.f - abs_percentage);
	}
}
