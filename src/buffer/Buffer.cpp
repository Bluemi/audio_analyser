#include "Buffer.hpp"

#include <cstring> // for memcpy
#include <algorithm> // for swap

namespace analyser {
	Buffer::Buffer()
		: samples_(nullptr), number_of_references_(nullptr), number_of_samples_(0)
	{}

	Buffer::Buffer(size_t number_of_samples)
		: number_of_samples_(number_of_samples)
	{
		samples_ = (float*)::operator new(sizeof(float) * number_of_samples);
		number_of_references_ = (unsigned int*)::operator new(sizeof(unsigned int));
		*number_of_references_ = 1;
	}

	Buffer::Buffer(const Buffer& buffer)
		: samples_(buffer.samples_), number_of_references_(buffer.number_of_references_), number_of_samples_(buffer.number_of_samples_)
	{
		plus_reference();
	}

	void Buffer::swap(Buffer& buffer1, Buffer& buffer2)
	{
		using std::swap;
		swap(buffer1.samples_, buffer2.samples_);
		swap(buffer1.number_of_references_, buffer2.number_of_references_);
		swap(buffer1.number_of_samples_, buffer2.number_of_samples_);
	}

	Buffer& Buffer::operator=(Buffer buffer)
	{
		swap(*this, buffer);
		return *this;
	}

	Buffer::~Buffer()
	{
		minus_reference();
	}

	void Buffer::allocate(size_t number_of_samples)
	{
		// this buffers samples are overwritten
		minus_reference();

		samples_ = (float*)::operator new(sizeof(float) * number_of_samples);
		number_of_references_ = (unsigned int*)::operator new(sizeof(unsigned int));
		*number_of_references_ = 1;
	}

	Buffer Buffer::clone() const
	{
		Buffer buffer(number_of_samples_);
		memcpy(buffer.get_samples(), get_samples(), number_of_samples_);
		return buffer;
	}

	Buffer Buffer::clone_from_to(size_t start, size_t end)  const
	{
		size_t number_of_samples = end-start;
		Buffer buffer(end-start);
		memcpy(buffer.get_samples(), get_samples()+start, number_of_samples);
		return buffer;
	}

	void Buffer::plus_reference()
	{
		if (number_of_references_ != nullptr)
			(*number_of_references_)++;
	}

	void Buffer::minus_reference()
	{
		if (number_of_references_ != nullptr) {
			(*number_of_references_)--;
			if (*number_of_references_ == 0) {
				delete samples_;
				delete number_of_references_;
			}
		}
	}

	float* Buffer::get_samples() const
	{
		return samples_;
	}

	bool Buffer::is_empty() const
	{
		return samples_ == nullptr;
	}

	size_t Buffer::get_number_of_samples() const
	{
		return number_of_samples_;
	}
}
