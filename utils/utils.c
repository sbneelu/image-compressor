#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../shared.h"
#include "../files/files.h"
#include "utils.h"

byte *pixel_to_bytes(pixel_t pixel, byte *bytes)
{
    bytes[0] = pixel->r;
    bytes[1] = pixel->g;
    bytes[2] = pixel->b;
    return bytes;
}

pixel_t bytes_to_pixel(byte *bytes)
{
    pixel_t pixel = malloc(sizeof(struct pixel));
    pixel->r = bytes[0];
    pixel->g = bytes[1];
    pixel->b = bytes[2];
    return pixel;
}

byte *unsigned_int_to_bytes(unsigned int i, byte *bytes)
{
    bytes[0] = (i >> 24) & 0xFF;
    bytes[1] = (i >> 16) & 0xFF;
    bytes[2] = (i >> 8) & 0xFF;
    bytes[3] = i & 0xFF;
    return bytes;
}

unsigned int bytes_to_unsigned_int(byte *bytes)
{
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

int square_distance(pixel_t a, pixel_t b)
{
    return (a->r - b->r) * (a->r - b->r) + (a->g - b->g) * (a->g - b->g) + (a->b - b->b) * (a->b - b->b);
}

pixel_t pixel_copy(pixel_t to, const pixel_t from)
{
    to->r = from->r;
    to->g = from->g;
    to->b = from->b;
    return to;
}

pixel_t *pixel_array_copy(pixel_t *to, const pixel_t *from, int len)
{
    for (int i = 0; i < len; i++)
        pixel_copy(to[i], from[i]);
    return to;
}

bool pixel_arrays_equal(const pixel_t *a, const pixel_t *b, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i]->r != b[i]->r || a[i]->g != b[i]->g || a[i]->b != b[i]->b)
            return false;
    }
    return true;
}

byte *byte_array_copy(byte *to, const byte *from, int len)
{
    for (int i = 0; i < len; i++)
        to[i] = from[i];
    return to;
}

bool byte_arrays_equal(const byte *a, const byte *b, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}