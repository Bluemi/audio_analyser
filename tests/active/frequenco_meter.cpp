#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/converting/SamplesToFrequencies.hpp>
#include <audio/frequencies/FrequencyBuffer.hpp>
#include <audio/frequencies/FrequencyBlock.hpp>

#include <audio/channel/Channels.hpp>
#include <audio/converting/WindowFunction.hpp>
#include <time/Time.hpp>
#include <time/PartialTime.hpp>

const unsigned int SCREEN_WIDTH = 180;
const unsigned int NUMBER_OF_RENDER_BANDS = 10;
const unsigned int NUMBER_OF_FREQUENCIES = 2048*2;
const std::string DEFAULT_AUDIO_PATH = "res/the_who.wav";

const unsigned int BAND_WIDTH = SCREEN_WIDTH / NUMBER_OF_RENDER_BANDS;
const unsigned int NUMBER_OF_FREQUENCIES_PER_BAND = NUMBER_OF_FREQUENCIES / NUMBER_OF_RENDER_BANDS;
const float MAX_VALUE = 10.f;
const float MAX_BAND_VALUES[] { 5572.38, 4527.65, 3167.44, 558.048, 526.94, 675.507, 261.743, 1267.84, 1344.45, 2225.26 };

int index_sum = 0;

void play_song(const std::string& audio_path) {
	std::string system_command = "cvlc " + audio_path + " --play-and-exit &>/dev/null &";
	system(system_command.c_str());
}

void render(float* samples) {
	float max_value = 0.f;
	unsigned int max_value_index = 0;
	for (unsigned int i = 0; i < NUMBER_OF_FREQUENCIES; i++) {
		if (max_value < samples[i]) {
			max_value = samples[i];
			max_value_index = i;
		}
	}
	std::cout << "> " << max_value_index << std::endl;
	index_sum += max_value_index;
}

int main(int argc, char* argv[]) {
	analyser::SampleBuffer sample_buffer;
	std::string audio_path;
	if (argc > 1) {
		audio_path = argv[1];
	} else {
		audio_path = DEFAULT_AUDIO_PATH;
	}
	if (analyser::SampleBuffer::load_from_file(audio_path.c_str(), &sample_buffer)) {
		analyser::SamplesToFrequencies stf(sample_buffer, NUMBER_OF_FREQUENCIES, analyser::von_hann_window);
		analyser::FrequencyBuffer frequency_buffer = stf.convert((size_t)0, sample_buffer.get_duration());

		int wait_time = (int)(1000 * sample_buffer.number_of_samples_to_time(NUMBER_OF_FREQUENCIES).get_seconds());

		// print status information
		std::cout << "number_of_samples of song: " << sample_buffer.get_duration().get_number_of_samples() << std::endl;
		std::cout << "wait_time: " << wait_time << std::endl;
		std::cout << "frequency_buffer.number_of_blocks(): " << frequency_buffer.get_number_of_blocks() << std::endl;
		std::cout << "frequency_buffer.block_size(): " << frequency_buffer.get_block_size() << std::endl;

		play_song(audio_path);

		// print frequencies
		for (size_t i = 0; i < frequency_buffer.get_number_of_blocks(); i++) {
			analyser::FrequencyBlock frequency_block;
			if (frequency_buffer.get_frequency_block_by_id(analyser::StereoChannel::LEFT, i, &frequency_block)) {
				render(frequency_block.get_frequencies());
				std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
			} else {
				std::cout << "couldn't get block number " << i << std::endl;
				break;
			}
		}

		std::cout << "average index = " << index_sum / (float) frequency_buffer.get_number_of_blocks() << std::endl;
	} else {
		std::cout << "couldn't load " << audio_path << std::endl;
	}

	return 0;
}
