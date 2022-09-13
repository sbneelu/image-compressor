#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../shared.h"
#include "../files/files.h"
#include "../utils/utils.h"
#include "compressor.h"

#include "headers/simple_kmeans_compressor.h" // KMNS

bool is_format_valid(byte format_identifier[4])
{
    return true; // TODO: Fix this
}

compressed_file_t compress(image_t image, byte format_identifier[4])
{
    if (!is_format_valid(format_identifier))
        return NULL;

    compressed_file_t compressed_file = malloc(sizeof(struct compressed_file));
    byte_array_copy(compressed_file->format_identifier, format_identifier, 4);
    compressed_file->content = NULL;
    compressed_file->content_size = 0;

    if (byte_arrays_equal(format_identifier, "KMNS", 4))
        compressed_file = compress_simple_kmeans(image, compressed_file);

    return compressed_file;
}

image_t decompress(compressed_file_t compressed_file)
{
    if (!is_format_valid(compressed_file->format_identifier))
        return NULL;

    image_t image = malloc(sizeof(struct image));
    image->pixels = NULL;
    image->width = 0;
    image->height = 0;

    if (byte_arrays_equal(compressed_file->format_identifier, "KMNS", 4))
        image = decompress_simple_kmeans(compressed_file, image);

    return image;
}
