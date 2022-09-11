#include <stdlib.h>
#include <stdbool.h>
#include "../../shared.h"
#include "../../image.h"
#include "utils.h"

void pixel_to_bytes(pixel_t pixel, byte *bytes)
{
    bytes[0] = pixel->r;
    bytes[1] = pixel->g;
    bytes[2] = pixel->b;
}

pixel_t bytes_to_pixel(byte *bytes)
{
    pixel_t pixel = malloc(sizeof(struct pixel));
    pixel->r = bytes[0];
    pixel->g = bytes[1];
    pixel->b = bytes[2];
    return pixel;
}

void int_to_bytes(int i, byte *bytes)
{
    bytes[0] = (i >> 24) & 0xFF;
    bytes[1] = (i >> 16) & 0xFF;
    bytes[2] = (i >> 8) & 0xFF;
    bytes[3] = i & 0xFF;
}

int bytes_to_int(byte *bytes)
{
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}