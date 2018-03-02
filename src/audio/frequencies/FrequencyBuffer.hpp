#ifndef __FREQUENCYBUFFER_CLASS__
#define __FREQUENCYBUFFER_CLASS__

#include <cstddef>
#include <vector>

#include <buffer/Buffer.hpp>

namespace analyser {
	class FrequencyBlock;
	class Time;

	class FrequencyBuffer
	{
		public:
			FrequencyBuffer();
			FrequencyBuffer(unsigned int number_of_channels, size_t number_of_blocks, size_t block_size);

			bool get_frequency_block(unsigned int channel_index, const Time& time, FrequencyBlock* frequency_block) const;
			bool get_frequency_block_by_id(unsigned int channel_index, size_t block_index, FrequencyBlock* frequency_block) const;
			unsigned int get_number_of_channels() const;

		private:
			std::vector<Buffer> channels_;
			size_t number_of_blocks_;
			size_t block_size_;
	};
}

#endif
