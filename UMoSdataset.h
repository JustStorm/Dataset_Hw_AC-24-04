#pragma once

#include "Struct.h"
#include <unordered_map>
#include <string>


class UMoSdataset {
    int size;
    std::unordered_map<int, accident> entry;
public:
    UMoSdataset(std::string fname, int size);
	int get_size();

	bool read_cached(std::string fname, int expected_size);
	void write_cached(std::string fname);

	void insert(int index);
	void delete_item(int index);
	void swapitems(int ind1, int ind2);

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