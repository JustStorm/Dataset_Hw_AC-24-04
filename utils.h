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

template <typename dataset1, typename dataset2>
void ComparisonTime(dataset1& SoA, dataset2& AoS) {
	std::cout << "Test 1 SoA" << std::endl;
	timeit(FilterForTemperature<dataset1>, SoA);
	std::cout << "Test 1 AoS" << std::endl;
	timeit(FilterForTemperature<dataset2>, AoS);
	std::cout << "Test 2 SoA" << std::endl;
	timeit(SortForTemperature<dataset1>, SoA);
	std::cout << "Test 2 AoS" << std::endl;
	timeit(SortForTemperature<dataset2>, AoS);
	std::cout << "Test 3 SoA" << std::endl;
	timeit(SearchForTemperature<dataset1>, SoA);
	std::cout << "Test 3 AoS" << std::endl;
	timeit(SearchForTemperature<dataset2>, AoS);
	std::cout << "Test 4 SoA" << std::endl;
	timeit(FilterForTemperatureAndWindspeed<dataset1>, SoA);
	std::cout << "Test 4 AoS" << std::endl;
	timeit(FilterForTemperatureAndWindspeed<dataset2>, AoS);
	std::cout << "Test 5 SoA" << std::endl;
	timeit(SearchForTemperatureAndWindspeed<dataset1>, SoA);
	std::cout << "Test 5 AoS" << std::endl;
	timeit(SearchForTemperatureAndWindspeed<dataset2>, AoS);
	std::cout << "Test 6 SoA" << std::endl;
	timeit(InsertItems<dataset1>, SoA);
	std::cout << "Test 6 SoV" << std::endl;
	timeit(InsertItems<dataset2>, AoS);
}