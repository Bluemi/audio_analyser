#ifndef __FFTWHANDLER_CLASS__
#define __FFTWHANDLER_CLASS__

#include <fftw3.h>

#include <audio/converting/WindowFunction.hpp>

namespace analyser {
	class FFTWHandler
	{
		public:
			FFTWHandler(size_t buffer_size, WindowFunction window_function);
			~FFTWHandler();

			// reads the samples from in_buffer into internal_input_buffer
			void write_input_buffer(const float* in_buffer, size_t input_size);

			// writes the samples from internal_output_buffer into out_buffer
			void read_output_buffer(float* out_buffer);

			void apply_window_function();
			void convert() const;

			bool is_empty() const;
			size_t get_buffer_size() const;
			void set_buffer_size(size_t buffer_size);
			void set_window_function(WindowFunction window_function);

		private:
			using SampleType = float;
			// after this function, buffer_size_ will be buffer_size and capacity_ will be at least buffer_size
			void allocate(size_t buffer_size);
			void update_transform_plan();
			void update_window_buffer();

			SampleType* internal_input_buffer_;
			SampleType* internal_output_buffer_;
			SampleType* internal_window_buffer_;
			size_t buffer_size_;
			size_t capacity_;

			bool initialized_transform_plan;

			fftwf_plan fftw_transform_plan;
			WindowFunction window_function_;
	};
}

#endif
