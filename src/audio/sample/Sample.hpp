#ifndef __SAMPLE_CLASS__
#define __SAMPLE_CLASS__

#include <vector>

namespace analyser {
	class Sample
	{
		public:
			Sample(std::vector<float> samples);
			Sample();
			void invalidate();

			bool is_empty() const;
			bool get_subsample(unsigned int channel_number, float* subsample) const;

			unsigned int get_number_of_channels() const;

			Sample* operator->();
			const Sample* operator->() const;
		private:
			std::vector<float> samples_;
	};
}

#endif
