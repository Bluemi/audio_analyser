#include "BoundsGrouper.hpp"

#include <math/MathFunctions.hpp>

BoundsGrouper::BoundsGrouper(const std::vector<float> bounds, unsigned int max)
	: bounds(bounds), max(max)
{}

BoundsGrouper::~BoundsGrouper() {}

std::vector<float> BoundsGrouper::group(const std::vector<float> &input) const
{
	return MathFunctions::group(input, bounds, max);
}
