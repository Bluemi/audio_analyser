#ifndef __MATHFUNCTIONS_CLASS__
#define __MATHFUNCTIONS_CLASS__

#include <vector>

class SampleIterator;
class Time;

std::vector<float> group(std::vector<float> &vec, unsigned int subbands);

// Transformations
std::vector<float> discreteCosineTransformationIV(SampleIterator iterator, const Time &duration);
std::vector<float> inverseDiscreteCosineTransformationIV(const std::vector<float> &vec);

std::vector<float> modifiedDiscreteCosineTransformation(SampleIterator iterator, const Time &duration, float percentage);
//std::vector<float> modifiedDinverseDiscreteCosineTransformation(const std::vector<float> &vec);

#include <SampleIterator.hpp>
#include <time/Time.hpp>

#endif
