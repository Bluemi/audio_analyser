#include "SamplesToFrequencies.hpp"

namespace analyser {
	SamplesToFrequencies::SamplesToFrequencies() {}

	void SamplesToFrequencies::clear() {
		// resets the sample_source to std::monostate
		sample_source_ = SampleSourceVariant();
	}

	template<typename SampleSource>
	FrequencyBuffer convert_impl(const SampleSource& /*sample_source*/, const Time& /*begin_time*/, const Time& /*end_time*/) {
		return FrequencyBuffer();
	}

	// Dispatcher for different SampleSource Types
	class Overloader {
		public:
			Overloader(const SamplesToFrequencies* stf, const Time& begin_time, const Time& end_time) : stf_(stf), begin_time_(begin_time), end_time_(end_time) {}

			FrequencyBuffer operator()(std::monostate) {
				return FrequencyBuffer();
			}

			template<typename SampleSource>
			FrequencyBuffer operator()(const SampleSource& source) {
				// defined in header
				return convert_impl(source, begin_time_, end_time_);
			}


		private:
			const SamplesToFrequencies* stf_;
			Time begin_time_;
			Time end_time_;
	};

	FrequencyBuffer SamplesToFrequencies::convert(const Time& begin_time, const Time& end_time) const
	{
		FrequencyBuffer fbuffer = std::visit(Overloader(this, begin_time, end_time), sample_source_);
		return fbuffer;
	}
}
