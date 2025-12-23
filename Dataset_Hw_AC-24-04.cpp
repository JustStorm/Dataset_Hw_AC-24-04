#include "FilterDataset.h"
#include "utils.h"
#include "SeverityBucketSort.h"
#include "MergeSort.h"
#include "substring_searcher.h"

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
    //DoSdataset DoS(fname, 50000);
    UMoSdataset UMoS(fname, 50000);

    cout << "\n\n";

    // ==================== ТЕСТ ПОИСКА ПОДСТРОКИ ====================
    cout << "=== Testing REGISTER-SENSITIVE substring search algorithm ===" << endl;
    cout << "\nSearching for 'rain' in weather_condition (SoA):" << endl;

    auto results = countSubstringOccurrences(
        SoA,
        [](SoAdataset& ds, int idx) -> const char* {
            return ds.get_weather_condition(idx);
        },
        "rain" 
    );

    int total_rain = 0;
    int records_with_rain = 0;
    for (int i = 0; i < results.size(); i++) {
        total_rain += results[i];
        if (results[i] > 0) {
            records_with_rain++;
        }
    }

    cout << "Total 'rain' occurrences: " << total_rain << endl;
    cout << "Records containing 'rain': " << records_with_rain << endl;
    cout << "Total records processed: " << SoA.get_size() << endl;

    ComparisonTime(SoA, AoS);
    
    // EXAMPLE COMPARE5
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
    check_sort("BucketSort", AoS, [&AoS](int i) {return AoS.get_severity(i); });

    // MergeSort
    merge_sort(SoA, 10000, [&](int i) { return SoA.get_temperature(i); });
    check_sort("MergeSort", SoA, [&SoA](int i) { return SoA.get_temperature(i); });
    
    
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
    //OperationSpeed(DoS);
    cout << "\n\nOperation speed of unordered map of structures" << endl;
    OperationSpeedMaps(UMoS);

    return 0;
}
