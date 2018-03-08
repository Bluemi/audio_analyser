#include <iostream>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/converting/SamplesToFrequencies.hpp>
#include <audio/frequencies/FrequencyBlock.hpp>
#include <audio/frequencies/FrequencyBuffer.hpp>
#include <audio/channel/Channel.hpp>
#include <time/Time.hpp>

#include <cmath>

void compute_DCT_IV(const float* input_array, float* output_array, size_t size) {
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
	if (analyser::SampleBuffer::load_from_file("res/the_who.wav", &buffer)) {
		size_t sample_index = 44100*41; // 41 seconds
		size_t width = 256;
		analyser::SamplesToFrequencies stf(buffer, width);

		analyser::Time start_time = buffer.number_of_samples_to_time(sample_index);
		analyser::Time end_time = buffer.number_of_samples_to_time(sample_index + width);

		analyser::FrequencyBuffer fbuffer = stf.convert(start_time, end_time);

		analyser::FrequencyBlock fb;

		if (fbuffer.get_frequency_block(0, analyser::Time::from_number_of_samples(0, 44100), &fb)) {
			analyser::Channel::Block sb;
			if (buffer.get_block(0, start_time, end_time, &sb)) {
				float own_out_array[width];
				compute_DCT_IV(sb.get_samples(), own_out_array, width);

				std::cout << "  fftw      own_out_array * 2" << std::endl;

				for (size_t i = 0; i < fb.get_size(); i++) {
					// std::cout << i << ". " << fb.get_data()[i] << "  \t" << own_out_array[i] * 2.f << std::endl;
					if (std::abs(fb.get_frequencies()[i] - own_out_array[i] * 2.f) > 0.1f) {
						failed = 1;
						std::cout << i << ". " << fb.get_frequencies()[i] << "      " << own_out_array[i] * 2.f << std::endl;
					}
				}
			} else {
				failed = 1;
				std::cout << "couldn't get block at start_time: " << start_time.get_number_of_samples() << std::endl;
			}
		} else {
			failed = 2;
			std::cout << "couldn't initialize frequency buffer" << std::endl;
		}

		// std::cout << "samples:" << std::endl;
		// for (auto iter = buffer.get_iterator_at(0, start_time); iter != buffer.get_iterator_at(0, end_time); ++iter) {
		// 	std::cout << *iter << std::endl;
		// }
	} else {
		failed = 3;
		std::cout << "couldn't load \"the_who.wav\" frequency buffer" << std::endl;
	}
	return failed;
}
