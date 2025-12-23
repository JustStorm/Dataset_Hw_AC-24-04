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

    // ==================== ТЕСТИРОВАНИЕ ПОИСКА ПОДСТРОК ====================
    cout << "=== Testing substring search algorithms ===" << endl;

    cout << "\n--- Test 1: Searching for 'rain' in weather_condition ---" << endl;

    auto soa_results = SubstringSearcher::searchInWeatherCondition(SoA, "rain");
    int soa_count = 0;
    for (auto r : soa_results) soa_count += r;
    cout << "SoA: Found 'rain' " << soa_count << " times in weather_condition" << endl;

    auto aos_results = SubstringSearcher::searchInWeatherCondition(AoS, "rain");
    int aos_count = 0;
    for (auto r : aos_results) aos_count += r;
    cout << "AoS: Found 'rain' " << aos_count << " times in weather_condition" << endl;

    auto sov_results = SubstringSearcher::searchInWeatherCondition(SoV, "rain");
    int sov_count = 0;
    for (auto r : sov_results) sov_count += r;
    cout << "SoV: Found 'rain' " << sov_count << " times in weather_condition" << endl;

    auto vos_results = SubstringSearcher::searchInWeatherCondition(VoS, "rain");
    int vos_count = 0;
    for (auto r : vos_results) vos_count += r;
    cout << "VoS: Found 'rain' " << vos_count << " times in weather_condition" << endl;

    auto sod_results = SubstringSearcher::searchInWeatherCondition(SoD, "rain");
    int sod_count = 0;
    for (auto r : sod_results) sod_count += r;
    cout << "SoD: Found 'rain' " << sod_count << " times in weather_condition" << endl;

    if (soa_count == aos_count && aos_count == sov_count &&
        sov_count == vos_count && vos_count == sod_count) {
        cout << "✓ All datasets show consistent results!" << endl;
    }
    else {
        cout << "✗ Inconsistent results detected!" << endl;
    }

    cout << "\n--- Test 2: Searching for 'New' in city field ---" << endl;

    auto city_results = SubstringSearcher::searchInCity(SoA, "New");
    int city_count = 0;
    for (auto r : city_results) city_count += r;
    cout << "SoA: Found 'New' " << city_count << " times in city field" << endl;

 
    cout << "\n--- Test 3: Searching for 'County' in all string fields ---" << endl;

    auto all_results = SubstringSearcher::searchInAllStringFields(SoA, "County");
    int all_count = 0;
    for (auto r : all_results) all_count += r;
    cout << "SoA: Found 'County' " << all_count << " times across all string fields" << endl;

    cout << "\n--- Test 4: Performance measurement of substring search ---" << endl;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 10;
    for (int i = 0; i < iterations; i++) {
        SubstringSearcher::searchInAllStringFields(SoA, "rain");
    }

    auto end = clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "Time for " << iterations << " searches in SoA dataset: "
        << duration << " ms (" << (duration / iterations) << " ms per search)" << endl;

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
