#pragma once
#include <deque>
#include <string>
#include <array>

class SoDdataset {
    int size;
    std::deque<int> id;
    std::deque<short int> severity;
    std::deque<std::array<char, 20>> city;
    std::deque<std::array<char, 20>> county;
    std::deque<std::array<char, 3>> state;
    std::deque<float> temperature;
    std::deque<float> wind_temperature;
    std::deque<float> humidity_percent;
    std::deque<float> pressure;
    std::deque<float> wind_speed;
    std::deque<std::array<char, 60>> weather_condition;
    void alloc_data();
public:
    SoDdataset(std::string fname, int size);

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
