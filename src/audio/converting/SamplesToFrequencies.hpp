#ifndef __SAMPLESTOFREQUENCIES_CLASS__
#define __SAMPLESTOFREQUENCIES_CLASS__

#include <variant>

#include <audio/buffer/SampleBuffer.hpp>

namespace analyser {
	class SamplesToFrequencies
	{
		public:
			SamplesToFrequencies();
			SamplesToFrequencies(const SampleBuffer& buffer);
			void bind(const SampleBuffer& buffer);
			void clear();
		private:
			using SampleSourceVariant = std::variant<std::monostate, SampleBuffer>;

			SampleSourceVariant sample_source_;
	};
}

#endif
