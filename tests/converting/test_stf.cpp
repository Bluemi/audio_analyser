#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/converting/SamplesToFrequencies.hpp>

int main() {
	analyser::SampleBuffer buffer;
	if (analyser::SampleBuffer::load_from_file("audio_tests/test1.wav", &buffer)) {
		analyser::SamplesToFrequencies stf;
		stf.bind(buffer);
		size_t sample_index = 44100*41; // 41 seconds
		size_t width = 256;

		analyser::Time start_time = buffer.number_of_samples_to_time(sample_index);
		analyser::Time end_time = buffer.number_of_samples_to_time(sample_index + width);

		analyser::FrequencyBuffer fbuffer = stf.convert(start_time, end_time);

		analyser::Buffer fb;
		std::cout << "frequencies:" << std::endl;
		if (fbuffer.get_frequencies(0, &fb)) {
			for (size_t i = 0; i < fb.get_size(); i++) {
				std::cout << i << ". " << fb.get_data()[i] << std::endl;
			}
		}

		std::cout << "samples:" << std::endl;
		for (auto iter = buffer.get_iterator_at(0, start_time); iter != buffer.get_iterator_at(0, end_time); ++iter) {
			std::cout << *iter << std::endl;
		}
	}
	return 0;
}
