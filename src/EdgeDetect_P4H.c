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

void* process1(void* arg) {
  step1_brightness(width, height, data, brightness, 0, width/4-1, 0, height);
  step2_edges(width, height, brightness, edges, 0, width/4, 0, height-1);
  step3_merge(width, height, data, edges, result, 0, width/4, 0, height-1);
  return NULL;
}

void* process2(void* arg) {
  step1_brightness(width, height, data, brightness, width/4, width/2-1, 0, height);
  step2_edges(width, height, brightness, edges, width/4+1, width/2-1, 0, height-1);
  step3_merge(width, height, data, edges, result, width/4+1, width/2-1, 0, height-1);
  return NULL;
}

void* process3(void* arg) {
  step1_brightness(width, height, data, brightness, width/2, 3*width/4-1, 0, height);
  step2_edges(width, height, brightness, edges, width/2+1, 3*width/4-1, 0, height-1);
  step3_merge(width, height, data, edges, result, width/2+1, 3*width/4-1, 0, height-1);
  return NULL;
}

void* process4(void* arg) {
  step1_brightness(width, height, data, brightness, 3*width/4, width-1, 0, height);
  step2_edges(width, height, brightness, edges, 3*width/4+1, width-1, 0, height-1);
  step3_merge(width, height, data, edges, result, 3*width/4+1, width-1, 0, height-1);
  return NULL;
}
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
  pthread_t thread1, thread2, thread3, thread4;
  pthread_create(&thread1, NULL, process1, NULL);
  pthread_create(&thread2, NULL, process2, NULL);
  pthread_create(&thread3, NULL, process3, NULL);
  pthread_create(&thread4, NULL, process4, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);

  // Liberacion de memoria
  free(brightness);
  free(edges);
  free(data);

  // Guardado de la imagen
  setResultAndSaveImage(img, result, outputFileName);

  return 0;
}
