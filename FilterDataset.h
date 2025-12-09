#pragma once
#include "SoAdataset.h"
#include "AoSdataset.h"


template <typename dataset>

void FilterForTemperature(dataset& list) {
	int cnt = 0;
	for (int i = 0; i < list.get_size(); i++) {
		if (list.get_temperature(i) > 36.0)
			cnt++;
	}
}

template <typename dataset>
void SortForTemperature(dataset& list) {
	for (int i = 0; i < list.get_size()-1; i++) {
		if (list.get_temperature(i) > list.get_temperature(i + 1))
			list.swapitems(i, i + 1);
	}
}

template <typename dataset>
void SearchForTemperature(dataset& list) {
	int cnt = 0;
	for (int i = 0; i < list.get_size(); i++) {
		if (list.get_temperature(i) == 36.0)
			cnt++;
	}
}

template <typename dataset>
void FilterForTemperatureAndWindspeed(dataset& list) {
	int cnt = 0;
	for (int i = 0; i < list.get_size(); i++) {
		if (list.get_temperature(i) > 36.0 && list.get_wind_speed(i) >= 3.5)
			cnt++;
	}
}

template <typename dataset>
void SearchForTemperatureAndWindspeed(dataset& list) {
	int cnt = 0;
	for (int i = 0; i < list.get_size(); i++) {
		if (list.get_temperature(i) == 36.0 && list.get_wind_speed(i) == 3.5)
			cnt++;
	}
}