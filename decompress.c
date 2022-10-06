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
        fclose(in);
        return 3;
    }

    compressed_file_t compressed_file = read_compressed_file(in);
    if (compressed_file == NULL)
    {
        printf("Error: could not read compressed file %s\n", input);
        fclose(in);
        fclose(out);
        return 4;
    }

    if (!is_valid_format(compressed_file->format_identifier))
    {
        printf("Error: invalid format identifier - compressed file may be corrupted\n");
        fclose(in);
        fclose(out);
        free_compressed_file(compressed_file);
        return 5;
    }

    image_t image = decompress(compressed_file, argc - 3, argv + 3);
    if (image == NULL)
    {
        printf("Error: could not decompress file %s. There may be additional information above.\n", input);
        fclose(in);
        fclose(out);
        free_compressed_file(compressed_file);
        return 6;
    }

    bool success = write_image(out, image);

    fclose(in);
    fclose(out);

    free_image(image);
    free_compressed_file(compressed_file);

    if (!success)
    {
        printf("Error: Could not write decompressed image.");
        return 7;
    }

    printf("Decompressed %s to %s!\n", input, output);
    return 0;
}
