#ifndef __MATHFUNCTIONS_CLASS__
#define __MATHFUNCTIONS_CLASS__

#include <vector>

template <typename SampleType>
class SampleIterator;
class Time;

template <typename T>
std::vector<T> group(std::vector<T> &vec, unsigned int subbands);

template <typename T>
std::vector<T> group(const std::vector<T> &input, const std::vector<float> &bounds, const int max);

template <typename T>
T getSubgroup(const std::vector<T> &input, unsigned int lower_bound, unsigned int upper_bound);

template <typename SampleType>
std::vector<float> modifiedDiscreteCosineTransformation(SampleIterator<SampleType> iterator, const Time &duration, float percentage);

#include <audio/SampleIterator.hpp>
#include <time/Time.hpp>

#endif
