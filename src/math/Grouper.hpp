#ifndef __GROUPER_CLASS__
#define __GROUPER_CLASS__

#include <vector>

class Grouper
{
	public:
		virtual ~Grouper();
		virtual std::vector<float> group(const std::vector<float> &input) const = 0;
	protected:
		Grouper();
};

#endif
