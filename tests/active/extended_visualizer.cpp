#include <string>
#include <cstdlib>
#include <thread>
#include <curses.h>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/converting/SamplesToFrequencies.hpp>
#include <audio/frequencies/FrequencyBuffer.hpp>
#include <audio/frequencies/FrequencyBlock.hpp>

#include <audio/channel/Channels.hpp>
#include <audio/converting/WindowFunction.hpp>
#include <time/Time.hpp>
#include <time/PartialTime.hpp>

const unsigned int SCREEN_WIDTH = 180;
const unsigned int SCREEN_HEIGHT = 57;
const unsigned int NUMBER_OF_BINS = SCREEN_WIDTH;
const unsigned int NUMBER_OF_FREQUENCIES = 2048;
const std::string DEFAULT_AUDIO_PATH = "res/the_who.wav";

const unsigned int NUMBER_OF_FREQUENCIES_PER_BAND = NUMBER_OF_FREQUENCIES / NUMBER_OF_BINS;
const float MAX_VALUE = 2.f;
float max_bin_values[NUMBER_OF_BINS] = {1844.88, 1193.94, 887.921, 720.237, 782.236, 833.592, 760.405, 831.123, 803.695, 856.021, 563.842, 714.365, 591.761, 610.401, 476.38, 484.813, 560.088, 351.041, 277.955, 294.297, 234.995, 218.871, 231.037, 164.963, 169.896, 169.567, 165.18, 169.456, 132.383, 187.767, 183.739, 270.698, 290.525, 295.1, 268.957, 295.023, 396.193, 272.208, 156.369, 125.614, 209.046, 185.561, 116.402, 106.616, 144.091, 157.353, 137.961, 141.198, 161.39, 139.873, 145.839, 168.315, 186.543, 189.1, 182.364, 199.296, 277.148, 199.357, 189.428, 168.962, 211.921, 171.781, 174.089, 177.27, 174.96, 157.264, 207.166, 237.036, 164.359, 188.085, 195.472, 162.873, 204.374, 224.709, 170.041, 137.017, 142.389, 196.328, 160.021, 188.697, 139.49, 169.892, 151.668, 181.254, 141.894, 147.211, 152.223, 142.664, 152.857, 118.681, 125.647, 143.697, 113.032, 160.639, 116.328, 140.842, 108.259, 156.43, 123.992, 89.5429, 202.874, 88.0273, 97.4928, 113.734, 72.9365, 77.1759, 60.6573, 76.8671, 63.0425, 69.1685, 72.3886, 60.6731, 62.6597, 51.0542, 44.7787, 41.5379, 35.9307, 27.268, 35.3811, 31.2456, 32.1699, 29.304, 23.7897, 20.387, 24.0516, 21.4462, 16.1338, 18.8844, 12.4199, 13.5963, 15.9234, 12.5274, 13.2364, 15.531, 9.74357, 7.93963, 9.85342, 9.83451, 10.9312, 10.0883, 8.682, 17.9214, 9.60699, 8.56115, 9.7344, 6.8541, 8.48411, 5.37761, 8.13585, 7.7932, 6.58663, 6.62051, 11.0701, 7.0944, 6.21004, 5.3283, 6.42756, 7.19704, 9.83141, 4.56217, 5.66787, 5.47783, 5.37208, 5.02763, 9.48536, 5.74564, 3.97989, 3.99291, 4.82362, 6.27367, 5.23433, 3.28527, 2.94525, 3.55155, 3.34975, 3.31708, 3.73333, 3.39816, 3.82123, 3.47821};

void init_curses() {
	initscr();
	noecho();
}

void play_song(const std::string& audio_path) {
	std::string system_command = "cvlc " + audio_path + " --play-and-exit &>/dev/null &";
	system(system_command.c_str());
}

float min(float a, float b) {
	return a<b?a:b;
}

float abs(float f) {
	if (f < 0.f) {
		return -f;
	}
	return f;
}

float normalize_value(float bin) {
	float value = bin / MAX_VALUE;
	return min(1.f, abs(value));
	
}

void render_bins(float* bins) {
	for (unsigned int x = 0; x < NUMBER_OF_BINS; x++) {
		/*
		if (max_bin_values[x] < abs(bins[x])) {
			max_bin_values[x] = abs(bins[x]);
		}
		*/
		float normalized_value = bins[x];
		normalized_value = normalized_value / max_bin_values[x];
		normalized_value = normalize_value(normalized_value);
		for (unsigned int y = SCREEN_HEIGHT; y > SCREEN_HEIGHT - SCREEN_HEIGHT * normalized_value; y--) {
			mvaddch(y, x, '#');
		}
	}
}

float bins[NUMBER_OF_BINS];

void render(float* frequencies) {
	clear();
	for (unsigned int i = 0; i < NUMBER_OF_BINS; i++) {
		bins[i] = 0.f;
		for (unsigned int j = 0; j < NUMBER_OF_FREQUENCIES_PER_BAND; j++) {
			bins[i] += abs(frequencies[i*NUMBER_OF_FREQUENCIES_PER_BAND+j]);
		}
	}

	render_bins(bins);
	refresh();
}

int main(int argc, char* argv[]) {
	init_curses();

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

		play_song(audio_path);

		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(40.0));

		// print frequencies
		for (size_t i = 0; i < frequency_buffer.get_number_of_blocks(); i++) {
			std::chrono::time_point next_wait_point = std::chrono::system_clock::now() + std::chrono::milliseconds(wait_time);
			analyser::FrequencyBlock frequency_block;
			if (frequency_buffer.get_frequency_block_by_id(analyser::StereoChannel::LEFT, i, &frequency_block)) {
				render(frequency_block.get_frequencies());
			} else {
				break;
			}
			std::this_thread::sleep_until(next_wait_point);
		}
	}

	endwin();

	/*
	for (unsigned int i = 0; i < NUMBER_OF_BINS; i++) {
		std::cout << max_bin_values[i] << ", ";
	}
	*/

	return 0;
}
