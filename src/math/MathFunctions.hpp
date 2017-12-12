#ifndef __MATHFUNCTIONS_CLASS__
#define __MATHFUNCTIONS_CLASS__

#include <vector>

class SampleIterator;
class Time;

namespace MathFunctions
{
	std::vector<float> group(std::vector<float> &vec, unsigned int subbands);
	std::vector<float> group(const std::vector<float> &input, const std::vector<float> &bounds, const int max);
	float getSubgroup(const std::vector<float> &input, unsigned int lower_bound, unsigned int upper_bound);
	std::vector<float> modifiedDiscreteCosineTransformation(SampleIterator iterator, const Time &duration, float percentage);
	std::vector<float> scale(const std::vector<float>& input, const std::vector<float>& factor);
	std::vector<float> scale(const std::vector<float>& input, float factor);
}

#include <time/Time.hpp>
#include <audio/SampleIterator.hpp>

#endif
