#ifndef __FREQUENCYBUFFER_CLASS__
#define __FREQUENCYBUFFER_CLASS__

#include <cstddef>

#include <buffer/Buffer.hpp>

namespace analyser {
	class FrequencyBuffer
	{
		public:
			FrequencyBuffer();
			FrequencyBuffer(size_t size);

		private:
			Buffer buffer_;
	};
}

#endif
