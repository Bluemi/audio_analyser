#include "MathFunctions.hpp"

#include <cmath>

std::vector<float> group(std::vector<float> &vec, unsigned int num_of_subbands)
{
	const float subband_width = vec.size() / (float) num_of_subbands;
	std::vector<float> result(num_of_subbands, 0.f);
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

std::vector<float> discreteCosineTransformationIV(SampleIterator iterator, const Time &duration)
{
	const int N = duration.getFrameCount();
	std::vector<float> result(N);
	for (int k = 0; k < N; k++)
	{
		float sum = 0.f;
		for (int n = 0; n < N; n++, ++iterator)
		{
			sum += iterator.get() * cos(M_PI/N * (n + 0.5f) * (k + 0.5f));
		}
		result[k] = sum;
	}
	return result;
}

std::vector<float> inverseDiscreteCosineTransformationIV(const std::vector<float> &vec)
{
	std::vector<float> result(vec.size(), 0.f);
	const int N = vec.size();
	for (int k = 0; k < N; k++)
	{
		float sum = 0.f;
		for (int n = 0; n < N; n++)
		{
			sum += vec[n] * cos(M_PI/N * (n + 0.5f) * (k + 0.5f));
		}
		result[k] = (2.f/N) * sum;
	}
	return result;
}

std::vector<float> modifiedDiscreteCosineTransformation(SampleIterator iterator, const Time &duration, float percentage)
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
