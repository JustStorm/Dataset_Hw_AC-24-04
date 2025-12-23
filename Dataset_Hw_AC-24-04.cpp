#include "FilterDataset.h"
#include "utils.h"
#include "SeverityBucketSort.h"
#include "MergeSort.h"
#include "Compression.h"  // Добавляем заголовочный файл для алгоритмов сжатия
#include "substring_searcher.h"

using namespace std;


int main()
{

    //// ПЕРЕД ТЕМ, КАК СЧИТЫВАТЬ БОЛЬШОЕ КОЛИЧЕСТВО, УБЕДИТЕСЬ ЧТО ФАЙЛ ДОСТАТОЧНО БОЛЬШОЙ
    const char fname[] = "./dataset/Accidents_full.csv";
    //const char fname[] = "./dataset/Accidents_100k.csv";
    //const char fname[] = "./dataset/Accidents_50k.csv";
    //const char fname[] = "./dataset/Accidents_100k.csv";
    //const char fname[] = "./dataset/Accidents_1k.csv";
    //const char fname[] = "./dataset/output.csv";

    SoAdataset SoA(fname, 1000000);
    SoVdataset SoV(fname, 1000000);
    SoDdataset SoD(fname, 1000000);
    AoSdataset AoS(fname, 1000000);
    VoSdataset VoS(fname, 1000000);
    DoSdataset DoS(fname, 1000000);
    UMoSdataset UMoS(fname, 1000000);
    
    cout << "\n\n";

    // ==================== ТЕСТ ПОИСКА ПОДСТРОКИ ====================
    /*
    cout << "=== Testing REGISTER-SENSITIVE substring search algorithm ===" << endl;
    cout << "\nSearching for 'Rain' in weather_condition (SoA):" << endl;

    auto results = countSubstringOccurrences(
        SoA,
        [](SoAdataset& ds, int idx) -> const char* {
            return ds.get_weather_condition(idx);
        },
        "Rain" 
    );

    int total_rain = 0;
    int records_with_rain = 0;
    for (int i = 0; i < results.size(); i++) {
        total_rain += results[i];
        if (results[i] > 0) {
            records_with_rain++;
        }
    }

    cout << "Total 'Rain' occurrences: " << total_rain << endl;
    cout << "Records containing 'Rain': " << records_with_rain << endl;
    cout << "Total records processed: " << SoA.get_size() << endl;
    */





    /*
    // STL TESTING
    ComparisonTime(SoA, AoS);

    Compare5Datasets("Test1Compare_Filter_for_temperature",
        SoV, FilterForTemperature<SoVdataset>,
        VoS, FilterForTemperature<VoSdataset>,
        SoD, FilterForTemperature<SoDdataset>,
        DoS, FilterForTemperature<DoSdataset>,
        UMoS, FilterForTemperature<UMoSdataset>
    );

    Compare5Datasets("Test2Compare_Sort_for_temperature",
        SoV, SortForTemperature<SoVdataset>,
        VoS, SortForTemperature<VoSdataset>,
        SoD, SortForTemperature<SoDdataset>,
        DoS, SortForTemperature<DoSdataset>,
        UMoS, SortForTemperature<UMoSdataset>
    );

    Compare5Datasets("Test3Compare_Search_for_temperature",
        SoV, SearchForTemperature<SoVdataset>,
        VoS, SearchForTemperature<VoSdataset>,
        SoD, SearchForTemperature<SoDdataset>,
        DoS, SearchForTemperature<DoSdataset>,
        UMoS, SearchForTemperature<UMoSdataset>
    );

    Compare5Datasets("Test4Compare+filter_for_temperature_and_speed",
        SoV, FilterForTemperatureAndWindspeed<SoVdataset>,
        VoS, FilterForTemperatureAndWindspeed<VoSdataset>,
        SoD, FilterForTemperatureAndWindspeed<SoDdataset>,
        DoS, FilterForTemperatureAndWindspeed<DoSdataset>,
        UMoS, FilterForTemperatureAndWindspeed<UMoSdataset>
    );

    Compare5Datasets("Test5Compare_Serch_for_temperature_and_wind_speed",
        SoV, SearchForTemperatureAndWindspeed<SoVdataset>,
        VoS, SearchForTemperatureAndWindspeed<VoSdataset>,
        SoD, SearchForTemperatureAndWindspeed<SoDdataset>,
        DoS, SearchForTemperatureAndWindspeed<DoSdataset>,
        UMoS, SearchForTemperatureAndWindspeed<UMoSdataset>
    );

    Compare5Datasets("Test6Compare_Insert_item_in_beginning",
        SoV, InsertItemsInBeginning<SoVdataset>,
        VoS, InsertItemsInBeginning<VoSdataset>,
        SoD, InsertItemsInBeginning<SoDdataset>,
        DoS, InsertItemsInBeginning<DoSdataset>,
        UMoS, InsertItemsInBeginning<UMoSdataset>
    );

    Compare5Datasets("Test7Compare_Delete_item_in_beginning",
        SoV, DeleteItemInBeginning<SoVdataset>,
        VoS, DeleteItemInBeginning<VoSdataset>,
        SoD, DeleteItemInBeginning<SoDdataset>,
        DoS, DeleteItemInBeginning<DoSdataset>,
        UMoS, DeleteItemInBeginning<UMoSdataset>
    );

    Compare5Datasets("Test8Compare_Insert_item_in_middle",
        SoV, InsertItemsInMiddle<SoVdataset>,
        VoS, InsertItemsInMiddle<VoSdataset>,
        SoD, InsertItemsInMiddle<SoDdataset>,
        DoS, InsertItemsInMiddle<DoSdataset>,
        UMoS, InsertItemsInMiddle<UMoSdataset>
    );

    Compare5Datasets("Test9Compare_Delete_item_in_middle",
        SoV, DeleteItemInMiddle<SoVdataset>,
        VoS, DeleteItemInMiddle<VoSdataset>,
        SoD, DeleteItemInMiddle<SoDdataset>,
        DoS, DeleteItemInMiddle<DoSdataset>,
        UMoS, DeleteItemInMiddle<UMoSdataset>
    );
    */




    /*
    // Severity sorting with bucket sort
    int bucket_time = timeit([](AoSdataset &data, int sz) {bucket_sort_by_severity(data, sz, [&data](int i) {return data.get_severity(i); }); }, AoS, AoS.get_size(), 1);
    cout << "BucketSort took " << bucket_time << "mcs.\n";
    //bucket_sort_by_severity(AoS, AoS.get_size(), [&AoS](int i) {return AoS.get_severity(i); });
    check_sort("BucketSort", AoS, [&AoS](int i) {return AoS.get_severity(i); });
    

    // MergeSort
    int merge_time = timeit([](AoSdataset& data, int sz) {merge_sort(data, sz, [&data](int i) {return data.get_temperature(i); }); }, AoS, AoS.get_size(), 1);
    cout << "MergeSort took " << merge_time << "mcs.\n";
    //merge_sort(AoS, AoS.get_size(), [&AoS](int i) { return AoS.get_temperature(i); });
    check_sort("MergeSort", AoS, [&AoS](int i) { return AoS.get_temperature(i); });
    */
    
    
    /*
  
    // ============================================================
    // COMPRESSION ALGORITHMS TESTING SECTION
    // ============================================================

    cout << "\n\n";
    cout << "========================================================================" << endl;
    cout << "COMPRESSION ALGORITHMS TESTING" << endl;
    cout << "========================================================================" << endl;

    // Run compression algorithms benchmark
    DatasetCompression::benchmarkCompression(fname);

    cout << "\n\n";
    cout << "========================================================================" << endl;
    cout << "COMPRESSION ALGORITHMS DETAILED ANALYSIS" << endl;
    cout << "========================================================================" << endl;

    // Run detailed compression analysis
    DatasetCompression::testAllCompressionAlgorithms(fname);

    cout << "\n\n";
    cout << "========================================================================" << endl;
    cout << "COMPRESSION ALGORITHMS CORRECTNESS DEMONSTRATION" << endl;
    cout << "========================================================================" << endl;

    // Run compression demo for correctness verification
    DatasetCompression::runCompressionDemo();
    */
    return 0;
}