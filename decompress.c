#include <stdio.h>
#include <stdbool.h>
#include "shared.h"
#include "image.h"
#include "fileio.h"
#include "compressor.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./decompress <input> <output>\n");
        return 1;
    }
    char *input = argv[1];
    char *output = argv[2];

    FILE *in = fopen(input, "rb");
    if (in == NULL)
    {
        printf("Error: could not open file %s\n", input);
        return 2;
    }

    FILE *out = fopen(output, "w");
    if (out == NULL)
    {
        printf("Error: could not open file %s\n", output);
        return 3;
    }

    compressed_file_t compressed_file = read_compressed_file(in);
    if (compressed_file == NULL)
    {
        printf("Error: could not read compressed file %s\n", input);
        return 4;
    }

    image_t image = decompress(compressed_file);
    write_image(out, image);
    
    fclose(in);
    fclose(out);

    free_image(image);
    free_compressed_file(compressed_file);

    printf("Decompressed %s to %s!\n", input, output);
    return 0;
}
