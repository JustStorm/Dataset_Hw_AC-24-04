#pragma once
#include "FilterDataset.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <array>
#include <vector>

template<typename dataset, typename getter>
void check_sort(const char fname[], dataset &data, getter get) {
	bool flag = true;
	for (int i = 0; i < 9999; i++) {
		if (get(i) > get(i + 1)) {
			flag = false;
		}
	}
	if (flag) {
		std::cout << fname << " finished correctly\n";
	}
	else {
		std::cout << fname << " finished incorrectly\n";
	};
	return;
}
void parse_spaces(std::ifstream& input, std::stringstream& output);

template<typename func, typename dataset>
int timeit(func function, dataset& data, int size) {
	using clock = std::chrono::high_resolution_clock;
	const int tries = 10;
	std::array<int, tries> time;

	for (int N = 0; N < tries; N++) {
		auto start = clock::now();
		function(data, size);
		auto end = clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		time[N] = duration.count();

	}
	std::sort(time.begin(), time.end());
	int median = time[tries / 2];
	//std::cout << median << " microseconds\n";
	return median;
};




#define MEASURE(DATA, IDX) \
{ \
    time.fill(0); \
    for (int N = 0; N < tries; ++N) { \
        auto start = clock::now(); \
        function(DATA, size); \
        auto end = clock::now(); \
        time[N] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); \
    } \
    std::sort(time.begin(), time.end()); \
    EXEC_TIME[IDX].push_back(time[tries / 2]); \
}



template<typename func1, typename func2, typename dataset1, typename dataset2>
void Compare2Datasets(const char funcname[], dataset1& data1, func1 function1, dataset2& data2, func2 function2, int inputsize = -1) {
	if (inputsize == -1) {
		inputsize = data1.get_size();
	}
	using clock = std::chrono::high_resolution_clock;
	const int SIZES[] = {10000, 50000, 100000, 250000, 500000, 1000000, 3000000, 7000000};
	const int DATA_COUNT = 2;

	std::array<std::vector<int>, DATA_COUNT> EXEC_TIME{};
	for (int size : SIZES) {
		if (inputsize >= size) {
			EXEC_TIME[0].push_back(
				timeit(function1, data1, size)
			);
			EXEC_TIME[1].push_back(
				timeit(function2, data2, size)
			);

		}
	}

	std::string path = "./performance/";
	path += funcname;
	path += ".dat";
	std::ofstream file(path);

	std::cout << "Function " << funcname << '\n';
	file << funcname << '\n';

	file << "Size ";
	for (int somesize : SIZES) {
		if (somesize > inputsize) continue;
		file << somesize << ' ';
	}
	file << '\n';

	int rows = EXEC_TIME[0].size();
	for (int line = 0; line < DATA_COUNT; line++) {
		std::cout << "Dataset" << line + 1 << ' ';
		file      << "Dataset" << line + 1 << ' ';
		for (int i = 0; i < rows; i++) {
			std::cout << EXEC_TIME[line][i] << ' ';
			file      << EXEC_TIME[line][i] << ' ';
		}
		std::cout << '\n';
		file      << '\n';
	}
	file.close();
	std::cout << "Saved to '" << path << "'\n\n";
}

template <typename dataset>
void OperationSpeed(dataset& DS) {
	int sz = DS.get_size();
	std::cout << "Filter for one feature" << std::endl;
	std::cout << timeit(FilterForTemperature<dataset>, DS, sz) << std::endl;
	std::cout << "Swaping elements" << std::endl;
	std::cout << timeit(SortForTemperature<dataset>, DS, sz) << std::endl;
	std::cout << "Searching for one feature" << std::endl;
	std::cout << timeit(SearchForTemperature<dataset>, DS, sz) << std::endl;
	std::cout << "Filter for two features" << std::endl;
	std::cout << timeit(FilterForTemperatureAndWindspeed<dataset>, DS, sz) << std::endl;
	std::cout << "Searching for two features" << std::endl;
	std::cout << timeit(SearchForTemperatureAndWindspeed<dataset>, DS, sz) << std::endl;
	std::cout << "Adding size / 2 elements in the beginning" << std::endl;
	std::cout << timeit(InsertItemsInBeginning<dataset>, DS, sz) << std::endl;
	std::cout << "Deleting one third of the elements" << std::endl;
	std::cout << timeit(DeleteItemInBeginning<dataset>, DS, sz) << std::endl;
	std::cout << "Adding size / 2 elements in the middle" << std::endl;
	std::cout << timeit(InsertItemsInMiddle<dataset>, DS, sz) << std::endl;
}

template <typename dataset>
void OperationSpeedMaps(dataset& DS)  {
	int sz = DS.get_size();
	std::cout << "Deleting one third of the elements" << std::endl;
	std::cout << timeit(DeleteItemInBeginning<dataset>, DS, sz) << std::endl;
	std::cout << "Counting elements passing the filter (read speed)" << std::endl;
	std::cout << timeit(SearchForTemperature<dataset>, DS, sz) << std::endl;
	std::cout << "Adding size / 2 elements in the beginning" << std::endl;
	std::cout << timeit(InsertItemsInBeginning<dataset>, DS, sz) << std::endl;
}

template <typename dataset>
void OperationSpeedArrays(dataset& DS) {
	int sz = DS.get_size();
	std::cout << "Filter for one feature" << std::endl;
	std::cout << timeit(FilterForTemperature<dataset>, DS, sz);
	std::cout << "Swaping elements" << std::endl;
	std::cout << timeit(SortForTemperature<dataset>, DS, sz);
	std::cout << "Searching for one feature" << std::endl;
	std::cout << timeit(SearchForTemperature<dataset>, DS, sz);
	std::cout << "Filter for two features" << std::endl;
	std::cout << timeit(FilterForTemperatureAndWindspeed<dataset>, DS, sz);
	std::cout << "Searching for two features" << std::endl;
	std::cout << timeit(SearchForTemperatureAndWindspeed<dataset>, DS, sz);
}

template<typename func1, typename func2, typename func3, typename func4, typename func5, typename dataset1, typename dataset2, typename dataset3, typename dataset4, typename dataset5>
void Compare5Datasets(const char funcname[], dataset1& data1, func1 function1, dataset2& data2, func2 function2, dataset3& data3, func3 function3, dataset4& data4, func4 function4, dataset5& data5, func5 function5, int inputsize = -1) {
	if (inputsize == -1) {
		inputsize = data1.get_size();
	}
	using clock = std::chrono::high_resolution_clock;
	const int SIZES[] = { 10000, 50000, 100000, 250000, 500000, 1000000, 3000000, 7000000 };
	const int DATA_COUNT = 5;

	std::array<std::vector<int>, DATA_COUNT> EXEC_TIME{};
	for (int size : SIZES) {
		if (inputsize >= size) {
			EXEC_TIME[0].push_back(timeit(function1, data1, size));
			EXEC_TIME[1].push_back(timeit(function2, data2, size));
			EXEC_TIME[2].push_back(timeit(function3, data3, size));
			EXEC_TIME[3].push_back(timeit(function4, data4, size));
			EXEC_TIME[4].push_back(timeit(function5, data5, size));

		}
	}

	std::string path = "./performance/";
	path += funcname;
	path += ".dat";
	std::ofstream file(path);

	std::cout << "Function " << funcname << '\n';
	file << funcname << '\n';

	file << "Size ";
	for (int somesize : SIZES) {
		if (somesize > inputsize) continue;
		file << somesize << ' ';
	}
	file << '\n';

	int rows = EXEC_TIME[0].size();
	for (int line = 0; line < DATA_COUNT; line++) {
		std::cout << "Dataset" << line + 1 << ' ';
		file << "Dataset" << line + 1 << ' ';
		for (int i = 0; i < rows; i++) {
			std::cout << EXEC_TIME[line][i] << ' ';
			file << EXEC_TIME[line][i] << ' ';
		}
		std::cout << '\n';
		file << '\n';
	}
	file.close();
	std::cout << "Saved to '" << path << "'\n\n";
}

void ComparisonTime(SoAdataset& SoA, AoSdataset& AoS);
