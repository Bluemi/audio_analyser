#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/channel/Channels.hpp>

#define INPUT_PATH "./res/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;

	analyser::SampleBuffer buffer;

	if (analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		analyser::Channel channel;
		if (buffer.get_channel(analyser::StereoChannel::LEFT, &channel)) {
			std::cout << "channel.duration = " << channel.get_duration().get_seconds() << std::endl;
			analyser::Channel::Block block;
			size_t number_of_copied_samples = channel.get_block(channel.seconds_to_time(2.0), channel.number_of_samples_to_time(5), &block);
			std::cout << "number_of_copied_samples = " << number_of_copied_samples << std::endl;
			if (number_of_copied_samples > 0) {
				std::cout << "number_of_samples = " << block.get_number_of_samples() << std::endl;
				block.manipulate([](float& subsample, size_t index, size_t number_of_samples) { subsample = index / (float) (number_of_samples-1); });
				for (float& f : block) {
					std::cout << f << std::endl;
				}
			} else {
				failed = 1;
			}
		} else {
			failed = 1;
		}
	} else {
		failed = 1;
	}

	return failed;
}
