#include <stdio.h>
#include <stdbool.h>
#include "shared.h"
#include "image.h"
#include "fileio.h"
#include "image.h"
#include "compressor.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./compress <input> <output>\n");
        return 1;
    }
    char *input = argv[1];
    char *output = argv[2];

    FILE *in = fopen(input, "r");
    if (in == NULL)
    {
        printf("Error: could not open file %s\n", input);
        return 2;
    }

    FILE *out = fopen(output, "wb");
    if (out == NULL)
    {
        printf("Error: could not open file %s\n", output);
        return 3;
    }

    image_t image = read_image(in);
    if (image == NULL)
    {
        printf("Error: could not read image %s\n", input);
        return 4;
    }

    compressed_file_t compressed_file = compress(image);
    write_compressed_file(out, compressed_file);
    
    fclose(in);
    fclose(out);

    free_image(image);
    free_compressed_file(compressed_file);

    printf("Compressed %s to %s!\n", input, output);
    return 0;
}
