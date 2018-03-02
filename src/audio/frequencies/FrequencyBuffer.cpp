#include "FrequencyBuffer.hpp"

#include <time/Time.hpp>
#include <buffer/BufferSection.hpp>
#include <audio/frequencies/FrequencyBlock.hpp>

namespace analyser {
	FrequencyBuffer::FrequencyBuffer() {}

	FrequencyBuffer::FrequencyBuffer(unsigned int number_of_channels, size_t number_of_blocks, size_t block_size)
		: channels_(number_of_channels), number_of_blocks_(number_of_blocks), block_size_(block_size)
	{
		for (unsigned int i = 0; i < number_of_channels; i++) {
			channels_[i] = Buffer(number_of_blocks * block_size);
		}
	}

	bool FrequencyBuffer::get_frequency_block(unsigned int channel_index, const Time& time, FrequencyBlock* frequency_block) const
	{
		bool success = false;
		size_t block_index = time.get_number_of_samples() / block_size_;
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
}
