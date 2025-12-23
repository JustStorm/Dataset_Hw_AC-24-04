#include "VoSdataset.h"
#include "utils.h"

using namespace std;




VoSdataset::VoSdataset(std::string fname, int sz) {
	string cached_fname = fname + ".cachedVoS";
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

int VoSdataset::get_size() {
	return size;
}

void VoSdataset::swapitems(int index1, int index2) {
	std::swap(entry[index1], entry[index2]);
}



const int VoSdataset::get_id(int index) {
	return entry[index].id;
}
const short int VoSdataset::get_severity(int index) {
	return entry[index].severity;
}
const char* VoSdataset::get_city(int index) {
	return entry[index].city;
}
const char* VoSdataset::get_county(int index) {
	return entry[index].county;
}
const char* VoSdataset::get_state(int index) {
	return entry[index].state;
}
const float VoSdataset::get_temperature(int index) {
	return entry[index].temperature;
}
const float VoSdataset::get_wind_temperature(int index) {
	return entry[index].wind_temperature;
}
const float VoSdataset::get_humidity_percent(int index) {
	return entry[index].humidity_percent;
}
const float VoSdataset::get_pressure(int index) {
	return entry[index].pressure;
}
const float VoSdataset::get_wind_speed(int index) {
	return entry[index].wind_speed;
}
const char* VoSdataset::get_weather_condition(int index) {
	return entry[index].weather_condition;
}


void VoSdataset::insert(int index) {
	int count = size;
    for (int i = 0; i < count; i++){
    	entry.emplace(entry.begin() + index, new_accident);
	}
    size += count;
}

void VoSdataset::delete_item(int index) {
	entry.erase(entry.begin() + index);
	size--;
}

bool VoSdataset::read_cached(std::string cached_fname, int expected_size) {
	ifstream file_cached(cached_fname, ios::binary);
	if (!file_cached.is_open()) {
		std::cout << "Could not find cached version! Proceeding to parsing...\n";
		return false;
	}

	std::cout << "Found a processed version VoS! Loading processed...\n";

	file_cached.read(reinterpret_cast<char*>(&size), sizeof(size));

	if (size != expected_size) {
		cout << "Processed file has different size. Aborting, parsing...\n";
		return false;
	}
	alloc_data();

	file_cached.read(reinterpret_cast<char*>(entry.data()), sizeof(accident) * size);

	file_cached.close();
	return true;
}

void VoSdataset::write_cached(std::string cached_fname) {
	ofstream cached(cached_fname, ios::binary);
	if (!cached.is_open()) {
		cout << "Failed to open file '" << cached_fname << "', can not save cache!";
	}

	cached.write(reinterpret_cast<char*>(&size), sizeof(size));
	cached.write(reinterpret_cast<char*>(entry.data()), sizeof(accident) * size);

	cached.close();
	cout << "Saved processed to cache successfully!\n";
}

void VoSdataset::alloc_data() {
	entry.resize(size);
}
