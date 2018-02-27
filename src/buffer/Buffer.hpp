#ifndef __BUFFER_CLASS__
#define __BUFFER_CLASS__

#include <cstddef>

namespace analyser {
	class BufferSection;

	class Buffer
	{
		public:
			// memory stuff
			Buffer();
			Buffer(size_t size_);
			template<typename IteratorType>
			Buffer(size_t size, const IteratorType& begin_iterator, const IteratorType& last_iterator);
			Buffer(const Buffer& buffer);
			static void swap(Buffer& buffer1, Buffer& buffer2);
			Buffer& operator=(Buffer buffer);
			~Buffer();

			void allocate(size_t size);
			Buffer clone() const;
			Buffer clone_from_to(size_t start, size_t end) const;
			void clear();

			// getters
			float* get_data() const;
			float operator[](size_t index) const;
			bool is_empty() const;
			size_t get_size() const;
			BufferSection get_section(size_t begin, size_t end) const;
		private:
			void plus_reference();
			void minus_reference();

			float* data_;
			unsigned int* number_of_references_;
			size_t size_;
	};

	template<typename IteratorType>
	Buffer::Buffer(size_t size, const IteratorType& begin_iterator, const IteratorType& last_iterator)
		: size_(size)
	{
		// allocate memory
		data_ = (float*)::operator new(sizeof(float) * size);
		// initiate number_of_references
		number_of_references_ = (unsigned int*)::operator new(sizeof(unsigned int));
		*number_of_references_ = 1;

		float* d = data_;
		for (IteratorType iter = begin_iterator; iter != last_iterator; ++iter) {
			*d = *iter;
			d++;
		}
	}
}

#endif
