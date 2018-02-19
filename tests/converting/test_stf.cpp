#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/converting/SamplesToFrequencies.hpp>
#include <cmath>

void compute_DCT_IV(float* input_array, float* output_array, size_t size) {
	for (size_t k = 0; k < size; k++) {
		output_array[k] = 0.f;
		for (size_t n = 0; n < size; n++) {
			output_array[k] += input_array[n] * cos((M_PI/size) * (n + 0.5f)*(k+0.5f));
		}
	}
}

int main() {
	analyser::SampleBuffer buffer;
	int failed = 0;
	if (analyser::SampleBuffer::load_from_file("audio_tests/test1.wav", &buffer)) {
		analyser::SamplesToFrequencies stf;
		stf.bind(buffer);
		size_t sample_index = 44100*41; // 41 seconds
		size_t width = 256;

		analyser::Time start_time = buffer.number_of_samples_to_time(sample_index);
		analyser::Time end_time = buffer.number_of_samples_to_time(sample_index + width);

		analyser::FrequencyBuffer fbuffer = stf.convert(start_time, end_time);

		analyser::Buffer fb;

		if (fbuffer.get_frequencies(0, &fb)) {
			analyser::Channel::Block sb;
			if (buffer.get_block(0, start_time, end_time, &sb)) {
				float own_out_array[width];
				compute_DCT_IV(sb.get_samples(), own_out_array, width);

				//std::cout << "     fftw                own_out_array * 2" << std::endl;

				for (size_t i = 0; i < fb.get_size(); i++) {
					// std::cout << i << ". " << fb.get_data()[i] << "  \t" << own_out_array[i] * 2.f << std::endl;
					if (std::abs(fb.get_data()[i] - own_out_array[i] * 2.f) > 0.1f) {
						failed = 1;
						std::cout << "     fftw                own_out_array * 2" << std::endl;
						std::cout << i << ". " << fb.get_data()[i] << "      " << own_out_array[i] * 2.f << std::endl;
					}
				}
			} else failed = 1;
		} else failed = 1;

		// std::cout << "samples:" << std::endl;
		// for (auto iter = buffer.get_iterator_at(0, start_time); iter != buffer.get_iterator_at(0, end_time); ++iter) {
		// 	std::cout << *iter << std::endl;
		// }
	} else failed = 1;
	return failed;
}
