#include "utils.h"
#include "FilterDataset.h"

using namespace std;


void parse_spaces(ifstream& input, stringstream& output) {
	string value{ };
	char c;
	int cnt = 0;
	while (input.get(c)) {
		switch (c) {
		case '\n':
		case ',':
			if (value.empty()) {
				value.push_back('0');
			}
			output << value << '\n';
			value.erase();
			if (c == '\n')
				return;
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
	Compare2Datasets("FilterForTemperature", AoS, FilterForTemperature<AoSdataset>, SoA, FilterForTemperature<SoAdataset>);
	Compare2Datasets("SortForTemperature", AoS, SortForTemperature<AoSdataset>, SoA, SortForTemperature<SoAdataset>);
	Compare2Datasets("SearchForTemperature", AoS, SearchForTemperature<AoSdataset>, SoA, SearchForTemperature<SoAdataset>);
	Compare2Datasets("FilterForTemperatureAndWindspeed", AoS, FilterForTemperatureAndWindspeed<AoSdataset>, SoA, FilterForTemperatureAndWindspeed<SoAdataset>);
	Compare2Datasets("SearchForTemperatureAndWindspeed", AoS, SearchForTemperatureAndWindspeed<AoSdataset>, SoA, SearchForTemperatureAndWindspeed<SoAdataset>);
}
