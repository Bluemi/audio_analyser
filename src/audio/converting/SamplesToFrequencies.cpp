#include "SamplesToFrequencies.hpp"

namespace analyser {
	SamplesToFrequencies::SamplesToFrequencies() {}

	void SamplesToFrequencies::clear() {
		// resets the sample_source to std::monostate
		sample_source_ = SampleSource();
	}

	FrequencyBuffer SamplesToFrequencies::convert_impl(const SampleBuffer& sbuffer, const Time& begin_time, const Time& end_time) {
		size_t size = end_time.get_number_of_samples() - begin_time.get_number_of_samples();
		FrequencyBuffer fbuffer(sbuffer.get_number_of_channels(), size);

		for (unsigned int channel_index = 0; channel_index < sbuffer.get_number_of_channels(); channel_index++) {

			// getting sample block
			Channel::Block sample_block;
			if (sbuffer.get_block(channel_index, begin_time, end_time, &sample_block)) {

				// getting frequency block
				Buffer fb;
				if (fbuffer.get_frequencies(channel_index, &fb)) {
					fftw_handler.load_input_buffer(sample_block.get_samples(), size);
					fftw_handler.convert();
					fftw_handler.load_output_buffer(fb.get_data());
				}
			}
		}

		return fbuffer;
	}

	// Dispatcher for different SampleSource Types
	class Overloader {
		public:
			Overloader(SamplesToFrequencies* stf, const Time& begin_time, const Time& end_time) : stf_(stf), begin_time_(begin_time), end_time_(end_time) {}

			FrequencyBuffer operator()(std::monostate) {
				return FrequencyBuffer();
			}

			template<typename TSampleSource>
			FrequencyBuffer operator()(const TSampleSource& source) {
				return stf_->convert_impl(source, begin_time_, end_time_);
			}

		private:
			SamplesToFrequencies* stf_;
			const Time begin_time_;
			const Time end_time_;
	};

	FrequencyBuffer SamplesToFrequencies::convert(const Time& begin_time, const Time& end_time)
	{
		return std::visit(Overloader(this, begin_time, end_time), sample_source_);
	}
}
