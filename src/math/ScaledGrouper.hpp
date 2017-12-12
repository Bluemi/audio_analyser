#ifndef __SCALEDGROUPER_CLASS__
#define __SCALEDGROUPER_CLASS__

#include <vector>

#include "Grouper.hpp"

class ScaledGrouper : public Grouper
{
	public:
		ScaledGrouper(const std::vector<float> bounds, const std::vector<float> scale, unsigned int max = 22050);
		virtual ~ScaledGrouper();
		virtual std::vector<float> group(const std::vector<float>& input) const override;
	private:
		const std::vector<float> bounds;
		const std::vector<float> scale;
		unsigned int max;
};

#endif
