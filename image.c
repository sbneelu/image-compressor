#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "shared.h"
#include "image.h"

void free_image(image_t image)
{
    for (int i = 0; i < image->height * image->width; i++)
    {
        free(image->pixels[i]);
    }
    free(image->pixels);
    free(image);
}

void free_compressed_file(compressed_file_t compressed_file)
{
    free(compressed_file->content);
    free(compressed_file);
}

void pixel_copy(pixel_t to, const pixel_t from)
{
    to->r = from->r;
    to->g = from->g;
    to->b = from->b;
}

void pixel_array_copy(pixel_t *to, const pixel_t *from, int len)
{
    for (int i = 0; i < len; i++)
        pixel_copy(to[i], from[i]);
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

int square_distance(pixel_t a, pixel_t b)
{
    return (a->r - b->r) * (a->r - b->r) + (a->g - b->g) * (a->g - b->g) + (a->b - b->b) * (a->b - b->b);
}
