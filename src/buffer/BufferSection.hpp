#ifndef __BUFFERSECTION_CLASS__
#define __BUFFERSECTION_CLASS__

#include <cstddef>

namespace analyser {
	class Buffer;

	class BufferSection
	{
		public:
			BufferSection();
			BufferSection(float* data, size_t size, float* origin, unsigned int* number_of_references);
			BufferSection(const BufferSection& buffer_section);

			BufferSection& operator=(BufferSection buffer_section);
			static void swap(BufferSection& buffer_section1, BufferSection& buffer_section2);

			~BufferSection();

			Buffer clone() const;

			float operator[](size_t index) const;

			float* get_data() const;
			size_t get_size() const;
			bool is_empty() const;
		private:
			void plus_reference();
			void minus_reference();

			float* data_;
			size_t size_;
			float* origin_;
			unsigned int* number_of_references_;
	};
}

#endif
