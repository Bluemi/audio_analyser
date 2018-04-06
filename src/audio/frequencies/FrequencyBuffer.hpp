#ifndef __FREQUENCYBUFFER_CLASS__
#define __FREQUENCYBUFFER_CLASS__

#include <cstddef>
#include <vector>

namespace analyser {
	class FrequencyBlock;
	class Time;
	class PartialTime;
	class Buffer;

	class FrequencyBuffer
	{
		public:
			FrequencyBuffer();
			FrequencyBuffer(unsigned int number_of_channels, size_t number_of_blocks, size_t block_size, unsigned int samplerate);

			bool get_frequency_block(unsigned int channel_index, const PartialTime& time, FrequencyBlock* frequency_block) const;
			bool get_frequency_block_by_id(unsigned int channel_index, size_t block_index, FrequencyBlock* frequency_block) const;
			unsigned int get_number_of_channels() const;
			size_t get_number_of_blocks() const;
			size_t get_block_size() const;

		private:
			std::vector<Buffer> channels_;
			size_t number_of_blocks_;
			size_t block_size_;
			unsigned int samplerate_;
	};
}

#endif
