#ifndef __CHANNELBLOCK_CLASS__
#define __CHANNELBLOCK_CLASS__

#include <cstdlib>

#include <buffer/BufferSection.hpp>
#include <audio/channel/ChannelIterator.hpp>

namespace analyser {
	class ChannelBlock
	{
		public:
			ChannelBlock();
			ChannelBlock(const ChannelBlock& original) = default;
			ChannelBlock(const BufferSection& buffer_section);

			float operator[](size_t index) const;

			bool get_subsample(size_t index, float* subsample) const;
			const float* get_samples() const;

			size_t get_number_of_samples() const;
			bool is_empty() const;

			ChannelIterator begin() const;
			ChannelIterator end() const;
			ChannelIterator get_iterator_at_sample(size_t index) const;
		private:
			BufferSection buffer_section_;
	};
}

#endif
