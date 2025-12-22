#pragma once
#include "SoAdataset.h"
#include "AoSdataset.h"
#include "SoVdataset.h"
#include "VoSdataset.h"
#include "UMoSdataset.h"
#include <iostream>

template <typename dataset>
void DeleteItems(dataset& list) {
	int cnt = list.get_size();
	int count = 0;
	for (int i = cnt / 8; i < cnt / 4; i++) {
		list.delete_item(i);
		count++;
	}
	std::cout << "Deleted " << count << " items\n";
}

template <typename dataset>
void SortForTemperature(dataset& list) {
	for (int i = 0; i < list.get_size()-1; i++) {
		int mn = list.get_temperature(i), ind = i;
		for (int j = i + 1; j < list.get_size(); j++){
			if (mn > list.get_temperature(j)){
				mn = list.get_temperature(j);
				ind = j;
			}
		}
		list.swapitems(i, ind);
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
void InsertItems(dataset& list) {
    list.insert();
}