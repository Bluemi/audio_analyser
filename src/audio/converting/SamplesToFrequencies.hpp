#ifndef __SAMPLESTOFREQUENCIES_CLASS__
#define __SAMPLESTOFREQUENCIES_CLASS__

#include <variant>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/frequencies/FrequencyBuffer.hpp>
#include <audio/converting/FFTWHandler.hpp>

#include <audio/converting/SampleSource.hpp>

/*
 * Handles a SampleSource and converts its samples into frequencies.
 * A SampleSource has to implement the following methods:
 *  - SampleSource::Iterator begin()
 *  - SampleSource::Iterator end()
 *  - SampleSource::Iterator get_iterator_at(const Time& time)
 */

class Overloader;

namespace analyser {
	class SamplesToFrequencies
	{
		public:
			SamplesToFrequencies();

			SamplesToFrequencies(const SampleSource& source) : sample_source_(source) {}

			// binds a source to this converter
			void bind(const SampleSource& source) { sample_source_ = source; }

			// unbinds all sources
			void clear();

			FrequencyBuffer convert(const Time& begin_time, const Time& end_time);
		private:
			FrequencyBuffer convert_impl(const SampleBuffer& sbuffer, const Time& begin_time, const Time& end_time);
			void load_internal_double_buffer(float* input, size_t size);

			SampleSource sample_source_;

			// handling fftw
			FFTWHandler fftw_handler;

		friend class Overloader;
	};
}

#endif
