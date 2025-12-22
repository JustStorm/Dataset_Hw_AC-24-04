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
    SoVdataset SoV(fname, 100000);
    AoSdataset AoS(fname, 100000);
    VoSdataset VoS(fname, 100000);
    UMoSdataset UMoS(fname, 100000);

    cout << "Operation speed of structure of arrays" << endl;
    ComparisonTime(SoA);
    cout << SoA.get_size();
    cout << "\n\nOperation speed of structure of vectors" << endl;
    ComparisonTime(SoV);
    cout << SoV.get_size();
    cout << "\n\nOperations speed of array of structures" << endl;
    ComparisonTime(AoS);
    cout << AoS.get_size();
    cout << "\n\nOperation speed of vector of structures" << endl;
    ComparisonTime(VoS);
    cout << VoS.get_size();
    cout << "\n\nOperation speed of unordered map of structures" << endl;
    ComparisonTimeMaps(UMoS);
    cout << UMoS.get_size();
    return 0;


}
