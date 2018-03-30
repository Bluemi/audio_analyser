#ifndef __SAMPLETOVOLUME_CLASS__
#define __SAMPLETOVOLUME_CLASS__

#include <audio/buffer/SampleSource.hpp>

namespace analyser {
	class VolumeBuffer;

	class SamplesToVolume
	{
		public:
			SamplesToVolume();
			SamplesToVolume(const SampleSource& sample_source);
			SamplesToVolume(size_t block_size);
			SamplesToVolume(const SampleSource& sample_source, size_t block_size);

			void bind(const SampleSource& sample_source);
			void unbind();

			VolumeBuffer convert(const PartialTime& begin_time, const PartialTime& end_time) const;
		private:
			VolumeBuffer convert_impl(const SampleBuffer& sample_buffer, const PartialTime& begin_time, const PartialTime& end_time) const;

			SampleSource sample_source_;
			size_t block_size_;

		friend class Overloader;
	};
}

#endif
