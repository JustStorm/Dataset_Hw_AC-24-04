#ifndef READ_DATASET_H
#define READ_DATASET_H

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <sstream>


struct accident {
	int id;                  // 0
	char severity;           // 2
	char city[20];           // 12
	char county[20];         // 13
	char state[2];           // 14
	float temperature;       // 20
	float wind_temperature;  // 21
	float humidity_percent;    // 22
	float pressure;          // 23
	float wind_speed;        // 26
	char weather_condition[15];  // 28
};

#define arr_size 10000
struct dataset {
	int id[arr_size];                  // 0
	char severity[arr_size];           // 2
	char city[arr_size][20];           // 12
	char county[arr_size][20];         // 13
	char state[arr_size][2];           // 14
	float temperature[arr_size];       // 20
	float wind_temperature[arr_size];  // 21
	float humidity_percent[arr_size];    // 22
	float pressure[arr_size];          // 23
	float wind_speed[arr_size];        // 26
	char weather_condition[arr_size][15];  // 28
};


void parse_spaces(std::ifstream& input, std::stringstream& output);

void read_SoA(std::string fname, dataset& data, int amount = 10000);
void read_AoS(std::string fname, accident* data, int amount = 10000);

template<typename func>
void timeit(func function) {
	using clock = std::chrono::high_resolution_clock;

	auto start = clock::now();
	function();
	auto end = clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Took " << duration.count() << "ms\n";
}


#endif