#include "FilterDataset.h"
#include "utils.h"
#include "SeverityBucketSort.h"
#include "MergeSort.h"

using namespace std;


int main()
{

    //// ПЕРЕД ТЕМ, КАК СЧИТЫВАТЬ БОЛЬШОЕ КОЛИЧЕСТВО, УБЕДИТЕСЬ ЧТО ФАЙЛ ДОСТАТОЧНО БОЛЬШОЙ
    //const char fname[] = "./dataset/Accidents_full.csv";
    //const char fname[] = "./dataset/Accidents_100k.csv";
    //const char fname[] = "./dataset/Accidents_50k.csv";
    const char fname[] = "./dataset/Accidents_100k.csv";
    //const char fname[] = "./dataset/Accidents_1k.csv";
    //const char fname[] = "./dataset/output.csv";

    SoAdataset SoA(fname, 50000);
    SoVdataset SoV(fname, 50000);
    SoDdataset SoD(fname, 50000);
    AoSdataset AoS(fname, 50000);
    VoSdataset VoS(fname, 50000);
    DoSdataset DoS(fname, 50000);
    UMoSdataset UMoS(fname, 50000);

    cout << "\n\n";

    ComparisonTime(SoA, AoS);
    
    /*
    Compare5Datasets("Test5Compare",
        SoA, FilterForTemperature<SoAdataset>,
        AoS, FilterForTemperature<AoSdataset>,
        SoA, FilterForTemperature<SoAdataset>,
        SoA, FilterForTemperature<SoAdataset>,
        AoS, FilterForTemperature<AoSdataset>
    );
    */

    // Severity sorting with bucket sort
    bucket_sort_by_severity(AoS, [&AoS](int i) {return AoS.get_severity(i); });
    bool flag = true;
    for (int i = 0; i < AoS.get_size()-1; i++) {
        if (AoS.get_severity(i) > AoS.get_severity(i + 1)) flag = false;
        //cout << AoS.get_severity(i);
    }
    cout << ((flag) ? "Bucket sorting finished correct\n" : "Bucket sorting is incorrect\n");

    // Вызов merge sort
    merge_sort(SoA, 10000, [&](int i) { return SoA.get_temperature(i); });

    // Проверка корректности
    bool flag_merge = true;
    for (int i = 0; i < 9999; i++) {
        if (SoA.get_temperature(i) > SoA.get_temperature(i + 1)) {
            flag_merge = false;
        }
    }
    cout << ((flag_merge) ? "Merge sorting finished correct\n" : "Merge sorting is incorrect\n");
    
    
    cout << "\n\nOperation speed of structure of arrays" << endl;
    OperationSpeedArrays(SoA);
    cout << "\n\nOperation speed of array of structures" << endl;
    OperationSpeedArrays(AoS);
    cout << "\n\nOperation speed of structure of vectors" << endl;
    OperationSpeed(SoV);
    cout << "\n\nOperation speed of vector of structures" << endl;
    OperationSpeed(VoS);
    cout << "\n\nOperation speed of structure of deques" << endl;
    OperationSpeed(SoD);
    cout << "\n\nOperation speed of deque of structures" << endl;
    OperationSpeed(DoS);
    cout << "\n\nOperation speed of unordered map of structures" << endl;
    OperationSpeedMaps(UMoS);

    return 0;
}
