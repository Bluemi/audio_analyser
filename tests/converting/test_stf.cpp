#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/converting/SamplesToFrequencies.hpp>

int main() {
	analyser::SampleBuffer buffer;
	if (analyser::SampleBuffer::load_from_file("audio_tests/test1.wav", &buffer)) {
		analyser::SamplesToFrequencies stf;
		stf.bind(buffer);
		analyser::FrequencyBuffer fbuffer = stf.convert(buffer.number_of_samples_to_time(1000), buffer.number_of_samples_to_time(1256));

		analyser::Buffer fb;
		if (fbuffer.get_frequencies(0, &fb)) {
			for (size_t i = 0; i < fb.get_size(); i++) {
				std::cout << fb.get_data()[i] << std::endl;
			}
		}
	}
	return 0;
}
