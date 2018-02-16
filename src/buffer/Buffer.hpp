#ifndef __BUFFER_CLASS__
#define __BUFFER_CLASS__

#include <cstddef>

namespace analyser {
	class Buffer
	{
		public:
			Buffer();
			Buffer(size_t size_);
			Buffer(const Buffer& buffer);
			static void swap(Buffer& buffer1, Buffer& buffer2);
			Buffer& operator=(Buffer buffer);
			~Buffer();

			void allocate(size_t size);
			Buffer clone() const;
			Buffer clone_from_to(size_t start, size_t end) const;
			void clear();

			float* get_data() const;
			bool is_empty() const;
			size_t get_size() const;
		private:
			void plus_reference();
			void minus_reference();

			float* data_;
			unsigned int* number_of_references_;
			size_t size_;
	};
}

#endif
