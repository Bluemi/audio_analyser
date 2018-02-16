#include "Buffer.hpp"

#include <cstring> // for memcpy
#include <algorithm> // for swap

namespace analyser {
	Buffer::Buffer()
		: data_(nullptr), number_of_references_(nullptr), size_(0)
	{}

	Buffer::Buffer(size_t size)
		: size_(size)
	{
		data_ = (float*)::operator new(sizeof(float) * size);
		number_of_references_ = (unsigned int*)::operator new(sizeof(unsigned int));
		*number_of_references_ = 1;
	}

	Buffer::Buffer(const Buffer& buffer)
		: data_(buffer.data_), number_of_references_(buffer.number_of_references_), size_(buffer.size_)
	{
		plus_reference();
	}

	void Buffer::swap(Buffer& buffer1, Buffer& buffer2)
	{
		using std::swap;
		swap(buffer1.data_, buffer2.data_);
		swap(buffer1.number_of_references_, buffer2.number_of_references_);
		swap(buffer1.size_, buffer2.size_);
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

	void Buffer::allocate(size_t size)
	{
		// this buffers data is overwritten
		minus_reference();

		data_ = (float*)::operator new(sizeof(float) * size);
		number_of_references_ = (unsigned int*)::operator new(sizeof(unsigned int));
		*number_of_references_ = 1;
	}

	void Buffer::clear()
	{
		minus_reference();
		number_of_references_ = nullptr;
		data_ = nullptr;
		size_ = 0;
	}

	Buffer Buffer::clone() const
	{
		Buffer buffer(size_);
		memcpy(buffer.get_data(), get_data(), size_);
		return buffer;
	}

	Buffer Buffer::clone_from_to(size_t start, size_t end)  const
	{
		if (start < end) {
			size_t size = end-start;
			Buffer buffer(size);
			memcpy(buffer.get_data(), get_data()+start, size);
		}
		return Buffer();
	}

	void Buffer::plus_reference()
	{
		if (!is_empty())
			(*number_of_references_)++;
	}

	void Buffer::minus_reference()
	{
		if (!is_empty()) {
			(*number_of_references_)--;
			if (*number_of_references_ == 0) {
				delete data_;
				delete number_of_references_;
				data_ = nullptr;
				number_of_references_ = nullptr;
			}
		}
	}

	float* Buffer::get_data() const
	{
		return data_;
	}

	bool Buffer::is_empty() const
	{
		return data_ == nullptr;
	}

	size_t Buffer::get_size() const
	{
		return size_;
	}
}
