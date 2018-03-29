#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/channel/Channels.hpp>
#include <audio/sample/Sample.hpp>
#include <time/PartialTime.hpp>

#include <math.h>

#define INPUT_PATH "./res/"
#define INPUT_FILE_PATH INPUT_PATH"the_who.wav"

int main() {
	int failed = 0;

	analyser::SampleBuffer buffer;
	if (analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		analyser::Sample sample;
		if (buffer.get_sample_at(20.3, &sample)) {
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
