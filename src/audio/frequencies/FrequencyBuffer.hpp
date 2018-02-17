#ifndef __FREQUENCYBUFFER_CLASS__
#define __FREQUENCYBUFFER_CLASS__

#include <cstddef>

#include <buffer/Buffer.hpp>
#include <vector>

namespace analyser {
	class FrequencyBuffer
	{
		public:
			FrequencyBuffer();
			FrequencyBuffer(unsigned int number_of_channels, size_t size);

			bool get_frequencies(unsigned int channel_index, Buffer* buffer) const;
			unsigned int get_number_of_channels() const;

		private:
			std::vector<Buffer> channels_;
	};
}

#endif
