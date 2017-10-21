#ifndef __MATHFUNCTIONS_CLASS__
#define __MATHFUNCTIONS_CLASS__

#include <vector>

template <typename SampleType>
class SampleIterator;
class Time;

template <typename T>
std::vector<T> group(std::vector<T> &vec, unsigned int subbands);

template <typename SampleType>
std::vector<float> modifiedDiscreteCosineTransformation(SampleIterator<SampleType> iterator, const Time &duration, float percentage);

#include <SampleIterator.hpp>
#include <time/Time.hpp>

#endif
