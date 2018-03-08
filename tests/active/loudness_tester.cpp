#include <iostream>
#include <thread>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/channel/Channels.hpp>
#include <time/Time.hpp>

const unsigned int SCREEN_WIDTH = 180;
const unsigned int NUMBER_OF_FREQUENCIES = 2048;
const std::string DEFAULT_AUDIO_PATH = "res/test_stereo_rhythm.wav";

const unsigned int BAND_WIDTH = 50;

void play_song(const std::string& audio_path) {
	std::string system_command = "cvlc " + audio_path + " --play-and-exit &>/dev/null &";
	system(system_command.c_str());
}

float abs(float v) {
	if (v < 0.f) {
		return -v;
	}
	return v;
}

float min(float a, float b) {
	return a<b?a:b;
}

void render_band(float value) {
	value = min(value, 1.f);
	unsigned int width = value * BAND_WIDTH;
	for (unsigned int i = 0; i < BAND_WIDTH; i++) {
		if (i < width) {
			std::cout << ">";
		} else {
			std::cout << " ";
		}
	}
}

void render(float f1, float f2) {
	render_band(f1);
	render_band(f2);
	std::cout << "\n";
}

int main(int argc, char* argv[]) {
	analyser::SampleBuffer sample_buffer;
	std::string audio_path;
	if (argc > 1) {
		audio_path = argv[1];
	} else {
		audio_path = DEFAULT_AUDIO_PATH;
	}
	std::cout << audio_path << std::endl;
	if (analyser::SampleBuffer::load_from_file(audio_path.c_str(), &sample_buffer)) {
		analyser::Time end_time = sample_buffer.number_of_samples_to_time((sample_buffer.get_duration().get_number_of_samples() / NUMBER_OF_FREQUENCIES) * NUMBER_OF_FREQUENCIES);

		play_song(audio_path);
		int wait_time = (int)(1000 * sample_buffer.number_of_samples_to_time(NUMBER_OF_FREQUENCIES).get_seconds());

		for (analyser::Time t = sample_buffer.number_of_samples_to_time(0); t < end_time; t = t + NUMBER_OF_FREQUENCIES) {
			analyser::Channel::Block sample_block;
			float max_value_left = 0.f;
			if (sample_buffer.get_block(analyser::StereoChannel::LEFT, t, t + NUMBER_OF_FREQUENCIES, &sample_block)) {
				for (auto iter = sample_block.begin(); iter != sample_block.end(); ++iter) {
					if (max_value_left < abs(*iter)) {
						max_value_left = abs(*iter);
					}
				}
			} else {
				std::cout << "couldn't get left block at sample " << t.get_number_of_samples() << std::endl;
				break;
			}

			float max_value_right = 0.f;
			if (sample_buffer.get_number_of_channels() > 1) {
				if (sample_buffer.get_block(analyser::StereoChannel::RIGHT, t, t + NUMBER_OF_FREQUENCIES, &sample_block)) {
					for (auto iter = sample_block.begin(); iter != sample_block.end(); ++iter) {
						if (max_value_right < abs(*iter)) {
							max_value_right = abs(*iter);
						}
					}
				} else {
					std::cout << "couldn't get right block at sample " << t.get_number_of_samples() << std::endl;
					break;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
			render(max_value_left, max_value_right);
		}
	} else {
		std::cout << "couldn't load " << audio_path << std::endl;
	}

	return 0;
}
