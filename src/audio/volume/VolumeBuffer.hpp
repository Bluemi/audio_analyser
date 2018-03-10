#ifndef __VOLUMEBUFFER_CLASS__
#define __VOLUMEBUFFER_CLASS__

#include <vector>

#include <buffer/Buffer.hpp>

namespace analyser {
	class Time;

	class VolumeBuffer
	{
		public:
			VolumeBuffer();
			VolumeBuffer(unsigned int number_of_channels, size_t number_of_volumes, size_t block_size, unsigned int samplerate);

			float* get_volumes(unsigned int channel_index) const;
			float get_volume(unsigned int channel_index, size_t volume_index) const;
			float get_volume_at(unsigned int channel_index, const Time& time) const;

			size_t get_number_of_volumes() const;
			unsigned int get_number_of_channels() const;
			size_t get_block_size() const;

			Time seconds_to_time(double seconds) const;
			Time number_of_samples_to_time(size_t number_of_samples) const;
		private:
			std::vector<Buffer> channels_;
			size_t number_of_volumes_;
			size_t block_size_;
			unsigned int samplerate_;
	};
}

#endif
