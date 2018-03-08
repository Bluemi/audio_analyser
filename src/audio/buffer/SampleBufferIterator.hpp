#ifndef __SAMPLEBUFFERITERATOR_CLASS__
#define __SAMPLEBUFFERITERATOR_CLASS__

#include <vector>

namespace analyser {
	class Sample;

	class SampleBufferIterator
	{
		public:
			SampleBufferIterator();
			SampleBufferIterator(const SampleBufferIterator& original) = default;
			SampleBufferIterator(std::vector<float*> channels, size_t initial_offset);
			SampleBufferIterator& operator=(const SampleBufferIterator& original) = default;

			float get_subsample(const unsigned int channel_index) const;
			bool operator==(const SampleBufferIterator& iterator) const;
			bool operator!=(const SampleBufferIterator& iterator) const;
			bool operator<(const SampleBufferIterator& iterator) const;
			bool operator>(const SampleBufferIterator& iterator) const;
			bool operator<=(const SampleBufferIterator& iterator) const;
			bool operator>=(const SampleBufferIterator& iterator) const;

			const Sample operator*() const;
			const Sample operator->() const;
			void operator++(int);
			void operator++();
			void operator--(int);
			void operator--();
			void operator+=(int step);
			void operator-=(int step);
			Sample operator[](int index) const;
		private:
			std::vector<float*> channels_;
			size_t offset_;
	};
}

#endif
