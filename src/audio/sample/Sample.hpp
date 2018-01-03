#ifndef __SAMPLE_CLASS__
#define __SAMPLE_CLASS__

namespace analyser {
	class Sample
	{
		public:
			Sample(float* samples, unsigned int number_of_channels);
			Sample();
			void set(float* samples, unsigned int number_of_channels);
			void invalidate();

			bool is_empty() const;
			bool get_subsample(unsigned int channel_number, float* subsample) const;

			Sample* operator->();
			const Sample* operator->() const;
		private:
			bool is_empty_;
			float* samples_;
			unsigned int number_of_channels_;
	};
}

#endif
