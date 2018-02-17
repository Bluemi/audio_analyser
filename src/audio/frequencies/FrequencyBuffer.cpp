#include "FrequencyBuffer.hpp"

namespace analyser {
	FrequencyBuffer::FrequencyBuffer() {}

	FrequencyBuffer::FrequencyBuffer(unsigned int number_of_channels, size_t size) : channels_(number_of_channels) {
		for (unsigned int i = 0; i < number_of_channels; i++) {
			channels_[i] = Buffer(size);
		}
	}

	bool FrequencyBuffer::get_frequencies(unsigned int channel_index, Buffer* buffer) const {
		bool success = true;
		if (channel_index >= get_number_of_channels()) {
			success = false;
		} else {
			*buffer = channels_[channel_index];
		}
		return success;
	}

	unsigned int FrequencyBuffer::get_number_of_channels() const {
		return channels_.size();
	}
}
