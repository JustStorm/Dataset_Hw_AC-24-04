#pragma once
#ifndef AOSDATASET_H
#define AOSDATASET_H

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <utility>

struct accident {
	int id;                  // 0
	char severity;           // 2
	char city[20];           // 12
	char county[20];         // 13
	char state[3];           // 14
	float temperature;       // 20
	float wind_temperature;  // 21
	float humidity_percent;    // 22
	float pressure;          // 23
	float wind_speed;        // 26
	char weather_condition[15];  // 28
};

class AoSdataset {
	int size;
	accident* entry = nullptr;

	void alloc_data();
	void free_data();
public:
	AoSdataset(std::string fname, int size);
	~AoSdataset();
	int get_size();
	void swapitems(int index1, int index2);

	bool read_cached(std::string fname, int expected_size);
	void write_cached(std::string fname);

	const int get_id(int index);
	const short int get_severity(int index);
	const char* get_city(int index);
	const char* get_county(int index);
	const char* get_state(int index);
	const float get_temperature(int index);
	const float get_wind_temperature(int index);
	const float get_humidity_percent(int index);
	const float get_pressure(int index);
	const float get_wind_speed(int index);
	const char* get_weather_condition(int index);
};

#endif