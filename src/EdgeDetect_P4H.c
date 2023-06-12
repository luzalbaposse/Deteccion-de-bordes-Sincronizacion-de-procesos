/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lib/libbmp.h"
#include "lib/utils.h"
#include "common.h"

uint32_t width;
uint32_t height;
uint8_t* data;

uint8_t* brightness;
uint8_t* edges;
uint8_t* result;

int main(int argc, char **argv) {

  char* inputFileName;
  char* outputFileName;
  BMP* img;

  // Cargado de imagen en memoria
  loadImage(argc, argv, &inputFileName, &outputFileName, &img);
  width = bmp_width(img);
  height = bmp_height(img);
  data = bmp_data(img);

  // Solicito memoria para datos temporales
  brightness = (uint8_t*) malloc(width * height);
  edges = (uint8_t*) malloc(width * height);
  result = (uint8_t*) malloc(width * height * sizeof(bgra_t));

  // Procesamiento de la imagen

  // Completar con el procesamiento de la imagen
  

  // Liberacion de memoria
  free(brightness);
  free(edges);
  free(data);

  // Guardado de la imagen
  setResultAndSaveImage(img, result, outputFileName);

  return 0;
}
