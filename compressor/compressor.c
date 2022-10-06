#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../shared.h"
#include "../files/files.h"
#include "../utils/utils.h"
#include "compressor.h"

#include "headers/simple_kmeans_compressor.h" // KMNS

bool is_valid_format(byte format_identifier[4])
{
    char *formats[] = {"KMNS"};
    for (int i = 0; i < sizeof(formats); i++)
        if (format_identifiers_equal(format_identifier, formats[i]))
            return true;
    return false;
}

compressed_file_t compress(image_t image, byte format_identifier[4], int argc, char **argv)
{
    if (!is_valid_format(format_identifier))
        return NULL;

    compressed_file_t compressed_file = NULL;

    if (format_identifiers_equal(format_identifier, "KMNS"))
    {
        if (argc != 2)
        {
            printf("Error: invalid number of arguments for format KMNS. There must be two arguments: a positive integer for the maximum number of iterations to run the k-means algorithm, and a positive integer less than or equal to 255 for the number of clusters (colors).\n");
            return NULL;
        }
        int max_iterations = (unsigned int)atoi(argv[0]);
        if (max_iterations <= 0)
        {
            printf("Error: invalid maximum number of iterations for format KMNS. Pass in a positive integer indicating number of iterations.\n");
            return NULL;
        }
        int k = atoi(argv[1]);
        if (k <= 0 || k > 255)
        {
            printf("Error: invalid number of clusters for format KMNS. Pass in a positive integer less than or equal to 255 indicating number of clusters.\n");
            return NULL;
        }
        compressed_file = malloc(sizeof(struct compressed_file));
        byte_array_copy(compressed_file->format_identifier, format_identifier, 4);
        compressed_file->content = NULL;
        compressed_file->content_size = 0;
        compressed_file = compress_simple_kmeans(image, compressed_file, max_iterations, k);
    }

    return compressed_file;
}

image_t decompress(compressed_file_t compressed_file, int argc, char **argv)
{
    if (!is_valid_format(compressed_file->format_identifier))
        return NULL;

    image_t image = malloc(sizeof(struct image));
    image->pixels = NULL;
    image->width = 0;
    image->height = 0;

    if (format_identifiers_equal(compressed_file->format_identifier, "KMNS"))
        image = decompress_simple_kmeans(compressed_file, image);

    return image;
}
