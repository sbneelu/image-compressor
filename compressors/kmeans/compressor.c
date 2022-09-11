#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../shared.h"
#include "../../image.h"
#include "../../compressor.h"
#include "utils.h"
#include "kmeans.h"

char *compression_identifier = "KMNS";

compressed_file_t compress(image_t image)
{
    compressed_file_t cf = malloc(sizeof(struct compressed_file));
    cf->identifier[0] = 'K';
    cf->identifier[1] = 'M';
    cf->identifier[2] = 'N';
    cf->identifier[3] = 'S';

    kmeans_compressed_image_t compressed_image = compress_with_kmeans(image);

    cf->size = 4 + 4 + 1 + 3 * compressed_image->k + compressed_image->width * compressed_image->height;
    cf->content = malloc(cf->size);

    int_to_bytes(image->width, cf->content);
    int_to_bytes(image->height, cf->content + 4);

    cf->content[8] = compressed_image->k;

    for (int i = 0; i < compressed_image->k; i++)
        pixel_to_bytes(compressed_image->centroids[i], cf->content + 9 + 3 * i);

    for (int i = 0; i < compressed_image->width * compressed_image->height; i++)
        cf->content[9 + 3 * compressed_image->k + i] = compressed_image->assignments[i];

    free(compressed_image->assignments);
    for (int i = 0; i < compressed_image->k; i++)
        free(compressed_image->centroids[i]);
    free(compressed_image->centroids);
    free(compressed_image);

    return cf;
}

image_t decompress(compressed_file_t cf)
{
    image_t image = malloc(sizeof(struct image));

    image->width = bytes_to_int(cf->content);
    image->height = bytes_to_int(cf->content + 4);
    image->pixels = malloc(sizeof(pixel_t) * image->width * image->height);
    for (int i = 0; i < image->width * image->height; i++)
        image->pixels[i] = malloc(sizeof(struct pixel));

    int k = cf->content[8];

    pixel_t *centroids = malloc(sizeof(pixel_t) * k);
    for (int i = 0; i < k; i++)
        centroids[i] = bytes_to_pixel(cf->content + 9 + 3 * i);

    byte *assignments = malloc(image->width * image->height);
    for (int i = 0; i < image->width * image->height; i++)
        assignments[i] = cf->content[9 + 3 * k + i];

    for (int i = 0; i < image->width * image->height; i++)
        pixel_copy(centroids[assignments[i]], image->pixels[i]);
    
    for (int i = 0; i < k; i++)
        free(centroids[i]);
    free(centroids);
    free(assignments);

    return image;
}
