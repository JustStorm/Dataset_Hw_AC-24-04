#include "FilterDataset.h"
#include "utils.h"
#include "SeverityBucketSort.h"
#include <functional>

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


    // // Severity sorting with bucket sort
    // bucket_sort_by_severity(AoS, [&AoS](int i) {return AoS.get_severity(i); });
    // bool flag = true;
    // for (int i = 0; i < AoS.get_size()-1; i++) {
    //     if (AoS.get_severity(i) > AoS.get_severity(i + 1)) flag = false;
    //     //cout << AoS.get_severity(i);
    // }
    // cout << ((flag) ? "Bucket sorting finished correct\n" : "Bucket sorting is incorrect\n");
    
    
    // cout << "\n\nOperation speed of structure of arrays" << endl;
    // OperationSpeedArrays(SoA);
    // cout << "\n\nOperation speed of array of structures" << endl;
    // OperationSpeedArrays(AoS);
    // cout << "\n\nOperation speed of structure of vectors" << endl;
    // OperationSpeed(SoV);
    // cout << "\n\nOperation speed of vector of structures" << endl;
    // OperationSpeed(VoS);
    // cout << "\n\nOperation speed of structure of deques" << endl;
    // OperationSpeed(SoD);
    // cout << "\n\nOperation speed of deque of structures" << endl;
    // OperationSpeed(DoS);
    // cout << "\n\nOperation speed of unordered map of structures" << endl;
    // OperationSpeedMaps(UMoS);

    return 0;
}
