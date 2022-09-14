#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../shared.h"
#include "../../files/files.h"
#include "memory_utils.h"

void free_image(image_t image)
{
    for (unsigned int i = 0; i < image->height * image->width; i++)
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
