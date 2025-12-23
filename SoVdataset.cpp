#include "SoVdataset.h"
#include "utils.h"

using namespace std;

void SoVdataset::alloc_data() {
	id.resize(size);
	severity.resize(size);
	city.resize(size);
	county.resize(size);
	state.resize(size);
	temperature.resize(size);
	wind_temperature.resize(size);
	humidity_percent.resize(size);
	pressure.resize(size);
	wind_speed.resize(size);
	weather_condition.resize(size);
}

void SoVdataset::swapitems(int index1, int index2) {
	std::swap(id[index1], id[index2]);
	std::swap(severity[index1], severity[index2]);
	std::swap(city[index1], city[index2]);
	std::swap(county[index1], county[index2]);
	std::swap(state[index1], state[index2]);
	std::swap(temperature[index1], temperature[index2]);
	std::swap(wind_temperature[index1], wind_temperature[index2]);
	std::swap(humidity_percent[index1], humidity_percent[index2]);
	std::swap(pressure[index1], pressure[index2]);
	std::swap(wind_speed[index1], wind_speed[index2]);
	std::swap(weather_condition[index1], weather_condition[index2]);
}

int SoVdataset::get_size() {
	return size;
}

const int SoVdataset::get_id(int index) {
	return id[index];
}
const short int SoVdataset::get_severity(int index) {
	return severity[index];
}
const char* SoVdataset::get_city(int index) {
	return city[index].data();
}
const char* SoVdataset::get_county(int index) {
	return county[index].data();
}
const char* SoVdataset::get_state(int index) {
	return state[index].data();
}
const float SoVdataset::get_temperature(int index) {
	return temperature[index];
}
const float SoVdataset::get_wind_temperature(int index) {
	return wind_temperature[index];
}
const float SoVdataset::get_humidity_percent(int index) {
	return humidity_percent[index];
}
const float SoVdataset::get_pressure(int index) {
	return pressure[index];
}
const float SoVdataset::get_wind_speed(int index) {
	return wind_speed[index];
}
const char* SoVdataset::get_weather_condition(int index) {
	return weather_condition[index].data();
}

bool SoVdataset::read_cached(std::string cached_fname, int expected_size) {
	ifstream file_cached(cached_fname, ios::binary);
	if (!file_cached.is_open()) {
		std::cout << "Could not find cached version! Proceeding to parsing...\n";
		return false;
	}

	std::cout << "Found a processed version SoV! Loading processed...\n";

	file_cached.read(reinterpret_cast<char*>(&size), sizeof(size));
	if (size != expected_size) {
		cout << "Processed file has different size. Aborting, parsing...\n";
		return false;
	}

	alloc_data();
	file_cached.read(reinterpret_cast<char*>(id.data()), sizeof(int) * size);
	file_cached.read(reinterpret_cast<char*>(severity.data()), sizeof(short int) * size);
	file_cached.read(reinterpret_cast<char*>(city.data()), sizeof(char) * size * 20);
	file_cached.read(reinterpret_cast<char*>(county.data()), sizeof(char) * size * 20);
	file_cached.read(reinterpret_cast<char*>(state.data()), sizeof(char) * size * 3);
	file_cached.read(reinterpret_cast<char*>(temperature.data()), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(wind_temperature.data()), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(humidity_percent.data()), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(pressure.data()), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(wind_speed.data()), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(weather_condition.data()), sizeof(char) * size * 60);

	file_cached.close();
	return true;
}

void SoVdataset::write_cached(std::string cached_fname) {
	ofstream cached(cached_fname, ios::binary);
	if (!cached.is_open()) {
		cout << "Failed to open file '" << cached_fname << "', can not save cache!";
	}
	cached.write(reinterpret_cast<char*>(&size), sizeof(size));

	cached.write(reinterpret_cast<char*>(id.data()), sizeof(int) * size);
	cached.write(reinterpret_cast<char*>(severity.data()), sizeof(short int) * size);
	cached.write(reinterpret_cast<char*>(city.data()), sizeof(char) * size * 20);
	cached.write(reinterpret_cast<char*>(county.data()), sizeof(char) * size * 20);
	cached.write(reinterpret_cast<char*>(state.data()), sizeof(char) * size * 3);
	cached.write(reinterpret_cast<char*>(temperature.data()), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(wind_temperature.data()), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(humidity_percent.data()), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(pressure.data()), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(wind_speed.data()), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(weather_condition.data()), sizeof(char) * size * 60);

	cached.close();
	cout << "Saved processed to cache successfully!\n";
}

void SoVdataset::insert(int index) {
	int count = size / 2;

    std::array<char, 20> new_city{};
    std::memcpy(new_city.data(), "new_city\0", 9);

    std::array<char, 20> new_county{};
    std::memcpy(new_county.data(), "new_county\0", 11);

    std::array<char, 3> new_state{};
    std::memcpy(new_state.data(), "NS\0", 3);

    std::array<char, 60> new_weather{};
    std::memcpy(new_weather.data(), "new_weather\0", 12);
	for (int i = 0; i < count; i++){
		id.insert(id.begin() + index, 999999);
		severity.insert(severity.begin() + index, static_cast<short int>(2));
		temperature.insert(temperature.begin() + index, 50.);
		wind_temperature.insert(wind_temperature.begin() + index, 45.);
		humidity_percent.insert(humidity_percent.begin() + index, 70.);
		pressure.insert(pressure.begin() + index, 30.);
		wind_speed.insert(wind_speed.begin() + index, 10.);



		city.insert(city.begin() + index, new_city);
		county.insert(county.begin() + index, new_county);
		state.insert(state.begin() + index, new_state);
		weather_condition.insert(weather_condition.begin() + index, new_weather);
 
	}
	size += count; 

}

void SoVdataset::delete_item(int index) {
	id.erase(id.begin() + index);
	severity.erase(severity.begin() + index);
	temperature.erase(temperature.begin() + index);
	wind_temperature.erase(wind_temperature.begin() + index);
	humidity_percent.erase(humidity_percent.begin() + index);
	pressure.erase(pressure.begin() + index);
	wind_speed.erase(wind_speed.begin() + index);

	city.erase(city.begin() + index);
	county.erase(county.begin() + index);
	state.erase(state.begin() + index);
	weather_condition.erase(weather_condition.begin() + index);

	size--;  
}

SoVdataset::SoVdataset(string fname, int sz) {
	string cached_fname = fname + ".cachedSOV";
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
		separated >> id[i];
		separated >> severity[i];
		separated >> city[i].data();
		separated >> county[i].data();
		separated >> state[i].data();
		separated >> temperature[i];
		separated >> wind_temperature[i];
		separated >> humidity_percent[i];
		separated >> pressure[i];
		separated >> wind_speed[i];
		separated >> weather_condition[i].data();

		if (separated.fail()) {
			std::cout << "Descriptor invalidated at index " << i << ", exiting.\n";
			break;
		}
	}

	auto parse_end = clock::now();
	std::cout << "Parsing took: " << std::chrono::duration_cast<std::chrono::milliseconds>(parse_end - parse_start).count() << " ms.\n";
	write_cached(cached_fname);
}