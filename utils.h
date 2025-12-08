#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>



void parse_spaces(std::ifstream& input, std::stringstream& output);

template<typename func>
void timeit(func function) {
	using clock = std::chrono::high_resolution_clock;

	auto start = clock::now();
	function();
	auto end = clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Took " << duration.count() << "ms\n";
}