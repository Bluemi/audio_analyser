#ifndef __FREQUENCYBLOCK_CLASS__
#define __FREQUENCYBLOCK_CLASS__

#include <buffer/BufferSection.hpp>

namespace analyser {
	class FrequencyBlock
	{
		public:
			FrequencyBlock();
			FrequencyBlock(const BufferSection& buffer_section);

			float* get_frequencies() const;
			size_t get_size() const;
		private:
			BufferSection buffer_section_;
	};
}

#endif
