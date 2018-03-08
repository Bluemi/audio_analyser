#ifndef __VOLUMEBUFFER_CLASS__
#define __VOLUMEBUFFER_CLASS__

#include <vector>

#include <buffer/Buffer.hpp>

namespace analyser {
	class VolumeBuffer
	{
		public:
			VolumeBuffer();
			VolumeBuffer(unsigned int number_of_channels, size_t number_of_volumes);

			float* get_volumes(unsigned int channel_index) const;
			size_t get_number_of_volumes() const;
			unsigned int get_number_of_channels() const;
		private:
			std::vector<Buffer> channels_;
			size_t number_of_volumes_;
	};
}

#endif
