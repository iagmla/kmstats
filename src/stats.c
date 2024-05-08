/* kmstats */
/* by Karl Zander */

struct stats {
    int occurences[256];
    double ic;
    double entropy;
    double avg;
};

void statsInit(struct stats *s) {
    memset(s->occurences, 0, 256 * sizeof(int));
    s->ic = 0.0;
    s->avg = 0.0;
    s->entropy = 0.0;
}

uint32_t calcOccurences(struct stats *s, char *inFilename) {
    FILE *infile;
    infile = fopen(inFilename, "rb");
    fseek(infile, 0, SEEK_END);
    uint32_t datalen = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    uint8_t data;
    for (int i = 0; i < datalen; i++) {
        fread(&data, 1, 1, infile);
        s->occurences[data] += 1;
    }
    fclose(infile);
    return datalen;
}

void printOccurences(struct stats *s) {
    printf("Value  Occurences\n");
    for (int i = 0; i < 256; i++) {
        printf("%3d    %d\n", i, s->occurences[i]);
    }
}

void calcIC(struct stats *s, uint32_t datalen) {
    float p = 0.0;
    for (int i = 0; i < 256; i++) {
        p += ((s->occurences[i] / (datalen / 256.0)) * (s->occurences[i] - 1) / ((datalen - 1) / 256.0));
    }
    s->ic = p;
}

void calcEntropy(struct stats *s, uint32_t datalen) {
    for (int i = 0; i < 256; i++) {
        if (s->occurences[i] != 0.0) {
            s->entropy += ((double)s->occurences[i] / datalen) * log2(1 / ((double)s->occurences[i] / datalen));
        }
    }
}

void calcAverage(struct stats *s, uint32_t datalen) {
    for (int i = 0; i < 256; i++) {
        s->avg += s->occurences[i] * i;
    }
    s->avg = s->avg / datalen;
}
