#include <iostream>
#include <audio/AudioBuffer.hpp>

#define INCLUDE_PATH "./audio_tests/"
#define INCLUDE_FILE INCLUDE_PATH"test1.wav"

int main() {
	analyser::AudioBuffer buffer;
	if (analyser::AudioBuffer::load_from_file(INCLUDE_FILE, &buffer)) {
		analyser::AudioBuffer buffer_copy = buffer;
	}

	return 0;
}
