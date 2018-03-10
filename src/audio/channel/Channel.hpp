#ifndef __CHANNEL_CLASS__
#define __CHANNEL_CLASS__

#include <cstddef>
#include <functional>

#include <buffer/Buffer.hpp>
#include <audio/channel/ChannelIterator.hpp>
#include <audio/channel/ChannelBlock.hpp>

namespace analyser {
	class Time;
	class ChannelBlock;

	class Channel
	{
		public:
			Channel();
			Channel(const Buffer& buffer, unsigned int samplerate);
			~Channel();

			void set_all(const Buffer& buffer, unsigned int samplerate);

			// Properties
			bool is_empty() const;
			unsigned int get_samplerate() const;
			size_t get_number_of_samples() const;
			Time get_duration() const;

			// Time
			Time seconds_to_time(float seconds) const;
			Time number_of_samples_to_time(size_t number_of_samples) const;

			// Iterator
			using Iterator = ChannelIterator;

			Iterator begin() const;
			Iterator end() const;
			Iterator get_iterator_at(const Time& time) const;
			Iterator get_iterator_at_sample(const size_t offset) const;

			size_t get_block(const Time& begin_time, const Time& end_time, ChannelBlock* block) const;

			// Subsample Access
			bool get_subsample_at(const Time& time, float* subsample);
			bool get_subsample_at_seconds(double seconds, float* subsample);

		private:
			Buffer buffer_;
			unsigned int samplerate_;
	};
}

#endif
