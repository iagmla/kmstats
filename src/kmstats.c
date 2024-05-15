#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include "stats.c"

/* kmstats v0.1.0 */
/* by Karl Zander */

void usage() {
    printf("kmstats v0.1.1\n");
    printf("Usage: kmstats <input file>\n");
}

int main(int arc, char *argv[]) {
    if (arc != 2) {
        usage();
        return 0;
    }
    char *inFilename;
    inFilename = argv[1];
    if (access(inFilename, F_OK) == -1 ) {
        printf("%s not found\n", inFilename);
        exit(1);
    }

    struct stats s;
    s.inFilename = inFilename;
    statsInit(&s);
    calcStats(&s, inFilename);
    calcFractions(&s);
    calcProbabilities(&s);
    calcIC(&s);
    calcEntropy(&s);
    calcAverage(&s);
    calcChiSQ(&s);
    calcSerialCorrelation(&s);
    printStats(&s);

    return 0;
}
