#include "DoSdataset.h"
#include "utils.h"

using namespace std;

const accident new_accident = {
    999999,                  
    2,                       
    "new_city",              
    "new_county",
    "NS",
    50.0,                  
    45.0,                   
    70.0,                   
    30.0,                   
    10.0,                   
    "Inserted"
};


DoSdataset::DoSdataset(std::string fname, int sz) {
	string cached_fname = fname + ".cachedDoS";
	if (read_cached(cached_fname, sz)) return;

	size = sz;
	alloc_data();

	ifstream file(fname);
	if (!file.is_open()) {
		std::cout << "Couldn't open file! Exiting read func.\n";
		return;
	}
	file.ignore(25565, '\n');



	using clock = std::chrono::high_resolution_clock;
	auto parse_start = clock::now();

	stringstream separated{};

	for (int i = 0; i < size; i++) {
		parse_spaces(file, separated);
		separated >> entry[i].id;
		separated >> entry[i].severity;
		separated >> entry[i].city;
		separated >> entry[i].county;
		separated >> entry[i].state;
		separated >> entry[i].temperature;
		separated >> entry[i].wind_temperature;
		separated >> entry[i].humidity_percent;
		separated >> entry[i].pressure;
		separated >> entry[i].wind_speed;
		separated >> entry[i].weather_condition;

		if (separated.fail()) {
			std::cout << "Descriptor invalidated at index " << i << ", exiting.\n";
			break;
		}
	}

	auto parse_end = clock::now();
	std::cout << "Parsing took: " << std::chrono::duration_cast<std::chrono::milliseconds>(parse_end - parse_start).count() << " ms.\n";
	write_cached(cached_fname);
}

int DoSdataset::get_size() {
	return size;
}

void DoSdataset::swapitems(int index1, int index2) {
	std::swap(entry[index1], entry[index2]);
}



const int DoSdataset::get_id(int index) {
	return entry[index].id;
}
const short int DoSdataset::get_severity(int index) {
	return entry[index].severity;
}
const char* DoSdataset::get_city(int index) {
	return entry[index].city;
}
const char* DoSdataset::get_county(int index) {
	return entry[index].county;
}
const char* DoSdataset::get_state(int index) {
	return entry[index].state;
}
const float DoSdataset::get_temperature(int index) {
	return entry[index].temperature;
}
const float DoSdataset::get_wind_temperature(int index) {
	return entry[index].wind_temperature;
}
const float DoSdataset::get_humidity_percent(int index) {
	return entry[index].humidity_percent;
}
const float DoSdataset::get_pressure(int index) {
	return entry[index].pressure;
}
const float DoSdataset::get_wind_speed(int index) {
	return entry[index].wind_speed;
}
const char* DoSdataset::get_weather_condition(int index) {
	return entry[index].weather_condition;
}


void DoSdataset::insert() {
	int index = 0;
	int count = size;
    for (int i = 0; i < count; i++){
    	entry.insert(entry.begin() + index, new_accident);
	}
    size += count;
}

void DoSdataset::delete_item(int index) {
	entry.erase(entry.begin() + index);
	size--;
}

bool DoSdataset::read_cached(std::string cached_fname, int expected_size) {
	ifstream file_cached(cached_fname, ios::binary);
	if (!file_cached.is_open()) {
		std::cout << "Could not find cached version! Proceeding to parsing...\n";
		return false;
	}

	std::cout << "Found a processed version DoS! Loading processed...\n";

	file_cached.read(reinterpret_cast<char*>(&size), sizeof(size));

	if (size != expected_size) {
		cout << "Processed file has different size. Aborting, parsing...\n";
		return false;
	}
	alloc_data();

	file_cached.read(reinterpret_cast<char*>(&entry), sizeof(accident) * size);

	file_cached.close();
	return true;
}

void DoSdataset::write_cached(std::string cached_fname) {
	ofstream cached(cached_fname, ios::binary);
	if (!cached.is_open()) {
		cout << "Failed to open file '" << cached_fname << "', can not save cache!";
	}

	cached.write(reinterpret_cast<char*>(&size), sizeof(size));
	cached.write(reinterpret_cast<char*>(&entry), sizeof(accident) * size);

	cached.close();
	cout << "Saved processed to cache successfully!\n";
}

void DoSdataset::alloc_data() {
	entry.resize(size);
}
