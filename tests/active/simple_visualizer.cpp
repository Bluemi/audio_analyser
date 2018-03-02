#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>

const char* AUDIO_PATH = "res/test1.wav";

int main() {
	analyser::SampleBuffer sample_buffer;
	if (analyser::SampleBuffer::load_from_file(AUDIO_PATH, &sample_buffer)) {
	} else {
		std::cout << "couldn't load " << AUDIO_PATH << std::endl;
	}
}
