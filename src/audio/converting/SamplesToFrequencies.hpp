#ifndef __SAMPLESTOFREQUENCIES_CLASS__
#define __SAMPLESTOFREQUENCIES_CLASS__

#include <audio/converting/FFTWHandler.hpp>
#include <audio/buffer/SampleSource.hpp>

/*
 * Handles a SampleSource and converts its samples into frequencies.
 */

class Overloader;

namespace analyser {
	class FrequencyBuffer;

	class SamplesToFrequencies
	{
		public:
			SamplesToFrequencies();
			SamplesToFrequencies(const SampleSource& source);
			SamplesToFrequencies(unsigned int block_size);
			SamplesToFrequencies(const SampleSource& source, unsigned int block_size);
			SamplesToFrequencies(const SampleSource& source, unsigned int block_size, WindowFunction window_function);

			// binds a source to this converter
			void bind(const SampleSource& source);
			void set_block_size(size_t block_size);
			void set_window_function(WindowFunction window_function);

			// unbinds all sources
			void clear();

			FrequencyBuffer convert(const PartialTime& begin_time, const PartialTime& end_time);
		private:
			FrequencyBuffer convert_impl(const SampleBuffer& sbuffer, const PartialTime& begin_time, const PartialTime& end_time);
			void load_internal_double_buffer(float* input, size_t size);

			SampleSource sample_source_;
			FFTWHandler fftw_handler; // handling fftw
			size_t block_size_;

		friend class Overloader;
	};
}

#endif
