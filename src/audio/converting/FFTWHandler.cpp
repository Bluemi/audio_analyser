#include "FFTWHandler.hpp"

#include <cstring>
#include <type_traits>

namespace __analyser_internal__ {
	FFTWHandler::FFTWHandler(size_t size)
		: size_(0), capacity_(0), initialized_transform_plan(false)
	{
		allocate(size);
		update_transform_plan();
	}

	FFTWHandler::~FFTWHandler() {
		if (initialized_transform_plan) {
			fftwf_destroy_plan(fftw_transform_plan);
		}
		if (capacity_ != 0) {
			fftwf_free(internal_input_buffer_);
			fftwf_free(internal_output_buffer_);
		}
	}

	void FFTWHandler::load_input_buffer(const float* in_buffer, size_t size)
	{
		if (size != size_) {
			allocate(size);
			// has to update transform_plan
			update_transform_plan();
		}

		// copy data to internal_input_buffer_
		if constexpr (std::is_same<float, SampleType>()) {
			// copy everything directly
			memcpy(internal_input_buffer_, in_buffer, sizeof(SampleType) * size);
		} else {
			// memberwise copy
			for (size_t i = 0; i < size; i++) {
				internal_input_buffer_[i] = in_buffer[i];
			}
		}
	}

	void FFTWHandler::load_output_buffer(float* out_buffer)
	{
		// copy data to internal_input_buffer_
		if constexpr (std::is_same<float, SampleType>()) {
			// copy everything directly
			memcpy(out_buffer, internal_output_buffer_, sizeof(SampleType) * size_);
		} else {
			// memberwise copy
			for (size_t i = 0; i < size_; i++) {
				out_buffer[i] = internal_output_buffer_[i];
			}
		}
	}

	void FFTWHandler::convert() const
	{
		fftwf_execute(fftw_transform_plan);
	}

	bool FFTWHandler::is_empty() const {
		return size_ == 0;
	}

	size_t FFTWHandler::get_size() const
	{
		return size_;
	}

	void FFTWHandler::allocate(size_t size) {
		bool has_to_allocate = size > capacity_;

		if (has_to_allocate) {
			// free if memory was allocated
			if (capacity_ != 0) {
				fftwf_free(internal_input_buffer_);
				fftwf_free(internal_output_buffer_);
			}
			internal_input_buffer_ = (SampleType*) fftwf_malloc(size * sizeof(SampleType));
			internal_output_buffer_ = (SampleType*) fftwf_malloc(size * sizeof(SampleType));

			capacity_ = size;
		}

		size_ = size;
	}

	void FFTWHandler::update_transform_plan() {
		if (initialized_transform_plan) {
			fftwf_destroy_plan(fftw_transform_plan);
		}
		fftw_transform_plan = fftwf_plan_r2r_1d(size_, internal_input_buffer_, internal_output_buffer_, FFTW_REDFT11, FFTW_ESTIMATE);
		initialized_transform_plan = true;
	}
}
