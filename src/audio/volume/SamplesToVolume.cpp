#include "SamplesToVolume.hpp"

#include <audio/volume/VolumeBuffer.hpp>
#include <audio/channel/ChannelBlock.hpp>
#include <time/Time.hpp>
#include <time/PartialTime.hpp>

namespace analyser {
	const unsigned int DEFAULT_BLOCK_SIZE = 2048;

	SamplesToVolume::SamplesToVolume()
	{}

	SamplesToVolume::SamplesToVolume(const SampleSource& sample_source)
		: sample_source_(sample_source), block_size_(DEFAULT_BLOCK_SIZE)
	{}

	SamplesToVolume::SamplesToVolume(size_t block_size)
		: block_size_(block_size)
	{}

	SamplesToVolume::SamplesToVolume(const SampleSource& sample_source, size_t block_size)
		: sample_source_(sample_source), block_size_(block_size)
	{}


	void SamplesToVolume::bind(const SampleSource& sample_source)
	{
		sample_source_ = sample_source;
	}

	void SamplesToVolume::unbind()
	{
		// resets sample_source_
		sample_source_ = SampleSource();
	}

	float abs(float f) {
		if (f < 0.f) return -f;
		return f;
	}

	float block_to_volume(const ChannelBlock& block) {
		float max_value = 0.f;
		for (auto iter = block.begin(); iter != block.end(); ++iter) {
			if (max_value < abs(*iter)) {
				max_value = abs(*iter);
			}
		}
		return max_value;
	}

	VolumeBuffer SamplesToVolume::convert_impl(const SampleBuffer& sample_buffer, const PartialTime& begin_time, const PartialTime& end_time) const
	{
		const Time b_time = begin_time.to_time(sample_buffer.get_samplerate());
		const Time e_time = end_time.to_time(sample_buffer.get_samplerate());
		size_t number_of_samples = e_time.get_number_of_samples() - b_time.get_number_of_samples();
		size_t number_of_blocks = number_of_samples / block_size_ + (number_of_samples%block_size_?1:0);
		unsigned int number_of_channels = sample_buffer.get_number_of_channels();

		VolumeBuffer volume_buffer(sample_buffer.get_number_of_channels(), number_of_blocks, block_size_, sample_buffer.get_samplerate());
		for (unsigned int channel_index = 0; channel_index < number_of_channels; channel_index++) {
			for (size_t block_index = 0; block_index < number_of_blocks; block_index++) {
				Time block_begin = b_time + (block_index * block_size_);
				Time block_end = block_begin + block_size_;
				ChannelBlock sample_block;
				if (sample_buffer.get_block(channel_index, block_begin, block_end, &sample_block)) {
					float* volume = volume_buffer.get_volumes(channel_index) + block_index;
					*volume = block_to_volume(sample_block);
				}
			}
		}
		return volume_buffer;
	}

	// Dispatcher for different SampleSource Types
	class Overloader {
		public:
			Overloader(const SamplesToVolume* stl, const PartialTime& begin_time, const PartialTime& end_time) : stl_(stl), begin_time_(begin_time), end_time_(end_time) {}

			VolumeBuffer operator()(std::monostate) {
				return VolumeBuffer();
			}

			template<typename TSampleSource>
			VolumeBuffer operator()(const TSampleSource& source) {
				return stl_->convert_impl(source, begin_time_, end_time_);
			}

		private:
			const SamplesToVolume* stl_;
			const PartialTime begin_time_;
			const PartialTime end_time_;
	};

	VolumeBuffer SamplesToVolume::convert(const PartialTime& begin_time, const PartialTime& end_time) const
	{
		return std::visit(Overloader(this, begin_time, end_time), sample_source_);
	}
}
