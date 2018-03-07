#include "FFTWHandler.hpp"

#include <cstring>
#include <type_traits>
#include <cstdlib>

namespace analyser {
	FFTWHandler::FFTWHandler(size_t buffer_size, WindowFunction window_function)
		: buffer_size_(0), capacity_(0), initialized_transform_plan(false), window_function_(window_function)
	{
		allocate(buffer_size);
		update_transform_plan();
		update_window_buffer();
	}

	FFTWHandler::~FFTWHandler() {
		if (initialized_transform_plan) {
			fftwf_destroy_plan(fftw_transform_plan);
		}
		if (capacity_ != 0) {
			fftwf_free(internal_input_buffer_);
			fftwf_free(internal_output_buffer_);
			free(internal_window_buffer_);
		}
	}

	void FFTWHandler::write_input_buffer(const float* in_buffer, size_t input_size)
	{
		if (buffer_size_ != input_size) {
			allocate(input_size);
			// has to update transform_plan
			update_transform_plan();
			update_window_buffer();
		}

		// copy data to internal_input_buffer_
		if constexpr (std::is_same<float, SampleType>()) {
			// copy everything directly
			memcpy(internal_input_buffer_, in_buffer, sizeof(SampleType) * input_size);
		} else {
			// elementwise copy
			for (size_t i = 0; i < input_size; i++) {
				internal_input_buffer_[i] = in_buffer[i];
			}
		}

		// fill last elements with 0
		if (buffer_size_ > input_size) {
			for (size_t i = input_size; i < buffer_size_; i++) {
				internal_input_buffer_[i] = 0.f;
			}
		}
	}

	void FFTWHandler::read_output_buffer(float* out_buffer)
	{
		// copy data to internal_input_buffer_
		if constexpr (std::is_same<float, SampleType>()) {
			// copy everything directly
			memcpy(out_buffer, internal_output_buffer_, sizeof(SampleType) * buffer_size_);
		} else {
			// memberwise copy
			for (size_t i = 0; i < buffer_size_; i++) {
				out_buffer[i] = internal_output_buffer_[i];
			}
		}
	}

	void FFTWHandler::apply_window_function()
	{
		for (size_t i = 0; i < buffer_size_; i++) {
			internal_input_buffer_[i] *= internal_window_buffer_[i];
		}
	}

	void FFTWHandler::convert() const
	{
		fftwf_execute(fftw_transform_plan);
	}

	bool FFTWHandler::is_empty() const {
		return buffer_size_ == 0;
	}

	size_t FFTWHandler::get_buffer_size() const
	{
		return buffer_size_;
	}

	void FFTWHandler::set_buffer_size(size_t buffer_size)
	{
		if (buffer_size_ != buffer_size) {
			allocate(buffer_size);
			buffer_size_ = buffer_size;
		}
	}

	void FFTWHandler::set_window_function(WindowFunction window_function)
	{
		window_function_ = window_function;
		update_window_buffer();
	}

	void FFTWHandler::allocate(size_t buffer_size) {
		const bool has_to_allocate = buffer_size > capacity_;

		if (has_to_allocate) {
			// free if memory was allocated
			if (capacity_ != 0) {
				fftwf_free(internal_input_buffer_);
				fftwf_free(internal_output_buffer_);
				free(internal_window_buffer_);
			}
			internal_input_buffer_ = (SampleType*) fftwf_malloc(buffer_size * sizeof(SampleType));
			internal_output_buffer_ = (SampleType*) fftwf_malloc(buffer_size * sizeof(SampleType));
			internal_window_buffer_ = (SampleType*) malloc(buffer_size * sizeof(SampleType));

			capacity_ = buffer_size;
		}

		buffer_size_ = buffer_size;
	}

	void FFTWHandler::update_transform_plan() {
		if (initialized_transform_plan) {
			fftwf_destroy_plan(fftw_transform_plan);
		}
		fftw_transform_plan = fftwf_plan_r2r_1d(buffer_size_, internal_input_buffer_, internal_output_buffer_, FFTW_REDFT11, FFTW_ESTIMATE);
		initialized_transform_plan = true;
	}

	void FFTWHandler::update_window_buffer() {
		window_function_(internal_window_buffer_, buffer_size_);
	}
}
