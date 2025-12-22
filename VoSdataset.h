#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <utility>
#include "Struct.h"


class VoSdataset {
	int size;
	std::vector<accident> entry;

	void alloc_data();
public:
	VoSdataset(std::string fname, int size);
	int get_size();
	void swapitems(int index1, int index2);

	bool read_cached(std::string fname, int expected_size);
	void write_cached(std::string fname);

	void insert();
	void delete_item(int index);

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