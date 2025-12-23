#include "UMoSdataset.h"
#include "utils.h"
#include <iostream>
using namespace std;


UMoSdataset::UMoSdataset(std::string fname, int sz) {
    string cached_fname = fname + ".cachedUMoS";
    if (read_cached(cached_fname, sz)) return;

    size = sz;


    ifstream file(fname);
    if (!file.is_open()) {
        std::cout << "Couldn't open file! Exiting read func.\n";
        return;
    }

    file.ignore(25565, '\n');

    using clock = std::chrono::high_resolution_clock;
    auto parse_start = clock::now();

    stringstream separated{};
    separated.width(100);

    for (int i = 0; i < size; i++) {
        separated.str("");
        separated.clear();
        parse_spaces(file, separated);
        accident a{};
        separated >> a.id;
        separated >> a.severity;
        separated >> a.city;
        separated >> a.county;
        separated >> a.state;
        separated >> a.temperature;
        separated >> a.wind_temperature;
        separated >> a.humidity_percent;
        separated >> a.pressure;
        separated >> a.wind_speed;
        separated >> a.weather_condition;

        if (separated.fail()) {
            std::cout << "Descriptor invalidated at index " << i << ", exiting.\n";
            break;
        }

        entry[a.id] = a;

    }

    auto parse_end = clock::now();
    std::cout << "Parsing took: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(parse_end - parse_start).count()
        << " ms.\n";

    write_cached(cached_fname);
}

int UMoSdataset::get_size() {
    return size;
}



const int UMoSdataset::get_id(int id) {
    return id;
}

const short int UMoSdataset::get_severity(int index) {
    return entry[index].severity;
}

const char* UMoSdataset::get_city(int index) {
    return entry[index].city;
}

const char* UMoSdataset::get_county(int index) {
    return entry[index].county;
}

const char* UMoSdataset::get_state(int index) {
    return entry[index].state;
}

const float UMoSdataset::get_temperature(int index) {
    return entry[index].temperature;
}

const float UMoSdataset::get_wind_temperature(int index) {
    return entry[index].wind_temperature;
}

const float UMoSdataset::get_humidity_percent(int index) {
    return entry[index].humidity_percent;
}

const float UMoSdataset::get_pressure(int index) {
    return entry[index].pressure;
}

const float UMoSdataset::get_wind_speed(int index) {
    return entry[index].wind_speed;
}

const char* UMoSdataset::get_weather_condition(int index) {
    return entry[index].weather_condition;
}


void UMoSdataset::insert(int index) {
    entry.emplace(new_accident.id + index, new_accident);
    size++;
}

void UMoSdataset::delete_item(int index) {
    entry.erase(index);
    size--;
}

void UMoSdataset::swapitems(int ind1, int ind2) {
    return;
}


bool UMoSdataset::read_cached(std::string cached_fname, int expected_size) {
    ifstream file_cached(cached_fname, ios::binary);
    if (!file_cached.is_open()) {
        cout << "Could not find cached version! Proceeding to parsing...\n";
        return false;
    }

    cout << "Found a processed version UMoS! Loading processed...\n";

    file_cached.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (size != expected_size) {
        cout << "Processed file has different size. Aborting, parsing...\n";
        return false;
    }


    for (int i = 0; i < size; i++) {
        accident a{};
        file_cached.read(reinterpret_cast<char*>(&a), sizeof(accident));
        entry[a.id] = a;
    }

    file_cached.close();
    return true;
}

void UMoSdataset::write_cached(std::string cached_fname) {
    ofstream cached(cached_fname, ios::binary);
    if (!cached.is_open()) {
        cout << "Failed to open file '" << cached_fname << "', can not save cache!";
        return;
    }

    cached.write(reinterpret_cast<char*>(&size), sizeof(size));

    for (auto& [id, a] : entry) {
        cached.write(reinterpret_cast<char*>(&a), sizeof(accident));
    }

    cached.close();
    cout << "Saved processed to cache successfully!\n";
}
