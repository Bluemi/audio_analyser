#ifndef __BUFFER_CLASS__
#define __BUFFER_CLASS__

/*
 * Buffer can be in one of the following states:
 *  - empty:
 *    buffer.samples_ equals nullptr
 *
 *  - filled:
 *    buffer.samples_ is unequal nullptr
 *    buffer.number_of_references_ is unequal nullptr and *(buffer.number_of_references_) is greater than 0
 *    buffer.number_of_samples_ is unequal 0
 */

#include <cstddef>

namespace analyser {
	class Buffer
	{
		public:
			/**
			 * \brief Creates an empty Buffer
			 *
			 * The created buffer doesn't hold any samples.
			 * get_samples() returns a nullptr.
			 * get_number_of_samples() returns 0.
			 */
			Buffer();

			/**
			 * \brief Creates an buffer with space for number_of_samples samples
			 *
			 * Creates a buffer holding number_of_samples samples.
			 * @param number_of_samples The number of samples to hold with this buffer.
			 */
			Buffer(size_t number_of_samples);

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
			 * Destroys the buffer and releases the samples, if no other buffer holds them.
			 */
			~Buffer();

			/**
			 * \brief Allocates `number_of_samples` samples
			 *
			 * Releases the samples hold before, if no other buffer holds them.
			 * @param number_of_samples The number of samples to allocate.
			 */
			void allocate(size_t number_of_samples);

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
			 * \brief Gets the samples
			 *
			 * @return Gets the pointer to the array of samples
			 */
			float* get_samples() const;

			/**
			 * \brief Checks whether the buffer is empty of not
			 *
			 * @return True if the buffer is empty, false if not.
			 */
			bool is_empty() const;

			/**
			 * \brief Gets the number of samples in this buffer
			 *
			 * @return Number of samples in this buffer.
			 */
			size_t get_number_of_samples() const;

		private:
			void plus_reference();
			void minus_reference();

			float* samples_;
			unsigned int* number_of_references_;
			size_t number_of_samples_;
	};
}

#endif
