#ifndef __SAMPLESOURCEVARIANT_CLASS__
#define __SAMPLESOURCEVARIANT_CLASS__

#include <variant>
#include <audio/buffer/SampleBuffer.hpp>

namespace analyser {
	using SampleSource = std::variant<std::monostate, SampleBuffer>;
}

#endif
