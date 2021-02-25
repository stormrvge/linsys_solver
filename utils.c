#include "utils.h"
#include <stdio.h>


/*
* * * * * * * * * * * * * * * * * * * * * * trash
int64_t to_int64t(const char* s) {
    int64_t i;
    char c;
    int scanned = sscanf(s, "%" SCNd64 "%c", &i, &c);
    if (scanned == 1) return i;
    if (scanned > 1) {
        // TBD about extra data found
        return i;
    }
    // TBD failed to scan;
    return 0;
}
*/
