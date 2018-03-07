#include "WindowFunction.hpp"

#include <math.h>

namespace analyser {
	void no_window(float* samples, size_t size)
	{
		for (size_t i = 0; i < size; i++) {
			samples[i] = 1.f;
		}
	}

	void von_hann_window(float* samples, size_t size)
	{
		for (size_t i = 0; i < size; i++) {
			samples[i] = 0.5f * (1 - cos((2*M_PI*i) / (size - 1)));
		}
	}
}
