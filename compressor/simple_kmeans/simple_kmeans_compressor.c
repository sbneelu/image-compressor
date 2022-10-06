#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../shared.h"
#include "../../files/files.h"
#include "../../utils/utils.h"
#include "../../utils/kmeans/kmeans_utils.h"
#include "../headers/simple_kmeans_compressor.h"

compressed_file_t compress_simple_kmeans(image_t image, compressed_file_t compressed_file, unsigned int max_iterations, int k)
{
    unsigned int num_of_pixels = image->width * image->height;
    unsigned int *assignments = malloc(sizeof(unsigned int) * num_of_pixels);
    pixel_t *centroids = malloc(sizeof(pixel_t) * k);

    for (int i = 0; i < k; i++)
        centroids[i] = malloc(sizeof(struct pixel));

    kmeans(image->pixels, num_of_pixels, k, max_iterations, assignments, centroids);

    compressed_file->content_size = 4 + 4 + 1 + 3 * k + image->width * image->height;
    compressed_file->content = malloc(sizeof(byte) * compressed_file->content_size);

    unsigned_int_to_bytes(image->width, compressed_file->content);
    unsigned_int_to_bytes(image->height, compressed_file->content + 4);

    compressed_file->content[8] = (byte)k;

    for (int i = 0; i < k; i++)
        pixel_to_bytes(centroids[i], compressed_file->content + 9 + 3 * i);

    for (unsigned int i = 0; i < image->width * image->height; i++)
        compressed_file->content[9 + 3 * k + i] = (byte)assignments[i];

    free(assignments);
    for (int i = 0; i < k; i++)
        free(centroids[i]);
    free(centroids);

    return compressed_file;
}

image_t decompress_simple_kmeans(compressed_file_t compressed_file, image_t image)
{
    image->width = bytes_to_unsigned_int(compressed_file->content);
    image->height = bytes_to_unsigned_int(compressed_file->content + 4);
    image->pixels = malloc(sizeof(pixel_t) * image->width * image->height);
    for (unsigned int i = 0; i < image->width * image->height; i++)
        image->pixels[i] = malloc(sizeof(struct pixel));

    int k = compressed_file->content[8];

    pixel_t *centroids = malloc(sizeof(pixel_t) * k);
    for (int i = 0; i < k; i++)
        centroids[i] = bytes_to_pixel(compressed_file->content + 9 + 3 * i);

    byte *assignments = malloc(sizeof(byte) * image->width * image->height);
    for (unsigned int i = 0; i < image->width * image->height; i++)
        assignments[i] = compressed_file->content[9 + 3 * k + i];

    for (unsigned int i = 0; i < image->width * image->height; i++)
        pixel_copy(image->pixels[i], centroids[assignments[i]]);

    for (int i = 0; i < k; i++)
        free(centroids[i]);
    free(centroids);
    free(assignments);

    return image;
}
