#include <iostream>

#include <audio/AudioBuffer.hpp>
#include <audio/Channels.hpp>

#define INPUT_PATH "./audio_tests/"
#define INPUT_FILE_PATH INPUT_PATH"test1.wav"

int main() {
	int failed = 0;

	analyser::AudioBuffer buffer;

	if (analyser::AudioBuffer::load_from_file(INPUT_FILE_PATH, &buffer)) {
		analyser::AudioBuffer::Iterator iterator = buffer.begin();
		iterator += 3;
		float f = iterator.get_subsample(0);
		// test increment
		iterator++;
		iterator--;

		if (iterator.get_subsample(0) == f) {
			analyser::AudioBuffer::Iterator iterator2;
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
