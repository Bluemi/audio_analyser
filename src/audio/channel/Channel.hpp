#ifndef __CHANNEL_CLASS__
#define __CHANNEL_CLASS__

#include <cstddef>
#include <functional>

#include <time/Time.hpp>
#include <buffer/Buffer.hpp>
#include <audio/iterator/ChannelIterator.hpp>

namespace analyser {
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

			ChannelIterator begin() const;
			ChannelIterator end();
			ChannelIterator get_iterator_at(const Time& time);
			ChannelIterator get_iterator_at_sample(const size_t offset);

			// Block
			class Block
			{
				public:
					Block();
					Block(const Block& original) = default;
					Block(const Buffer& buffer);

					float& operator[](size_t index) const;
					bool set_subsample(size_t index, float subsample);

					bool get_subsample(size_t index, float* subsample) const;
					float* get_samples() const;

					size_t get_number_of_samples() const;
					bool is_empty() const;

					ChannelIterator begin() const;
					ChannelIterator end() const;
					ChannelIterator get_iterator_at_sample(size_t index) const;

					void manipulate(std::function<void(float&, size_t, size_t)> function);

				private:
					Buffer buffer_;
			};

			size_t get_block(const Time& begin_time, const Time& end_time, Block* block) const;

			// Subsample Access
			bool get_subsample_at(const Time& time, float* subsample);
			bool get_subsample_at_seconds(double seconds, float* subsample);

		private:
			Buffer buffer_;
			unsigned int samplerate_;
	};
}

#endif
