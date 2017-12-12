#include "MathFunctions.hpp"

#include <cmath>

std::vector<float> MathFunctions::group(std::vector<float> &vec, unsigned int num_of_subbands)
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

std::vector<float> MathFunctions::group(const std::vector<float> &input, const std::vector<float> &bounds, const int max)
{
	unsigned int n = bounds.size()-1;
	if (n < 1)
	{
		return std::vector<float>();
	}
	float coefficient = input.size() / (float)max;
	std::vector<int> input_frequencies(bounds.size());
	for (unsigned int i = 0; i < bounds.size(); i++)
	{
		input_frequencies[i] = (int)(coefficient * bounds[i]);
	}

	std::vector<float> result(n);
	for (unsigned int i = 0; i < n; i++)
	{
		//std::cout << "getSubgroup(input, input_frequencies[" << i << "]=" << input_frequencies[i] << ", input_frequencies[i+i]);
		result[i] = MathFunctions::getSubgroup(input, input_frequencies[i], input_frequencies[i+1]);
	}
	return result;

}

float MathFunctions::getSubgroup(const std::vector<float> &input, unsigned int lower_bound, unsigned int upper_bound)
{
	float sum = 0;
	for (unsigned int i = lower_bound; i < upper_bound; i++)
	{
		sum += input[i];
	}
	return sum / (upper_bound - lower_bound);
}

std::vector<float> MathFunctions::modifiedDiscreteCosineTransformation(SampleIterator iterator, const Time &duration, float percentage)
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

std::vector<float> MathFunctions::scale(const std::vector<float>& input, const std::vector<float>& factor)
{
	std::vector<float> result(input.size());
	for (unsigned int i = 0; i < input.size(); i++)
	{
		result[i] = input[i] * factor[i];
	}
	return result;
}

std::vector<float> MathFunctions::scale(const std::vector<float>& input, float factor)
{
	std::vector<float> result;
	for (unsigned int i = 0; i < input.size(); i++)
	{
		result[i] = input[i] * factor;
	}
	return result;
}
