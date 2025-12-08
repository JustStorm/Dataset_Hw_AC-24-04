#pragma once
#include "SoAdataset.h"
#include "AoSdataset.h"


using namespace std;

void some_func() {
    int c = 0;
    for (int i = 0; i < 5000000; i++) {
        c += i * (c / 7);
    }
}

int main()
{

    //// ПЕРЕД ТЕМ, КАК СЧИТЫВАТЬ БОЛЬШОЕ КОЛИЧЕСТВО, УБЕДИТЕСЬ ЧТО ФАЙЛ ДОСТАТОЧНО БОЛЬШОЙ
    //const char fname[] = "./dataset/Accidents_full.csv";
    //const char fname[] = "./dataset/Accidents_100k.csv";
    //const char fname[] = "./dataset/Accidents_50k.csv";
    const char fname[] = "./dataset/Accidents_10k.csv";
    //const char fname[] = "./dataset/Accidents_1k.csv";
    //const char fname[] = "./dataset/output.csv";

    SoAdataset SoA(fname, 10000);
    AoSdataset AoS(fname, 10000);

    cout << "Data access example:\n";
    cout << SoA.get_weather_condition(950) << '\n';
    cout << AoS.get_weather_condition(950) << '\n';


    cout << "Swap test:\n";
    cout << SoA.get_temperature(700) << '\n';
    cout << SoA.get_temperature(800) << '\n';
    cout << "Swapped!\n";
    SoA.swapitems(700, 800);
    cout << SoA.get_temperature(700) << '\n';
    cout << SoA.get_temperature(800) << '\n';


    return 0;


}
