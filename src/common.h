/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include "lib/libbmp.h"
#include "lib/utils.h"

void loadImage(int argc, char **argv, char** inputFile, char** outputFile, BMP** image);

void step1_brightness(int width, int height, uint8_t* data, uint8_t* brightness, int wFrom, int wTo, int hFrom, int hTo);

void step2_edges(int width, int height, uint8_t* brightness, uint8_t* edge, int wFrom, int wTo, int hFrom, int hTo);

void step3_merge(int width, int height, uint8_t* data, uint8_t* edges, uint8_t* result, int wFrom, int wTo, int hFrom, int hTo);

void paintEdges(int width, int height, uint8_t* data);

void setResultAndSaveImage(BMP *image, uint8_t* result, char* outputFile);
