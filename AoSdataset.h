#pragma once

#include <string>
#include <cstring>
#include "Struct.h"


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
