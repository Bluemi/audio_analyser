#include <iostream>

#include <audio/buffer/AudioBuffer.hpp>
#include <audio/channel/Channels.hpp>

#include <math.h>

#define INPUT_PATH "./audio_tests/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;

	analyser::AudioBuffer buffer;
	if (analyser::AudioBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		analyser::Sample sample;
		if (buffer.get_sample_at(buffer.seconds_to_time(20.3), &sample)) {
			float subsample;
			if (sample.get_subsample(analyser::StereoChannel::LEFT, &subsample)) {
				if (isnan(subsample)) {
					failed = 1;
				}
			} else {
				failed = 1;
			}
		} else {
			failed = 1;
		}
	} else {
		failed = 1;
	}
	return failed;
}
