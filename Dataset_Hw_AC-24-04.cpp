#pragma once
#include "read_dataset.h"


using namespace std;

void some_func() {
    int c = 0;
    for (int i = 0; i < 5000000; i++) {
        c += i * (c / 7);
    }
}

int main()
{
    //const char fname[] = "./dataset/output.csv";
    const char fname[] = "./dataset/output.csv";

    accident *AoS = new accident[10000];
    dataset *SoA = new dataset;

    read_SoA(fname, *SoA, 10000);
    read_AoS(fname, AoS, 10000);

    timeit(some_func);
    cout << SoA->weather_condition[13] << '\n';
    cout << AoS[13].weather_condition << '\n';

    delete[] AoS;
    delete SoA;
    return 0;


}
