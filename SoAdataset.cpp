#include "SoAdataset.h"
#include "utils.h"

using namespace std;


SoAdataset::~SoAdataset() {
	free_data();
}
int SoAdataset::get_size() {
	return size;
}

void SoAdataset::swapitems(int index1, int index2) {
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

void SoAdataset::alloc_data() {
	free_data();
	id = new int[size];
	severity = new short int[size];
	city = new char[size][20];
	county = new char[size][20];
	state = new char[size][3];
	temperature = new float[size];
	wind_temperature = new float[size];
	humidity_percent = new float[size];
	pressure = new float[size];
	wind_speed = new float[size];
	weather_condition = new char[size][15];
}

void SoAdataset::free_data() {
	delete[] id;
	delete[] severity;
	delete[] city;
	delete[] county;
	delete[] state;
	delete[] temperature;
	delete[] wind_temperature;
	delete[] humidity_percent;
	delete[] pressure;
	delete[] wind_speed;
	delete[] weather_condition;

	id = nullptr;
	severity = nullptr;
	city = nullptr;
	county = nullptr;
	state = nullptr;
	temperature = nullptr;
	wind_temperature = nullptr;
	humidity_percent = nullptr;
	pressure = nullptr;
	wind_speed = nullptr;
	weather_condition = nullptr;
}

const int SoAdataset::get_id(int index) {
	return id[index];
}
const short int SoAdataset::get_severity(int index) {
	return severity[index];
}
const char* SoAdataset::get_city(int index) {
	return city[index];
}
const char* SoAdataset::get_county(int index) {
	return county[index];
}
const char* SoAdataset::get_state(int index) {
	return state[index];
}
const float SoAdataset::get_temperature(int index) {
	return temperature[index];
}
const float SoAdataset::get_wind_temperature(int index) {
	return wind_temperature[index];
}
const float SoAdataset::get_humidity_percent(int index) {
	return humidity_percent[index];
}
const float SoAdataset::get_pressure(int index) {
	return pressure[index];
}
const float SoAdataset::get_wind_speed(int index) {
	return wind_speed[index];
}
const char* SoAdataset::get_weather_condition(int index) {
	return weather_condition[index];
}






bool SoAdataset::read_cached(std::string cached_fname, int expected_size) {
	ifstream file_cached(cached_fname, ios::binary);
	if (!file_cached.is_open()) {
		std::cout << "Could not find cached version! Proceeding to parsing...\n";
		return false;
	}

	std::cout << "Found a processed version SoA! Loading processed...\n";

	file_cached.read(reinterpret_cast<char*>(&size), sizeof(size));
	if (size != expected_size) {
		cout << "Processed file has different size. Aborting, parsing...\n";
		return false;
	}

	alloc_data();
	file_cached.read(reinterpret_cast<char*>(id), sizeof(int) * size);
	file_cached.read(reinterpret_cast<char*>(severity), sizeof(short int) * size);
	file_cached.read(reinterpret_cast<char*>(city), sizeof(char) * size * 20);
	file_cached.read(reinterpret_cast<char*>(county), sizeof(char) * size * 20);
	file_cached.read(reinterpret_cast<char*>(state), sizeof(char) * size * 3);
	file_cached.read(reinterpret_cast<char*>(temperature), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(wind_temperature), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(humidity_percent), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(pressure), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(wind_speed), sizeof(float) * size);
	file_cached.read(reinterpret_cast<char*>(weather_condition), sizeof(char) * size * 15);

	file_cached.close();
	return true;
}

void SoAdataset::write_cached(std::string cached_fname) {
	ofstream cached(cached_fname, ios::binary);
	if (!cached.is_open()) {
		cout << "Failed to open file '" << cached_fname << "', can not save cache!";
	}
	cached.write(reinterpret_cast<char*>(&size), sizeof(size));

	cached.write(reinterpret_cast<char*>(id), sizeof(int) * size);
	cached.write(reinterpret_cast<char*>(severity), sizeof(short int) * size);
	cached.write(reinterpret_cast<char*>(city), sizeof(char) * size * 20);
	cached.write(reinterpret_cast<char*>(county), sizeof(char) * size * 20);
	cached.write(reinterpret_cast<char*>(state), sizeof(char) * size * 3);
	cached.write(reinterpret_cast<char*>(temperature), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(wind_temperature), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(humidity_percent), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(pressure), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(wind_speed), sizeof(float) * size);
	cached.write(reinterpret_cast<char*>(weather_condition), sizeof(char) * size * 15);

	cached.close();
	cout << "Saved processed to cache successfully!\n";
}

SoAdataset::SoAdataset(string fname, int sz) {
	string cached_fname = fname + ".cachedSOA";
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
	separated.width(100);

	for (int i = 0; i < size; i++) {
		parse_spaces(file, separated);
		separated >> id[i];
		separated >> severity[i];
		separated >> city[i];
		separated >> county[i];
		separated >> state[i];
		separated >> temperature[i];
		separated >> wind_temperature[i];
		separated >> humidity_percent[i];
		separated >> pressure[i];
		separated >> wind_speed[i];
		separated >> weather_condition[i];;

		if (separated.fail()) {
			std::cout << "Descriptor invalidated at index " << i << ", exiting.\n";
			break;
		}
	}

	auto parse_end = clock::now();
	std::cout << "Parsing took: " << std::chrono::duration_cast<std::chrono::milliseconds>(parse_end - parse_start).count() << " ms.\n";
	write_cached(cached_fname);
}