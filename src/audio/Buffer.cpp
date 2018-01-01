#include "Buffer.hpp"

#include <iostream>

namespace analyser {
	Buffer::Buffer()
		: samples_(nullptr), number_of_references_(nullptr)
	{}

	Buffer::Buffer(size_t number_of_samples)
	{
		samples_ = (float*)::operator new(sizeof(float) * number_of_samples);
		number_of_references_ = (unsigned int*)::operator new(sizeof(unsigned int));
		*number_of_references_ = 1;

		std::cout << "allocated " << number_of_samples << " samples" << std::endl;
	}

	Buffer::Buffer(const Buffer& buffer)
		: samples_(buffer.samples_), number_of_references_(buffer.number_of_references_)
	{
		plus_reference();
	}

	void Buffer::operator=(const Buffer& buffer)
	{
		samples_ = buffer.samples_;
		number_of_references_ = buffer.number_of_references_;
		plus_reference();
	}

	Buffer::~Buffer()
	{
		minus_reference();
		if (*number_of_references_ == 0) {
			delete samples_;
			delete number_of_references_;
			std::cout << "freed" << std::endl;
		}
	}

	void Buffer::plus_reference()
	{
		if (number_of_references_ != nullptr)
			(*number_of_references_)++;
	}

	void Buffer::minus_reference()
	{
		if (number_of_references_ != nullptr)
			(*number_of_references_)--;
	}

	float* Buffer::get_samples() const
	{
		return samples_;
	}
}
