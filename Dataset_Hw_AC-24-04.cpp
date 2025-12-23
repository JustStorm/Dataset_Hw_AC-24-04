#include "FilterDataset.h"
#include "utils.h"

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

    return 0;


}
