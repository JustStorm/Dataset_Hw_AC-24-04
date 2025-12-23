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
	std::cout << "Filter for one feature" << std::endl;
	timeit(FilterForTemperature<dataset>, DS);
	std::cout << "Swaping elements" << std::endl;
	timeit(SortForTemperature<dataset>, DS);
	std::cout << "Searching for one feature" << std::endl;
	timeit(SearchForTemperature<dataset>, DS);
	std::cout << "Filter for two features" << std::endl;
	timeit(FilterForTemperatureAndWindspeed<dataset>, DS);
	std::cout << "Searching for two features" << std::endl;
	timeit(SearchForTemperatureAndWindspeed<dataset>, DS);
	std::cout << "Adding size / 2 elements in the beginning" << std::endl;
	timeit(InsertItemsInBeginning<dataset>, DS);
	std::cout << "Deleting one third of the elements" << std::endl;
	timeit(DeleteItems<dataset>, DS);
	std::cout << "Adding size / 2 elements in the middle" << std::endl;
	timeit(InsertItemsInMiddle<dataset>, DS);
}

template <typename dataset>
void OperationSpeedMaps(dataset& DS)  {
	std::cout << "Deleting one third of the elements" << std::endl;
	timeit(DeleteItems<dataset>, DS);
	std::cout << "Counting elements passing the filter (read speed)" << std::endl;
	timeit(SearchForTemperature<dataset>, DS);
	std::cout << "Adding size / 2 elements in the beginning" << std::endl;
	timeit(InsertItemsInBeginning<dataset>, DS);
}

template <typename dataset>
void OperationSpeedArrays(dataset& DS) {
	std::cout << "Filter for one feature" << std::endl;
	timeit(FilterForTemperature<dataset>, DS);
	std::cout << "Swaping elements" << std::endl;
	timeit(SortForTemperature<dataset>, DS);
	std::cout << "Searching for one feature" << std::endl;
	timeit(SearchForTemperature<dataset>, DS);
	std::cout << "Filter for two features" << std::endl;
	timeit(FilterForTemperatureAndWindspeed<dataset>, DS);
	std::cout << "Searching for two features" << std::endl;
	timeit(SearchForTemperatureAndWindspeed<dataset>, DS);
}