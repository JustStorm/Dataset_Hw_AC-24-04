#include "utils.h"

using namespace std;


void parse_spaces(ifstream& input, stringstream& output) {
	string value{ 10 };
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

void ComparisonTime(SoAdataset& SoA, AoSdataset& AoS) {
	std::cout << "Test 1 SoA" << std::endl;
	timeit(FilterForTemperature<SoAdataset>, SoA);
	std::cout << "Test 1 AoS" << std::endl;
	timeit(FilterForTemperature<AoSdataset>, AoS);
	std::cout << "Test 2 SoA" << std::endl;
	timeit(SortForTemperature<SoAdataset>, SoA);
	std::cout << "Test 2 AoS" << std::endl;
	timeit(SortForTemperature<AoSdataset>, AoS);
	std::cout << "Test 3 SoA" << std::endl;
	timeit(SearchForTemperature<SoAdataset>, SoA);
	std::cout << "Test 3 AoS" << std::endl;
	timeit(SearchForTemperature<AoSdataset>, AoS);
	std::cout << "Test 4 SoA" << std::endl;
	timeit(FilterForTemperatureAndWindspeed<SoAdataset>, SoA);
	std::cout << "Test 4 AoS" << std::endl;
	timeit(FilterForTemperatureAndWindspeed<AoSdataset>, AoS);
	std::cout << "Test 5 SoA" << std::endl;
	timeit(SearchForTemperatureAndWindspeed<SoAdataset>, SoA);
	std::cout << "Test 5 AoS" << std::endl;
	timeit(SearchForTemperatureAndWindspeed<AoSdataset>, AoS);

}