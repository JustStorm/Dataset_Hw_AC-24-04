#pragma once

struct accident {
	int id;                  // 0
	short int severity;           // 2
	char city[20];           // 12
	char county[20];         // 13
	char state[3];           // 14
	float temperature;       // 20
	float wind_temperature;  // 21
	float humidity_percent;    // 22
	float pressure;          // 23
	float wind_speed;        // 26
	char weather_condition[70];  // 28
};
