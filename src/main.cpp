#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <cmath>

#include <audio/AudioFile.hpp>
#include <math/BoundsGrouper.hpp>

#define INPUT_FILE_PATH "./test/test1.wav"
const float DURATION = 0.03f;
const int window_width = 199;
const int NUM_OF_SUBBANDS = 20;
const float SCALE = 4.f;
const float SCALE_FREQ = 2.7f;
const float DELAY = 0.0f;

long int unix_micros();
void render(int left_value, int right_value, int width);
void render_single(int value, int width);

float round(float value, int position)
{
	const int factor = pow(10, position);
	const int new_value = (int)(factor*value);
	return new_value / (float)factor;
}

void test_runtime(const AudioFile &file)
{
	const float MAX_TIME = file.getDuration().getSeconds();

	const long int frame_time_micros = (long int) (1000000.f * DURATION);
	long int first_frame_unix_micros;
	{
		const long int pre_begin_micros = unix_micros();
		first_frame_unix_micros = pre_begin_micros - (pre_begin_micros % frame_time_micros) + frame_time_micros;
		usleep(first_frame_unix_micros - pre_begin_micros);
	}

	long int frameCounter = 0;

	float time = 0.f;

	system("cvlc " INPUT_FILE_PATH " &");

	while (time < MAX_TIME)
	{
		const long int current_time = unix_micros();
		if (frameCounter * frame_time_micros + first_frame_unix_micros > current_time)
		{
			usleep(frameCounter * frame_time_micros + first_frame_unix_micros - current_time);
		}
		else
		{
			std::cout << "overload" << std::endl;
		}

		const std::vector<float> frequencies = file.getScaledFrequencySubbands(file.secondsToTime(time), file.secondsToTime(DURATION*0.2f));
		for (unsigned int i = 0; i+1 < frequencies.size(); i++)
		{
			//render_single(frequencies[i]*SCALE_FREQ, window_width/frequencies.size());
			std::cout << frequencies[i] << "  ";
		}
		std::cout << std::endl;
		frameCounter++;
		time += DURATION;
	}
	system("pkill vlc");
}

int main()
{
	AudioFile file = AudioFile::fromPath(INPUT_FILE_PATH);
	file.print();
	test_runtime(file);

	return 0;
}

void render_single(int value, int width)
{
	value = std::abs(value);
	if (value > width)
	{
		value = width;
	}
	value--;
	std::cout << "|";
	std::cout << " value=" << value << std::endl;
	for (int i = 0; i < value; i++)
	{
		std::cout << ">";
	}
	for (int i = 0; i < (width - value); i++)
	{
		std::cout << " ";
	}
}

void render(int left_value, int right_value, int width)
{
	left_value = std::abs(left_value);
	right_value = std::abs(right_value);
	const int half_width = width/2-1;
	if (left_value > half_width)
	{
		left_value = half_width;
	}
	if (right_value > half_width)
	{
		right_value = half_width;
	}
	for (int i = 0; i < half_width - left_value; i++)
	{
		std::cout << " ";
	}
	for (int i = 0; i < left_value; i++)
	{
		std::cout << "<";
	}
	std::cout << "|";
	for (int i = 0; i < right_value; i++)
	{
		std::cout << ">";
	}
	for (int i = 0; i < half_width - right_value-1; i++)
	{
		std::cout << " ";
	}
}

long int unix_micros()
{
	using namespace std::chrono;
	return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}
