#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>

#define INPUT_PATH "./audio_tests/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;
	analyser::SampleBuffer buffer;
	if (!analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		failed = 1;
	}
	return failed;
}
