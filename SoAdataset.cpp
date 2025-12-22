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

void SoAdataset::delete_item(int index) {
	for (int i = index + 1; i < size; i++) {
		id[i - 1] = id[i];
		severity[i - 1] = severity[i];
		strncpy(city[i - 1], city[i], 19); city[i - 1][19] = '\0';
		strncpy(county[i - 1], county[i], 19); county[i - 1][19] = '\0';
		strncpy(state[i - 1], state[i], 2); state[i - 1][2] = '\0';
		temperature[i - 1] = temperature[i];
		wind_temperature[i - 1] = wind_temperature[i];
		humidity_percent[i - 1] = humidity_percent[i];
		pressure[i - 1] = pressure[i];
		wind_speed[i - 1] = wind_speed[i];
		strncpy(weather_condition[i - 1], weather_condition[i], 14); weather_condition[i - 1][14] = '\0';
	}
	size--;
}

void SoAdataset::insert() {
	int index = size / 2;
	int count = size / 2;

    int new_size = size + count;

    int* new_id = new int[new_size];
    short int* new_severity = new short int[new_size];
    char (*new_city)[20] = new char[new_size][20];
    char (*new_county)[20] = new char[new_size][20];
    char (*new_state)[3] = new char[new_size][3];
    float* new_temperature = new float[new_size];
    float* new_wind_temperature = new float[new_size];
    float* new_humidity_percent = new float[new_size];
    float* new_pressure = new float[new_size];
    float* new_wind_speed = new float[new_size];
    char (*new_weather_condition)[15] = new char[new_size][15];

    for (int i = 0; i < index; ++i) {
		new_id[i] = id[i];
		new_severity[i] = severity[i];
		strncpy(new_city[i], city[i], 19); new_city[i][19] = '\0';
		strncpy(new_county[i], county[i], 19); new_county[i][19] = '\0';
		strncpy(new_state[i], state[i], 2); new_state[i][2] = '\0';
		new_temperature[i] = temperature[i];
		new_wind_temperature[i] = wind_temperature[i];
		new_humidity_percent[i] = humidity_percent[i];
		new_pressure[i] = pressure[i];
		new_wind_speed[i] = wind_speed[i];
		strncpy(new_weather_condition[i], weather_condition[i], 14); new_weather_condition[i][14] = '\0';
	}

    for (int i = 0; i < count; ++i) {
        int pos = index + i;
        new_id[pos] = count; 
        new_severity[pos] = static_cast<short int>(count);
        strncpy(new_city[pos], "new_city", 19); new_city[pos][19] = '\0';
        strncpy(new_county[pos], "new_county", 19); new_county[pos][19] = '\0';
        strncpy(new_state[pos], "ns", 2); new_state[pos][2] = '\0'; 
        new_temperature[pos] = static_cast<float>(count);
        new_wind_temperature[pos] = static_cast<float>(count);
        new_humidity_percent[pos] = static_cast<float>(count);
        new_pressure[pos] = static_cast<float>(count);
        new_wind_speed[pos] = static_cast<float>(count);
        strncpy(new_weather_condition[pos], "new_weather", 14); new_weather_condition[pos][14] = '\0';
    }

	for (int i = index; i < size; ++i) {
		int pos = index + i;
		new_id[pos] = id[i];
		new_severity[pos] = severity[i];
		strncpy(new_city[pos], city[i], 19); new_city[pos][19] = '\0';
		strncpy(new_county[pos], county[i], 19); new_county[pos][19] = '\0';
		strncpy(new_state[pos], state[i], 2); new_state[pos][2] = '\0';
		new_temperature[pos] = temperature[i];
		new_wind_temperature[pos] = wind_temperature[i];
		new_humidity_percent[pos] = humidity_percent[i];
		new_pressure[pos] = pressure[i];
		new_wind_speed[pos] = wind_speed[i];
		strncpy(new_weather_condition[pos], weather_condition[i], 14); new_weather_condition[pos][14] = '\0';
	}
    delete[] id; id = new_id;
    delete[] severity; severity = new_severity;
    delete[] city; city = reinterpret_cast<char (*)[20]>(new_city);
    delete[] county; county = reinterpret_cast<char (*)[20]>(new_county);
    delete[] state; state = reinterpret_cast<char (*)[3]>(new_state);
    delete[] temperature; temperature = new_temperature;
    delete[] wind_temperature; wind_temperature = new_wind_temperature;
    delete[] humidity_percent; humidity_percent = new_humidity_percent;
    delete[] pressure; pressure = new_pressure;
    delete[] wind_speed; wind_speed = new_wind_speed;
    delete[] weather_condition; weather_condition = reinterpret_cast<char (*)[15]>(new_weather_condition);

    size = new_size;
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