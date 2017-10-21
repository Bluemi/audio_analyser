#include "MathFunctions.hpp"

#include <cmath>

template <typename T>
std::vector<T> group(std::vector<T> &vec, unsigned int num_of_subbands)
{
	const float subband_width = vec.size() / (float) num_of_subbands;
	std::vector<T> result(num_of_subbands, 0.f);
	unsigned int last_subband_index = 0;
	unsigned int value_counter = 0;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		const unsigned int subband_index = (int)(i / subband_width);
		value_counter++;
		result[subband_index] += std::abs(vec[i]);
		if (subband_index != last_subband_index)
		{
			result[last_subband_index] /= value_counter;
			value_counter = 0;
			last_subband_index = subband_index;
		}
	}
	if (value_counter != 0)
	{
		result[result.size()-1] /= value_counter;
	}
	return result;
}

template std::vector<float> group(std::vector<float> &vec, unsigned int num_of_subbands);
template std::vector<short> group(std::vector<short> &vec, unsigned int num_of_subbands);

template <typename T>
std::vector<float> modifiedDiscreteCosineTransformation(SampleIterator<T> iterator, const Time &duration, float percentage)
{
	const int N = duration.getFrameCount();
	std::vector<float> result((int)(N*percentage));
	for (int k = 0; k < (int)(N*percentage); k++)
	{
		float sum = 0.f;
		for (int n = 0; n < 2*N; n++)
		{
			sum += (iterator+n).get() * cos(M_PI/N * (n + 1.f/2.f + N/2.f)*(k+1.f/2.f));
		}
		result[k] = sum;
	}
	return result;
}

template std::vector<float> modifiedDiscreteCosineTransformation<float>(SampleIterator<float> iterator, const Time &duration, float percentage);
template std::vector<float> modifiedDiscreteCosineTransformation<short>(SampleIterator<short> iterator, const Time &duration, float percentage);
