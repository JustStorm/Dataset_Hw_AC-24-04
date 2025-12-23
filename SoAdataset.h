#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <utility>

class SoAdataset {
	int size;
	int* id = nullptr;
	short int* severity = nullptr;
	char (*city)[20] = nullptr;
	char (*county)[20] = nullptr;
	char (*state)[3] = nullptr;
	float* temperature = nullptr;
	float* wind_temperature = nullptr;
	float* humidity_percent = nullptr;
	float* pressure = nullptr;
	float* wind_speed = nullptr;
	char (*weather_condition)[60] = nullptr;

	void alloc_data();
	void free_data();
public:
	//SoAdataset(int size);
	SoAdataset(std::string fname, int size);
	~SoAdataset();
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