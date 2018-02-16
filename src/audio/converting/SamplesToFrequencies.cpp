#include "SamplesToFrequencies.hpp"

namespace analyser {
	SamplesToFrequencies::SamplesToFrequencies() {}
	SamplesToFrequencies::SamplesToFrequencies(const SampleBuffer& buffer) : sample_source_(buffer) {}

	void SamplesToFrequencies::bind(const SampleBuffer& buffer)
	{
		sample_source_ = buffer;
	}

	void SamplesToFrequencies::clear() {
		// resets the sample_source to std::monostate
		sample_source_ = SampleSourceVariant();
	}
}
