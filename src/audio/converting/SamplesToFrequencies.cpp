#include "SamplesToFrequencies.hpp"

#include <audio/frequencies/FrequencyBlock.hpp>

namespace analyser {
	const unsigned int DEFAULT_BLOCK_SIZE = 2048;

	SamplesToFrequencies::SamplesToFrequencies() : block_size_(DEFAULT_BLOCK_SIZE) {}

	SamplesToFrequencies::SamplesToFrequencies(const SampleSource& source)
		: sample_source_(source), block_size_(DEFAULT_BLOCK_SIZE)
	{}

	SamplesToFrequencies::SamplesToFrequencies(unsigned int block_size)
		: block_size_(block_size)
	{}

	SamplesToFrequencies::SamplesToFrequencies(const SampleSource& source, unsigned int block_size)
		: sample_source_(source), block_size_(block_size)
	{}

	void SamplesToFrequencies::bind(const SampleSource& source)
	{
		sample_source_ = source;
	}

	void SamplesToFrequencies::set_block_size(size_t block_size)
	{
		block_size_ = block_size;
	}

	void SamplesToFrequencies::clear() {
		// resets the sample_source to std::monostate
		sample_source_ = SampleSource();
	}

	FrequencyBuffer SamplesToFrequencies::convert_impl(const SampleBuffer& sbuffer, const Time& begin_time, const Time& end_time) {
		size_t number_of_samples = end_time.get_number_of_samples() - begin_time.get_number_of_samples();
		size_t number_of_blocks = number_of_samples / block_size_ + (number_of_samples%block_size_?1:0);
		FrequencyBuffer fbuffer(sbuffer.get_number_of_channels(), number_of_blocks, block_size_);

		for (unsigned int channel_index = 0; channel_index < sbuffer.get_number_of_channels(); channel_index++) {
			// getting sample block
			Channel::Block sample_block;
			for (size_t block_index = 0; block_index < number_of_blocks; block_index++) {
				Time block_begin = begin_time + (block_index * block_size_);
				Time block_end = block_begin + block_size_;
				if (sbuffer.get_block(channel_index, block_begin, block_end, &sample_block)) {
					FrequencyBlock frequency_block;
					if (fbuffer.get_frequency_block_by_id(channel_index, block_index, &frequency_block)) {
						fftw_handler.load_input_buffer(sample_block.get_samples(), block_size_);
						fftw_handler.convert();
						fftw_handler.load_output_buffer(frequency_block.get_frequencies());
					}
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
