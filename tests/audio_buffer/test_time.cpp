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
		if (buffer.number_of_samples_to_time(44100).get_number_of_samples() != analyser::Time::from_seconds(1.0f, 44100).get_number_of_samples()) {
			failed = 1;
		}
		if (buffer.seconds_to_time(25.2).get_number_of_samples() != analyser::Time::from_seconds(25.2f, 44100).get_number_of_samples()) {
			failed = 1;
		}
	}
	return failed;
}
