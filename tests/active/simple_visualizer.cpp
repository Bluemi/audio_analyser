#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/converting/SamplesToFrequencies.hpp>
#include <audio/frequencies/FrequencyBuffer.hpp>
#include <audio/frequencies/FrequencyBlock.hpp>

#include <audio/channel/Channels.hpp>

const unsigned int SCREEN_WIDTH = 180;
const unsigned int NUMBER_OF_RENDER_BANDS = 10;
const unsigned int NUMBER_OF_FREQUENCIES = 2048;
const std::string AUDIO_PATH = "res/test1.wav";

const unsigned int BAND_WIDTH = SCREEN_WIDTH / NUMBER_OF_RENDER_BANDS;
const unsigned int NUMBER_OF_FREQUENCIES_PER_BAND = NUMBER_OF_FREQUENCIES / NUMBER_OF_RENDER_BANDS;
const float MAX_VALUE = 10.f;
const float MAX_BAND_VALUES[] { 5572.38, 4527.65, 3167.44, 558.048, 526.94, 675.507, 261.743, 1267.84, 1344.45, 2225.26 };

void play_song() {
	std::string system_command = "cvlc " + AUDIO_PATH + " &";
	system(system_command.c_str());
}

float abs(float v) {
	if (v < 0.f) {
		return -v;
	}
	return v;
}

void render_band(float value) {
	unsigned int width = value * BAND_WIDTH;
	for (unsigned int i = 0; i < BAND_WIDTH; i++) {
		if (i < width) {
			std::cout << ">";
		} else {
			std::cout << " ";
		}
	}
}

void render(float* frequencies) {
	for (unsigned int band_index = 0; band_index < NUMBER_OF_RENDER_BANDS; band_index++) {
		float value = 0.f;
		for (unsigned int i = 0; i < NUMBER_OF_FREQUENCIES_PER_BAND; i++) {
			value += abs(frequencies[band_index * NUMBER_OF_FREQUENCIES_PER_BAND + i]);
		}
		render_band(value / MAX_BAND_VALUES[band_index]);
	}
	std::cout << "\n";
}

int main() {
	analyser::SampleBuffer sample_buffer;
	if (analyser::SampleBuffer::load_from_file(AUDIO_PATH.c_str(), &sample_buffer)) {
		analyser::SamplesToFrequencies stf(sample_buffer, NUMBER_OF_FREQUENCIES);
		analyser::Time end_time = sample_buffer.number_of_samples_to_time((sample_buffer.get_duration().get_number_of_samples() / NUMBER_OF_FREQUENCIES) * NUMBER_OF_FREQUENCIES);
		analyser::FrequencyBuffer frequency_buffer = stf.convert(sample_buffer.number_of_samples_to_time(0), end_time);

		play_song();
		int number_of_seconds_to_wait = (int)(500 * sample_buffer.number_of_samples_to_time(NUMBER_OF_FREQUENCIES).get_seconds());

		for (size_t i = 0; i < frequency_buffer.get_number_of_blocks(); i++) {
			analyser::FrequencyBlock frequency_block;
			if (frequency_buffer.get_frequency_block_by_id(analyser::StereoChannel::LEFT, i, &frequency_block)) {
				render(frequency_block.get_frequencies());
				std::this_thread::sleep_for(std::chrono::milliseconds(number_of_seconds_to_wait));
			} else {
				std::cout << "couldn't get block number " << i << std::endl;
				break;
			}
		}
	} else {
		std::cout << "couldn't load " << AUDIO_PATH << std::endl;
	}

	return 0;
}
