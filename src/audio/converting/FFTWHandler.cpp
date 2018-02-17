#include "FFTWHandler.hpp"

#include <cstdlib>

namespace __analyser_internal__ {
	FFTWHandler::FFTWHandler(size_t size)
		: size_(size), capacity_(size), initialized_transform_plan(false)
	{
		allocate(size);
		update_transform_plan();
	}

	FFTWHandler::~FFTWHandler() {
		if (initialized_transform_plan) {
			fftw_destroy_plan(fftw_transform_plan);
		}
	}

	void FFTWHandler::load_input_buffer(const float* in_buffer, size_t size)
	{
		if (size != size_) {
			allocate(size);
			// has to update transform_plan
			update_transform_plan();
		}

		for (size_t i = 0; i < size; i++) {
			internal_input_buffer_[i] = in_buffer[i];
		}
	}

	void FFTWHandler::load_output_buffer(float* out_buffer)
	{
		for (size_t i = 0; i < size_; i++) {
			out_buffer[i] = internal_output_buffer_[i];
		}
	}

	void FFTWHandler::convert() const
	{
		fftw_execute(fftw_transform_plan);
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
			if (capacity_ == 0) {
				internal_input_buffer_ = (double*) malloc(size * sizeof(double));
				internal_output_buffer_ = (double*) malloc(size * sizeof(double));
				capacity_ = size;
			} else {
				internal_input_buffer_ = (double*) realloc(internal_input_buffer_, size * sizeof(double));
				internal_output_buffer_ = (double*) realloc(internal_output_buffer_, size * sizeof(double));
				capacity_ = size;
			}
		}

		size_ = size;
	}

	void FFTWHandler::update_transform_plan() {
		if (initialized_transform_plan) {
			fftw_destroy_plan(fftw_transform_plan);
		}
		fftw_transform_plan = fftw_plan_r2r_1d(size_, internal_input_buffer_, internal_output_buffer_, FFTW_REDFT11, FFTW_ESTIMATE);
		initialized_transform_plan = true;
	}
}
