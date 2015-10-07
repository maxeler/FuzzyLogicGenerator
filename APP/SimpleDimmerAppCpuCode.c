#include <stdio.h>
#include <stdlib.h>

#include "MaxSLiCInterface.h"
#include "Maxfiles.h"

void readFile(int size, float* inputAmbient, float* outputPower) {
    FILE * file;
    char buffer[1000];
    int i;

    file = fopen("SimpleDimmerApp.fld", "r");
    fscanf(file, "%s %s ", buffer, buffer);
    for (i = 0; i < size; i++) {
        fscanf(file, "%f %f", &(inputAmbient)[i], &(outputPower)[i]);
    }
}

void writeFile(int size, float* inputAmbient, float* outputPower) {
    FILE * file;
    int i;

    file = fopen("SimpleDimmerApp.fld", "w");
    fprintf(file, "Ambient Power\n");
    for (i = 0; i < size; i++) {
        fprintf(file, "%f %f\n", inputAmbient[i], outputPower[i]);
    }
}

int main(void)
{
    const int size = 1000;
    const int sizeBytes = size * sizeof(float);
    float *inputAmbient = malloc(sizeBytes);
    float *outputPower = malloc(sizeBytes);

    readFile(size, inputAmbient, outputPower);

    printf("Running on DFE.\n");
    SimpleDimmerApp(size, inputAmbient, outputPower);


    writeFile(size, inputAmbient, outputPower);

    return 0;
}