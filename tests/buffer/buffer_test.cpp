#include <iostream>
#include <audio/Buffer.hpp>

void test_empty() {
	analyser::Buffer buffer;
}

void test_simple() {
	analyser::Buffer buffer(100); // allocate 100 samples
}

void test_assignment_operator() {
	analyser::Buffer buffer1(100);
	analyser::Buffer buffer2 = buffer1;
}

void test_copy_constructor() {
	analyser::Buffer buffer1(100);
	analyser::Buffer buffer2(buffer1);
	analyser::Buffer buffer3(buffer1);
	analyser::Buffer buffer4(buffer2);
}

void test_assign_nonempty() {
	analyser::Buffer buffer1(100);
	analyser::Buffer buffer2(200);
	buffer1 = buffer2;
}

void test_clone() {
	analyser::Buffer buffer1(100);
	analyser::Buffer buffer2 = buffer1.clone();
}

int main() {
	test_simple();
	test_assignment_operator();
	test_copy_constructor();
	test_assign_nonempty();
	test_clone();
}
