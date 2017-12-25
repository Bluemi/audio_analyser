#include <iostream>

#include <audio/AudioBuffer.hpp>
#include <audio/Channels.hpp>

#define INPUT_PATH "./audio_tests/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;

	analyser::AudioBuffer buffer;

	if (analyser::AudioBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		float sum = 0.f;
		for (analyser::AudioBuffer::Iterator iter = buffer.begin(); iter != buffer.end(); ++iter) {
			float f = 0.f;
			if ((*iter).get_subsample(analyser::StereoChannel::LEFT, &f)) {
				sum += f;
			} else {
				failed = 1;
				break;
			}
		}
		std::cout << "sum=" << sum << std::endl;
	} else {
		failed = 1;
	}

	return failed;
}
