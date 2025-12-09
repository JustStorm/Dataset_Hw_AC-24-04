#pragma once
#include "FilterDataset.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>



void parse_spaces(std::ifstream& input, std::stringstream& output);

template<typename func,typename dataset>
void timeit(func function, dataset& list) {
	using clock = std::chrono::high_resolution_clock;

	auto start = clock::now();
	function(list);
	auto end = clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << duration.count() << " microseconds\n";
}
void ComparisonTime(SoAdataset& SoA, AoSdataset& AoS);