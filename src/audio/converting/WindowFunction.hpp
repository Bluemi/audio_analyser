#ifndef __WINDOWFUNCTION_CLASS__
#define __WINDOWFUNCTION_CLASS__

#include <functional>

namespace analyser {
	using WindowFunction = std::function<void(float*, size_t)>;

	void no_window(float* samples, size_t size);
	void von_hann_window(float* samples, size_t size);
}

#endif
