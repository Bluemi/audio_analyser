#include <iostream>
#include <audio/buffer/SampleBuffer.hpp>

#define INCLUDE_PATH "./audio_tests/"
#define INCLUDE_FILE INCLUDE_PATH"test1.wav"

int main() {
	analyser::SampleBuffer buffer;
	if (analyser::SampleBuffer::load_from_file(INCLUDE_FILE, &buffer)) {
		analyser::SampleBuffer buffer_copy = buffer;
	}

	return 0;
}
