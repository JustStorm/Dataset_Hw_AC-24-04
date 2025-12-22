#include "utils.h"

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

