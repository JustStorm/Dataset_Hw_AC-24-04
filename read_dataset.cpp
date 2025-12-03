#pragma once
#include "read_dataset.h"

using namespace std;

void parse_spaces(ifstream &input, stringstream& output) {
	string value{10};
	char c;
	int cnt = 0;
	while (input.get(c)) {
		switch (c) {
		case '\n':
			if (value.empty()) {
				value.push_back('0');
			}
			output << value << '\n';
			value.erase();
			return;
		case ',':
			if (value.empty()) {
				value.push_back('0');
			}
			output << value << '\n';
			value.erase();
			break;
		case ' ':
			value.push_back('_');
			break;
		default:
			value.push_back(c);
		}
	}
}




void read_SoA(string fname, dataset& data, int amount) {
	string cached_fname = fname + ".cachedsoa";
	ifstream file_cached(cached_fname);
	if (file_cached.is_open()) {
		std::cout << "Found a processed version SoA! Loading processed...\n";

		ifstream cached(cached_fname, ios::binary);
		cached.read(reinterpret_cast<char*>(&data), sizeof(data));
		cached.close();
		return;
	}
	else {
		std::cout << "Could not find cached version! Proceeding to parsing...\n";
	}



	ifstream file(fname);
	if (!file.is_open()) {
		std::cout << "Couldn't open file! Exiting read func.\n";
		return;
	}
	file.ignore(25565, '\n');



	using clock = std::chrono::high_resolution_clock;
	auto st2 = clock::now();
	
	stringstream separated{};

	for (int i = 0; i < amount; i++) {
		parse_spaces(file, separated);
		separated >> data.id[i]
			>> data.severity[i]
			>> data.city[i]
			>> data.county[i]
			>> data.state[i]
			>> data.temperature[i]
			>> data.wind_temperature[i]
			>> data.humidity_percent[i]
			>> data.pressure[i]
			>> data.wind_speed[i]
			>> data.weather_condition[i];

		if (separated.fail()) {
			std::cout << "Descriptor invalidated at index " << i << ", exiting.\n";
			break;
		}
	}

	auto end2 = clock::now();
	std::cout << "Parsing took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - st2).count() << " ms.\n";
	ofstream cached(cached_fname, ios::binary);
	cached.write(reinterpret_cast<char*>(&data), sizeof(data));
	cached.close();
	cout << "Saved processed to cache successfully!\n";
}





void read_AoS(string fname, accident* data, int amount) {
	string cached_fname = fname + ".cachedaos";
	ifstream file_cached(cached_fname);
	if (file_cached.is_open()) {
		std::cout << "Found a processed version AoS! Loading processed...\n";

		ifstream cached(cached_fname, ios::binary);
		cached.read(reinterpret_cast<char*>(data), sizeof(data) * 10000);
		cached.close();
		return;
	}
	else {
		std::cout << "Could not find cached version! Proceeding to parsing...\n";
	}



	ifstream file(fname);
	if (!file.is_open()) {
		std::cout << "Couldn't open file! Exiting read func.\n";
		return;
	}
	file.ignore(25565, '\n');



	using clock = std::chrono::high_resolution_clock;
	auto st2 = clock::now();

	stringstream separated{};

	for (int i = 0; i < amount; i++) {
		parse_spaces(file, separated);
		separated >> data[i].id
			>> data[i].severity
			>> data[i].city
			>> data[i].county
			>> data[i].state
			>> data[i].temperature
			>> data[i].wind_temperature
			>> data[i].humidity_percent
			>> data[i].pressure
			>> data[i].wind_speed
			>> data[i].weather_condition;

		if (separated.fail()) {
			std::cout << "Descriptor invalidated at index " << i << ", exiting.\n";
			break;
		}
	}

	auto end2 = clock::now();
	std::cout << "Parsing took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - st2).count() << " ms.\n";
	ofstream cached(cached_fname, ios::binary);
	cached.write(reinterpret_cast<char*>(data), sizeof(accident) * 10000);
	cached.close();
	cout << "Saved processed to cache successfully!\n";
}
