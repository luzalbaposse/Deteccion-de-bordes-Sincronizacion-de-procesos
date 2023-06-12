/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include "lib/libbmp.h"
#include "lib/utils.h"

void loadImage(int argc, char **argv, char** inputFile, char** outputFile, BMP** image) {

  char* inputFileName;
  char* outputFileName;

  if(argc < 3) {
    printf("Usage:\n");
    printf("$ ./tp2 <inputFile> <outputFile>\n\n");
    printf("Example:\n");
    printf("$ ./tp2 imagen.bmp resultado.bmp\n");
    exit(1);
  }

  *inputFile = argv[1];
  *outputFile = argv[2];
  *image = bmp_read(*inputFile);

  uint32_t width = bmp_width(*image);
  uint32_t height = bmp_height(*image);
  uint32_t bytes = bmp_bytes_per_row(*image);
  uint16_t bits = bmp_bit_count(*image);
  uint32_t compress = bmp_compression(*image);
  
  printf("ancho: %i pixeles\n",width);
  printf("alto:  %i pixeles\n",height);
  printf("ancho en bytes: %i bytes\n",bytes);
  printf("bits por pixel: %i bits\n",bits);
  printf("compress codel: %i\n",compress);

  if(compress != 3 || bits != 32) {
    printf("Error: Tipo de imagen no soportado");
    exit(1);
  }
}

void step1_brightness(int width, int height, uint8_t* data, uint8_t* brightness, int wFrom, int wTo, int hFrom, int hTo) {
  bgra_t (*image)[width] = (bgra_t (*)[width]) data;
  uint8_t (*b)[width] = (uint8_t (*)[width]) brightness;
  for(int i=hFrom; i<hTo; i++) {
    for(int j=wFrom; j<wTo; j++) {
          b[i][j] = (image[i][j].r + 2 * image[i][j].g + image[i][j].b) / 4; 
    }
  }
}

void step2_edges(int width, int height, uint8_t* brightness, uint8_t* edges, int wFrom, int wTo, int hFrom, int hTo) {
  uint8_t (*b)[width] = (uint8_t (*)[width]) brightness;
  uint8_t (*e)[width] = (uint8_t (*)[width]) edges;
  for(int i=hFrom; i<hTo; i++) {
    for(int j=wFrom; j<wTo; j++) {
          int dh = abs(
              (-1) * b[i-1][j-1] + (0) * b[i][j-1] + (+1) * b[i+1][j-1] +
              (-2) * b[i-1][j+0] + (0) * b[i][j+0] + (+2) * b[i+1][j+0] +
              (-1) * b[i-1][j+1] + (0) * b[i][j+1] + (+1) * b[i+1][j+1] ) / 8;

          int dv = abs(
              (-1) * b[i-1][j-1] + (-2) * b[i][j-1] + (-1) * b[i+1][j-1] +
              (+0) * b[i-1][j+0] + (+0) * b[i][j+0] + (+0) * b[i+1][j+0] +
              (+1) * b[i-1][j+1] + (+2) * b[i][j+1] + (+1) * b[i+1][j+1] ) / 8;

          uint8_t sum = SAT(dh + dv);
          e[i][j] = sum;
    }
  }
}

void step3_merge(int width, int height, uint8_t* data, uint8_t* edges, uint8_t* result, int wFrom, int wTo, int hFrom, int hTo) {
  bgra_t (*image)[width] = (bgra_t (*)[width]) data;
  uint8_t (*e)[width] = (uint8_t (*)[width]) edges;
  bgra_t (*r)[width] = (bgra_t (*)[width]) result;
  for(int i=hFrom; i<hTo; i++) {
    for(int j=wFrom; j<wTo; j++) {
          uint8_t value = SAT(e[i][j] * 10);
          r[i][j].r = (value * image[i][j].r) / 255;
          r[i][j].g = (value * image[i][j].g) / 255;
          r[i][j].b = (value * image[i][j].b) / 255;
          r[i][j].a = 255;
    }
  }
}

void paintEdges(int width, int height, uint8_t* data) {
  bgra_t (*result)[width] = (bgra_t (*)[width]) data;
  for(int i=0; i<height; i++) {
    result[i][0].r = 0;
    result[i][0].g = 0;
    result[i][0].b = 0;
    result[i][0].a = 255;
    result[i][width-1].r = 0;
    result[i][width-1].g = 0;
    result[i][width-1].b = 0;
    result[i][width-1].a = 255;
  }
  for(int j=1; j<width-1; j++) {
    result[0][j].r = 0;
    result[0][j].g = 0;
    result[0][j].b = 0;
    result[0][j].a = 255;
    result[height-1][j].r = 0;
    result[height-1][j].g = 0;
    result[height-1][j].b = 0;
    result[height-1][j].a = 255;
  }
}

void setResultAndSaveImage(BMP *image, uint8_t* result, char* outputFile) {
  bmp_set_data(image, result);
  bmp_save(outputFile, image);
  bmp_delete(image);
}
