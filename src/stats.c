/* kmstats */
/* by Karl Zander */

struct stats {
    int occurences[256];
    double fractions[256];
    double probabilities[256];
    double ic;
    double entropy;
    double avg;
    double serialCorrelation;
    uint32_t datalen;
    char *inFilename;
};

void statsInit(struct stats *s) {
    memset(s->occurences, 0, 256 * sizeof(int));
    s->ic = 0.0;
    s->avg = 0.0;
    s->entropy = 0.0;
}

void calcStats(struct stats *s, char *inFilename) {
    FILE *infile;
    infile = fopen(inFilename, "rb");
    fseek(infile, 0, SEEK_END);
    uint32_t datalen = ftell(infile);
    s->datalen = datalen;
    fseek(infile, 0, SEEK_SET);
    uint8_t data;
    double p = 0.0;
    double e = 127.5;
    double last = 0.0;
    for (int i = 0; i < datalen; i++) {
        fread(&data, 1, 1, infile);
        s->occurences[data] += 1;
        p = ((data - (e)) / (last - (e)));
        last = p;
    }
    s->serialCorrelation = p;
    fclose(infile);
}

void printStats(struct stats *s) {
    printf("Value  Occurences  Fractions  Probabilitiy\n");
    for (int i = 0; i < 256; i++) {
        printf("%3d    %10d  %7f   %7f\n", i, s->occurences[i], s->fractions[i], s->probabilities[i]);
    }
    printf("Entropy %f\n", s->entropy);
    printf("Average %f\n", s->avg);
    printf("IC %f\n", s->ic);
    printf("Serial Correlation %f\n", s->serialCorrelation);
}

void calcIC(struct stats *s) {
    float p = 0.0;
    for (int i = 0; i < 256; i++) {
        p += ((s->occurences[i] / (s->datalen / 256.0)) * (s->occurences[i] - 1) / ((s->datalen - 1) / 256.0));
    }
    s->ic = p;
}

void calcEntropy(struct stats *s) {
    for (int i = 0; i < 256; i++) {
        if (s->occurences[i] != 0.0) {
            s->entropy += ((double)s->occurences[i] / s->datalen) * log2(1 / ((double)s->occurences[i] / s->datalen));
        }
    }
}

void calcAverage(struct stats *s) {
    for (int i = 0; i < 256; i++) {
        s->avg += s->occurences[i] * i;
    }
    s->avg = s->avg / s->datalen;
}

void calcFractions(struct stats *s) {
    for (int i = 0; i < 256; i++) {
        s->fractions[i] = (double)((double)s->occurences[i] / (double)s->datalen);
    }
}

void calcProbabilities(struct stats *s) {
    for (int i = 0; i < 256; i++) {
        s->probabilities[i] = s->fractions[i] * 256.0;
    }
}   
