#include "Buffer.hpp"

namespace analyser {
	Buffer::Buffer()
		: samples_(nullptr), number_of_references_(nullptr)
	{}

	Buffer::Buffer(size_t number_of_samples)
	{
		samples_ = (float*)::operator new(sizeof(float) * number_of_samples);
		number_of_references_ = (unsigned int*)::operator new(sizeof(unsigned int));
		*number_of_references_ = 1;
	}

	Buffer::Buffer(const Buffer& buffer)
		: samples_(buffer.samples_), number_of_references_(buffer.number_of_references_)
	{
		plus_reference();
	}

	void Buffer::operator=(const Buffer& buffer)
	{
		minus_reference();
		// if this has the same samples as buffer -> do nothing
		if (this->samples_ == buffer.samples_) {
			return;
		}
		samples_ = buffer.samples_;
		number_of_references_ = buffer.number_of_references_;
		plus_reference();
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
}
