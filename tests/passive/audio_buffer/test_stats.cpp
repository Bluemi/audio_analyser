#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <time/Time.hpp>

#define INPUT_PATH "./res/"
#define INPUT_FILE_PATH INPUT_PATH"test_stereo.wav"

int main() {
	int failed = 0;
	analyser::SampleBuffer buffer;
	if (!analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		failed = 1;
	} else {
		std::cout << "samplerate: " << buffer.get_samplerate() << std::endl;
		std::cout << "number of channels: " << buffer.get_number_of_channels() << std::endl;
		std::cout << "is empty: " << buffer.is_empty() << std::endl;
		std::cout << "duration: " << buffer.get_duration().get_seconds() << " Seconds" << std::endl;
	}
	return failed;
}
