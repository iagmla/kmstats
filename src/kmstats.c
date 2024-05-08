#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include "stats.c"

/* kmstats v0.0.1 */
/* by Karl Zander */

void usage() {
    printf("kmstats v0.0.1\n");
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
    FILE *infile;

    infile = fopen(inFilename, "rb");
    fseek(infile, 0, SEEK_END);
    uint32_t datalen = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    uint8_t data[datalen];
    fread(data, 1, datalen, infile);
    fclose(infile);

    struct stats s;
    statsInit(&s);
    calcOccurences(&s, data, datalen);
    printOccurences(&s);
    calcIC(&s, datalen);
    printf("IC %f\n", s.ic);
    calcEntropy(&s, datalen);
    calcAverage(&s, datalen);
    printf("Entropy %f\n", s.entropy);
    printf("Average %f\n", s.avg);

    return 0;
}
