#include <iostream>

#include <audio/AudioBuffer.hpp>

#define INPUT_PATH "./test_audio_files/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;
	analyser::AudioBuffer buffer;
	if (!analyser::AudioBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		failed = 1;
	}
	return failed;
}
