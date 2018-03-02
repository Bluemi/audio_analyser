#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/channel/Channels.hpp>

#define INPUT_PATH "./res/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;

	analyser::SampleBuffer buffer;

	if (analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		float sum = 0.f;

		/*
		auto end = buffer.end();
		for (auto iter = buffer.begin(); iter != end; ++iter) {
			float subsample = iter.get_subsample(analyser::StereoChannel::LEFT);
			sum += subsample;
		}
		*/

		for (auto iter = buffer.begin(analyser::StereoChannel::LEFT); iter != buffer.end(analyser::StereoChannel::LEFT); ++iter) {
			sum += *iter;
		}
		std::cout << "sum=" << sum << std::endl;
	} else {
		failed = 1;
	}

	return failed;
}
