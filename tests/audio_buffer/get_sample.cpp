#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/channel/Channels.hpp>

#include <math.h>

#define INPUT_PATH "./audio_tests/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;

	analyser::SampleBuffer buffer;
	if (analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		analyser::Sample sample;
		if (buffer.get_sample_at(buffer.seconds_to_time(20.3), &sample)) {
			float subsample;
			std::cout << "number_of_subsamples:" << sample.get_number_of_channels() << std::endl;
			if (sample.get_subsample(analyser::StereoChannel::LEFT, &subsample)) {
				if (isnan(subsample)) {
					failed = 1;
				}
			} else {
				failed = 2;
			}
		} else {
			failed = 3;
		}
	} else {
		failed = 4;
	}
	return failed;
}
