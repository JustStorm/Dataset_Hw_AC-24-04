#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <array>

class SoVdataset {
    int size;
    std::vector<int> id;
    std::vector<short int> severity;
    std::vector<std::array<char, 20>> city;
    std::vector<std::array<char, 20>> county;
    std::vector<std::array<char, 3>> state;
    std::vector<float> temperature;
    std::vector<float> wind_temperature;
    std::vector<float> humidity_percent;
    std::vector<float> pressure;
    std::vector<float> wind_speed;
    std::vector<std::array<char, 60>> weather_condition;
    void alloc_data();
public:
    SoVdataset(std::string fname, int size);

    bool read_cached(std::string fname, int expected_size);
	void write_cached(std::string fname);

    void swapitems(int index1, int index2);

    int get_size();
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

    void insert(int index);
    void delete_item(int index);
};
