#include "SampleSource.hpp"

namespace analyser {

	class Overloader {
		public:
			unsigned int operator()(const std::monostate&) {
				return 0;
			}

			unsigned int operator()(const SampleBuffer& sample_buffer) {
				return sample_buffer.get_samplerate();
			}
	};

	unsigned int get_samplerate(const SampleSource& sample_source)
	{
		return std::visit(Overloader(), sample_source);
	}
}
