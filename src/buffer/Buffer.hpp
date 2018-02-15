#ifndef __BUFFER_CLASS__
#define __BUFFER_CLASS__

/*
 * Buffer can be in one of the following states:
 *  - empty:
 *    buffer.data_ equals nullptr
 *
 *  - filled:
 *    buffer.data_ is unequal nullptr
 *    buffer.number_of_references_ is unequal nullptr and *(buffer.number_of_references_) is greater than 0
 *    buffer.size_ is unequal 0
 */

#include <cstddef>

namespace analyser {
	class Buffer
	{
		public:
			/**
			 * \brief Creates an empty Buffer
			 *
			 * The created buffer doesn't hold any data.
			 * get_data() returns a nullptr.
			 * get_size() returns 0.
			 */
			Buffer();

			/**
			 * \brief Creates an buffer with space for size elements
			 *
			 * Creates a buffer holding size elements.
			 * @param size The number of elements to hold with this buffer.
			 */
			Buffer(size_t size_);

			/**
			 * \brief Makes a shallow copy of `buffer`
			 *
			 * @param buffer The buffer to copy from.
			 */
			Buffer(const Buffer& buffer);

			/**
			 * \brief Swaps the content of `buffer1` and `buffer2`
			 *
			 * @param buffer1 The buffer which swaps the content with `buffer2`.
			 * @param buffer2 The buffer which swaps the content with `buffer1`.
			 */
			static void swap(Buffer& buffer1, Buffer& buffer2);

			/**
			 * \brief Assigns the left-hand buffer to the right-hand buffer
			 *
			 * The left-hand buffer becomes a shallow copy of the right-hand buffer.
			 * @param buffer1 The buffer which swaps the content with `buffer2`.
			 * @param buffer2 The buffer which swaps the content with `buffer1`.
			 * @return The left-hand buffer
			 */
			Buffer& operator=(Buffer buffer);

			/**
			 * \brief Destroys the buffer
			 *
			 * Destroys the buffer and releases the data, if no other buffer holds them.
			 */
			~Buffer();

			/**
			 * \brief Allocates `size` elements
			 *
			 * Releases the data hold before, if no other buffer holds them.
			 * @param size The number of elements to allocate.
			 */
			void allocate(size_t size);

			/**
			 * \brief Clones the buffer
			 *
			 * The new created buffer has its own independent memory.
			 * @return The new Buffer
			 */
			Buffer clone() const;

			/**
			 * \brief Clones the part of the buffer from start to end (end excluded)
			 *
			 * The new created buffer has its own independent memory.
			 * @param start The index of the sample to start from
			 * @param start The index of the sample to end with (excluded)
			 * @return The new Buffer
			 */
			Buffer clone_from_to(size_t start, size_t end) const;

			/**
			 * \brief Gets the data
			 *
			 * @return Gets the pointer to the array of data
			 */
			float* get_data() const;

			/**
			 * \brief Checks whether the buffer is empty of not
			 *
			 * @return True if the buffer is empty, false if not.
			 */
			bool is_empty() const;

			/**
			 * \brief Gets the size of this buffer
			 *
			 * @return Size of this buffer.
			 */
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
