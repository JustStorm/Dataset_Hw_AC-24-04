#include "FilterDataset.h"
#include "utils.h"
#include "SeverityBucketSort.h"

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

    SoAdataset SoA(fname, 100000);
    AoSdataset AoS(fname, 100000);

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
    for (int i = 0; i < 99999; i++) {
        if (AoS.get_severity(i) > AoS.get_severity(i + 1)) flag = false;
        //cout << AoS.get_severity(i);
    }
    cout << ((flag) ? "Bucket sorting finished correct\n" : "Bucket sorting is incorrect\n");
    return 0;


}
