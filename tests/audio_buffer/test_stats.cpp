#include <iostream>

#include <audio/AudioBuffer.hpp>

#define INPUT_PATH "./audio_tests/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;
	analyser::AudioBuffer buffer;
	if (!analyser::AudioBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		failed = 1;
	} else {
		std::cout << "samplerate: " << buffer.get_samplerate() << std::endl;
		std::cout << "number of channels: " << buffer.get_number_of_channels() << std::endl;
		std::cout << "is empty: " << buffer.is_empty() << std::endl;
		std::cout << "duration: " << buffer.get_duration().getSeconds() << " Seconds" << std::endl;
	}
	return failed;
}
