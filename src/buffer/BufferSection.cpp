#include "BufferSection.hpp"

#include <cstring> // for memcpy
#include <algorithm> // for swap

#include <buffer/Buffer.hpp>

namespace analyser {
	BufferSection::BufferSection()
		: data_(nullptr), size_(0), origin_(nullptr), number_of_references_(nullptr)
	{}

	BufferSection::BufferSection(float* data, size_t size, float* origin, unsigned int * number_of_references)
		: data_(data), size_(size), origin_(origin), number_of_references_(number_of_references)
	{
		plus_reference();
	}

	BufferSection::BufferSection(const BufferSection& buffer_section)
		: data_(buffer_section.data_), size_(buffer_section.size_), origin_(buffer_section.origin_), number_of_references_(buffer_section.number_of_references_)
	{
		plus_reference();
	}

	BufferSection& BufferSection::operator=(BufferSection buffer_section)
	{
		swap(*this, buffer_section);
		return *this;
	}

	void BufferSection::swap(BufferSection& buffer_section1, BufferSection& buffer_section2)
	{
		using std::swap;
		swap(buffer_section1.data_, buffer_section2.data_);
		swap(buffer_section1.size_, buffer_section2.size_);
		swap(buffer_section1.origin_, buffer_section2.origin_);
		swap(buffer_section1.number_of_references_, buffer_section2.number_of_references_);
	}

	BufferSection::~BufferSection()
	{
		minus_reference();
	}

	Buffer BufferSection::clone() const
	{
		Buffer buffer;
		if (!is_empty()) {
			buffer.allocate(size_);
			memcpy(buffer.get_data(), data_, sizeof(float) * size_);
		}
		return buffer;
	}

	float* BufferSection::get_data()
	{
		return data_;
	}

	size_t BufferSection::get_size()
	{
		return size_;
	}

	bool BufferSection::is_empty() const
	{
		return data_ == nullptr;
	}

	void BufferSection::plus_reference()
	{
		if (!is_empty()) {
			(*number_of_references_)++;
		}
	}

	void BufferSection::minus_reference()
	{
		if (!is_empty()) {
			(*number_of_references_)--;
			if (*number_of_references_ == 0) {
				delete origin_;
				delete number_of_references_;
				data_ = nullptr;
				size_ = 0;
				origin_ = nullptr;
				number_of_references_ = nullptr;
			}
		}
	}
}
