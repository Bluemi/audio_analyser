#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/buffer/SampleBufferIterator.hpp>
#include <audio/channel/Channels.hpp>

#define INPUT_PATH "./res/"
#define INPUT_FILE_PATH INPUT_PATH"test_stereo.wav"

int main() {
	int failed = 0;

	analyser::SampleBuffer buffer;

	if (analyser::SampleBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		analyser::SampleBuffer::Iterator iterator = buffer.begin();
		iterator += 3;
		float f = iterator.get_subsample(0);
		// test increment
		iterator++;
		iterator--;

		if (iterator.get_subsample(0) == f) {
			analyser::SampleBuffer::Iterator iterator2;
			iterator2 = iterator;
			if (iterator == iterator2) {
				++iterator;
				if (iterator-1 == iterator2) {
					if (iterator > iterator2) {
						if (iterator+1 != iterator2) {
							if (! (iterator == iterator2+1)) {
								failed = 1;
							}
						} else { failed = 1; }
					} else { failed = 1; }
				} else { failed = 1; }
			} else { failed = 1; }
		} else { failed = 1; }
	} else { failed = 1; }

	return failed;
}
