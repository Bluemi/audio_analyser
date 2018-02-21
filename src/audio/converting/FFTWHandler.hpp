#ifndef __FFTWHANDLER_CLASS__
#define __FFTWHANDLER_CLASS__

#include <fftw3.h>

/*
 * TODO:
 * - fftwf_destroy_plan in destructor
 * - fftwf_free arrays
 */

namespace analyser {
	class FFTWHandler
	{
		public:
			FFTWHandler(size_t size = 256);
			~FFTWHandler();

			// reads the samples from in_buffer into internal_input_buffer
			void load_input_buffer(const float* in_buffer, size_t size);

			// writes the samples from internal_output_buffer into out_buffer
			void load_output_buffer(float* out_buffer);

			void convert() const;

			bool is_empty() const;
			size_t get_size() const;
		private:
			using SampleType = float;
			// after this function, size_ will be size and capacity_ will be at least size
			void allocate(size_t size);
			void update_transform_plan();

			SampleType* internal_input_buffer_;
			SampleType* internal_output_buffer_;
			size_t size_;
			size_t capacity_;

			bool initialized_transform_plan;

			fftwf_plan fftw_transform_plan;
	};
}

#endif
