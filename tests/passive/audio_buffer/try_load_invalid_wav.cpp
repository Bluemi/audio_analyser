#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>

#define INPUT_PATH "./res/"
#define INPUT_FILE_PATH INPUT_PATH"invalid_wav.wav"

int main() {
	int failed = 0;
	analyser::SampleBuffer buffer;
	if (analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		failed = 1;
	}
	return failed;
}

