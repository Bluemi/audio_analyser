#include <iostream>
#include <thread>

#include <audio/buffer/SampleBuffer.hpp>
#include <audio/channel/Channels.hpp>
#include <audio/channel/Channel.hpp>
#include <audio/volume/SamplesToVolume.hpp>
#include <audio/volume/VolumeBuffer.hpp>
#include <audio/channel/Channels.hpp>
#include <time/Time.hpp>
#include <time/PartialTime.hpp>

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
	std::string audio_path;
	if (argc > 1) {
		audio_path = argv[1];
	} else {
		audio_path = DEFAULT_AUDIO_PATH;
	}

	std::cout << audio_path << std::endl;

	analyser::SampleBuffer sample_buffer;
	if (analyser::SampleBuffer::load_from_file(audio_path.c_str(), &sample_buffer)) {
		analyser::SamplesToVolume stv(sample_buffer);
		analyser::VolumeBuffer volume_buffer = stv.convert((size_t)0, sample_buffer.get_duration());

		int wait_time = (int)(1000 * sample_buffer.number_of_samples_to_time(NUMBER_OF_FREQUENCIES).get_seconds());

		play_song(audio_path);

		for (unsigned int i = 0; i < volume_buffer.get_number_of_volumes(); i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
			render(volume_buffer.get_volume(analyser::StereoChannel::LEFT, i), volume_buffer.get_volume(analyser::StereoChannel::RIGHT, i));
		}
	} else {
		std::cout << "couldn't load " << audio_path << std::endl;
	}

	return 0;
}
