#ifndef __BOUNDSGROUPER_CLASS__
#define __BOUNDSGROUPER_CLASS__

#include "Grouper.hpp"

class BoundsGrouper : public Grouper
{
	public:
		BoundsGrouper(const std::vector<float> bounds, unsigned int max = 22050);
		~BoundsGrouper();
		virtual std::vector<float> group(const std::vector<float> &input) const override;
	private:
		const std::vector<float> bounds;
		unsigned int max;
};

#endif
