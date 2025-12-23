#include "SeverityBucketSort.h"
#include "AoSdataset.h"
#include "SoAdataset.h"

void bucket_sort_severity(AoSdataset& ds) {
    bucket_sort_by_severity(ds);
}

void bucket_sort_severity(SoAdataset& ds) {
    bucket_sort_by_severity(ds);
}
