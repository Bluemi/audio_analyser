#include "ScaledGrouper.hpp"

#include "MathFunctions.hpp"

ScaledGrouper::ScaledGrouper(const std::vector<float> bounds, const std::vector<float> scale, unsigned int max)
	: bounds(bounds), scale(scale), max(max)
{}

ScaledGrouper::~ScaledGrouper() {}

std::vector<float> ScaledGrouper::group(const std::vector<float>& input) const
{
	return MathFunctions::scale(scale, MathFunctions::group(input, bounds, max));
}
