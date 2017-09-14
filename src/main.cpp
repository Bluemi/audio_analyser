#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

#include <AudioFile.hpp>

const char* INPUT_FILE_PATH = "./test1.wav";
const float dur = 0.02f;
const int window_width = 199;
float MAX_TIME = 0.f;

void tick(const AudioFile &file, const float time);
long int unix_micros();

int main()
{
	AudioFile file = AudioFile::fromPath(INPUT_FILE_PATH);

	file.print();

	MAX_TIME = file.getDuration().getSeconds(44100);

	const long int frame_time_micros = (long int) (1000000.f * dur);
	long int first_frame_unix_micros;
	{
		const long int pre_begin_micros = unix_micros();
		first_frame_unix_micros = pre_begin_micros - (pre_begin_micros % frame_time_micros) + frame_time_micros;
		usleep(first_frame_unix_micros - pre_begin_micros);
	}

	long int frameCounter = 0;

	float time = 0.f;

	while (time < MAX_TIME)
	{
		const long int current_time = unix_micros();
		if (frameCounter * frame_time_micros + first_frame_unix_micros > current_time)
		{
			usleep(frameCounter * frame_time_micros + first_frame_unix_micros - current_time);
		}

		tick(file, time);
		time += dur;
		frameCounter++;
	}
	return 0;
}

void render(float left_value, float right_value, float width)
{
	const float half_width = width/2.f;
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
	for (int i = 0; i < right_value; i++)
	{
		std::cout << ">";
	}
	for (int i = 0; i < half_width - right_value-1; i++)
	{
		std::cout << " ";
	}
}

const float scale = 15.f;

void tick(const AudioFile &file, const float time)
{
	const int loudness_left = (int)(file.getLoudness_sum(FrameTime::fromSeconds((float)time, 44100), FrameTime::fromSeconds(dur, 44100), StereoChannel::LEFT)*scale);
	const int loudness_right = (int)(file.getLoudness_sum(FrameTime::fromSeconds((float)time, 44100), FrameTime::fromSeconds(dur, 44100), StereoChannel::RIGHT)*scale);
	const int loudness_left2 = (int)(file.getLoudness_diff(FrameTime::fromSeconds((float)time, 44100), FrameTime::fromSeconds(dur, 44100), StereoChannel::LEFT)*scale);
	const int loudness_right2 = (int)(file.getLoudness_diff(FrameTime::fromSeconds((float)time, 44100), FrameTime::fromSeconds(dur, 44100), StereoChannel::RIGHT)*scale);
	render(loudness_left, loudness_right, window_width/2.f);
	render(loudness_left2, loudness_right2, window_width/2.f);
	std::cout << std::endl;
}

long int unix_micros()
{
	using namespace std::chrono;
	return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}
