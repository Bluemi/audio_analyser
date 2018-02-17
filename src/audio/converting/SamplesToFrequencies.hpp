#ifndef __SAMPLESTOFREQUENCIES_CLASS__
#define __SAMPLESTOFREQUENCIES_CLASS__

#include <variant>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/frequencies/FrequencyBuffer.hpp>
#include <audio/converting/FFTWHandler.hpp>

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

			template<typename SampleSource>
			SamplesToFrequencies(const SampleSource& source) : sample_source_(source) {}

			// binds a source to this converter
			template<typename SampleSource>
			void bind(const SampleSource& source) { sample_source_ = source; }

			// unbinds all sources
			void clear();

			FrequencyBuffer convert(const Time& time_begin, const Time& time_end);
		private:
			FrequencyBuffer convert_impl(const SampleBuffer& sbuffer, const Time& begin_time, const Time& end_time);
			void load_internal_double_buffer(float* input, size_t size);

			using SampleSourceVariant = std::variant<std::monostate, SampleBuffer>;

			SampleSourceVariant sample_source_;

			// handling fftw
			__analyser_internal__::FFTWHandler fftw_handler;

		friend class Overloader;
	};
}

#endif
