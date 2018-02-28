#include <buffer/Buffer.hpp>
#include <buffer/BufferSection.hpp>

#include <iostream>

int main() {
	// create a Buffer with 100 samples
	analyser::BufferSection section;

	{
		analyser::Buffer b(100);
		section = b.get_section(50, 70);
	}
	float sum = 0.f;
	for (float* f = section.get_data(); f != section.get_data()+section.get_size(); f++) {
		sum += *f;
	}
	std::cout << "sum: " << sum << std::endl;
	return 0;
}
