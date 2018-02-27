#ifndef __FREQUENCYBLOCK_CLASS__
#define __FREQUENCYBLOCK_CLASS__

#include <buffer/Buffer.hpp>

namespace analyser {
	class FrequencyBlock
	{
		public:
			FrequencyBlock(const Buffer& buffer, float max_frequency);

			float get_frequency(float frequency) const;
		private:
			Buffer buffer_;
			float max_frequency_;
	};
}

#endif
