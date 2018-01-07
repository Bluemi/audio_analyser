#ifndef __BUFFER_CLASS__
#define __BUFFER_CLASS__

#include <cstddef>

namespace analyser {
	class Buffer
	{
		public:
			Buffer();
			Buffer(size_t number_of_samples);
			Buffer(const Buffer& buffer);
			void operator=(const Buffer& buffer);
			~Buffer();
			void plus_reference();
			void minus_reference();

			void allocate(size_t number_of_samples);
			Buffer clone() const;

			float* get_samples() const;
			bool is_empty() const;
			size_t get_number_of_samples() const;

		private:
			float* samples_;
			unsigned int* number_of_references_;
			size_t number_of_samples_;
	};
}

#endif
