#pragma once
#include "FilterDataset.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>



void parse_spaces(std::ifstream& input, std::stringstream& output);

void ComparisonTime(SoAdataset& SoA, AoSdataset& AoS);

template<typename func,typename dataset>
void timeit(func function, dataset& list) {
	using clock = std::chrono::high_resolution_clock;

	auto start = clock::now();
	function(list);
	auto end = clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << duration.count() << " microseconds\n";
}

template <typename dataset>
void OperationSpeed(dataset& DS) {
	std::cout << "Deleting one eighth of the elements" << std::endl;
	timeit(DeleteItems<dataset>, DS);
	std::cout << "Sorting elements" << std::endl;
	timeit(SortByTemperature<dataset>, DS);
	std::cout << "Counting elements passing the filter (read speed)" << std::endl;
	timeit(SearchByTemperature<dataset>, DS);
	std::cout << "Adding size elements" << std::endl;
	timeit(InsertItems<dataset>, DS);
}

template <typename dataset>
void OperationSpeedMaps(dataset& DS) {
	std::cout << "Deleting one eighth of the elements" << std::endl;
	timeit(DeleteItems<dataset>, DS);
	std::cout << "Counting elements passing the filter (read speed)" << std::endl;
	timeit(SearchForTemperature<dataset>, DS);
	std::cout << "Adding size elements" << std::endl;
	timeit(InsertItems<dataset>, DS);
}