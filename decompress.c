#include <stdio.h>
#include <stdbool.h>
#include "shared.h"
#include "files/files.h"
#include "utils/memory/memory_utils.h"
#include "compressor/compressor.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./decompress <input> <output> [<format-specific arguments>]\n");
        return 1;
    }
    char *input = argv[1];
    char *output = argv[2];

    printf("Opening file %s for reading...\n", input);
    FILE *in = fopen(input, "rb");
    if (in == NULL)
    {
        printf("\033[1;31mError: could not open file %s\033[0m\n", input);
        return 2;
    }

    printf("Reading compressed file...\n");
    compressed_file_t compressed_file = read_compressed_file(in);
    fclose(in);
    if (compressed_file == NULL)
    {
        printf("\033[1;31mError: could not read compressed file %s\033[0m\n", input);
        return 3;
    }


    if (!is_valid_format(compressed_file->format_identifier))
    {
        printf("\033[1;31mError: invalid format identifier - compressed file may be corrupted\033[0m\n");
        free_compressed_file(compressed_file);
        return 5;
    }

    image_t image = decompress(compressed_file, argc - 3, argv + 3);
    free_compressed_file(compressed_file);

    if (image == NULL)
    {
        printf("\033[1;31mError: could not decompress file %s. There may be additional information above.\033[0m\n", input);
        return 6;
    }

    printf("Opening file %s for writing...\n", output);
    FILE *out = fopen(output, "w");
    if (out == NULL)
    {
        printf("\033[1;31mError: could not open file %s\033[0m\n", output);
        return 4;
    }

    printf("Writing decompressed image...\n");
    bool success = write_image(out, image);

    fclose(out);
    free_image(image);
    
    if (!success)
    {
        printf("\033[1;31mError: could not write decompressed image\033[0m\n");
        return 7;
    }

    printf("\033[1;32mDecompressed %s to %s!\033[0m\n", input, output);
    return 0;
}
