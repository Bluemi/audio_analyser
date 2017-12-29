#ifndef __CHANNEL_CLASS__
#define __CHANNEL_CLASS__

#include <cstddef>

#include <time/Time.hpp>

namespace analyser {
	class Channel
	{
		public:
			Channel();
			Channel(float* samples, size_t number_of_samples, unsigned int samplerate);
			~Channel();

			void set_all(float* samples, size_t number_of_samples, unsigned int samplerate);

			// Properties
			bool is_empty() const;
			unsigned int get_samplerate() const;
			Time get_duration() const;

			// Time
			Time seconds_to_time(float seconds) const;
			Time number_of_samples_to_time(size_t number_of_samples) const;

			// Iterator
			class Iterator
			{
				public:
					Iterator();
					Iterator(const Iterator& original) = default;
					Iterator(float* samples, size_t initial_offset);
					Iterator& operator=(const Iterator& original) = default;

					bool operator==(const Channel::Iterator& iterator) const;
					bool operator!=(const Channel::Iterator& iterator) const;

					bool operator<(const Channel::Iterator& iterator) const;
					bool operator>(const Channel::Iterator& iterator) const;
					bool operator<=(const Channel::Iterator& iterator) const;
					bool operator>=(const Channel::Iterator& iterator) const;

					float& operator*() const;

					Iterator operator++(int);
					Iterator operator++();

					Iterator operator--(int);
					Iterator operator--();

					void operator+=(int step);
					void operator-=(int step);

					float operator[](int index) const;
				private:
					float* samples_;
			};

		private:
			float* samples_;
			size_t number_of_samples_;
			unsigned int samplerate_;
	};
	// Iterator Functions
	Channel::Iterator operator+(Channel::Iterator iterator, int step);

	Channel::Iterator operator-(Channel::Iterator iterator, int step);

}

#endif
