/* ************************************************************************* */
/*   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         */
/* ************************************************************************* */

#include "utils.h"

uint8_t utils_saturate(int32_t a) {
    if(a > 255) {
        return 255;
    } else {
        if(a < 0 ) {
            return 0;
        } else {
            return a;
        }
    }
}

void utils_copyBorders32( uint8_t *src, uint8_t *dst,
                          int width, int height, int row_size,
                          int size) {
    uint32_t (*src_matrix)[(row_size+3)/4] = (uint32_t (*)[(row_size+3)/4]) src;
    uint32_t (*dst_matrix)[(row_size+3)/4] = (uint32_t (*)[(row_size+3)/4]) dst;
    
    for (int i = 0; i < height; i++) {
        for (int x = 0; x < size; x++)
            *((uint32_t*)(&(dst_matrix[i][x]))) = *((uint32_t*)(&(src_matrix[i][x])));
        for (int x = width-1-size; x < width; x++)
            *((uint32_t*)(&(dst_matrix[i][x]))) = *((uint32_t*)(&(src_matrix[i][x])));
    }
    for (int j = size; j < width-size; j++) {
        for (int x = 0; x < size; x++)
            *((uint32_t*)(&(dst_matrix[x][j]))) = *((uint32_t*)(&(src_matrix[x][j])));
        for (int x = height-1-size; x < height; x++)
            *((uint32_t*)(&(dst_matrix[x][j]))) = *((uint32_t*)(&(src_matrix[x][j])));
    }
}

void utils_paintBorders32( uint8_t *dst,
                           int width, int height, int row_size,
                           int size, uint32_t rgba) {
    uint32_t (*dst_matrix)[(row_size+3)/4] = (uint32_t (*)[(row_size+3)/4]) dst;
    
    for (int i = 0; i < height; i++) {
        for (int x = 0; x < size; x++)
            *((uint32_t*)(&(dst_matrix[i][x]))) = rgba;
        for (int x = width-size; x < width; x++)
            *((uint32_t*)(&(dst_matrix[i][x]))) = rgba;
    }
    for (int j = size; j < width-size; j++) {
        for (int x   = 0; x < size; x++)
            *((uint32_t*)(&(dst_matrix[x][j]))) = rgba;
        for (int x = height-size; x < height; x++)
            *((uint32_t*)(&(dst_matrix[x][j]))) = rgba;
    }
}

void utils_paintBorders8( uint8_t *dst,
                          int width, int height, int row_size,
                          int size, uint8_t color) {
    uint8_t (*dst_matrix)[row_size] = (uint8_t (*)[row_size]) dst;
    
    for (int i = 0; i < height; i++) {
        for (int x = 0; x < size; x++)
            *((uint8_t*)(&(dst_matrix[i][x]))) = color;
        for (int x = width-size; x < width; x++)
            *((uint8_t*)(&(dst_matrix[i][x]))) = color;
    }
    for (int j = size; j < width-size; j++) {
        for (int x   = 0; x < size; x++)
            *((uint8_t*)(&(dst_matrix[x][j]))) = color;
        for (int x = height-size; x < height; x++)
            *((uint8_t*)(&(dst_matrix[x][j]))) = color;
    }
}

uint8_t* utils_verticalFlip(uint8_t *src, int height, int width) {
    uint8_t *dst = malloc(height*width);
    uint8_t (*src_matrix)[width] = (uint8_t (*)[width]) src;
    uint8_t (*dst_matrix)[width] = (uint8_t (*)[width]) dst;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            dst_matrix[i][j] = src_matrix[height-1-i][j];
        }
    }
    free(src);
    return (uint8_t*)dst;
}
