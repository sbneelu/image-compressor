#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "shared.h"
#include "files/files.h"
#include "utils/memory/memory_utils.h"
#include "compressor/compressor.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Usage: ./compress <input> <output> <format identifier> [<format-specific arguments>]\n");
        return 1;
    }
    char *input = argv[1];
    char *output = argv[2];
    char *format_identifier = argv[3];

    if (strlen(format_identifier) != 4)
    {
        printf("\033[1;31mError: invalid format identifier\033[0m\n");
        return 2;
    }

    byte format[4] = {format_identifier[0], format_identifier[1], format_identifier[2], format_identifier[3]};
    if (!is_valid_format(format))
    {
        printf("\033[1;31mError: invalid format identifier\033[0m\n");
        return 3;
    }

    printf("Opening file %s for reading...\n", input);
    FILE *in = fopen(input, "r");
    if (in == NULL)
    {
        printf("\033[1;31mError: could not open file %s\033[0m\n", input);
        return 4;
    }
    
    image_t image = read_image(in);
    fclose(in);
    if (image == NULL)
    {
        printf("\033[1;31mError: could not read image %s\033[0m\n", input);
        return 5;
    }
    
    printf("Compressing image...\n");
    compressed_file_t compressed_file = compress(image, format, argc - 4, argv + 4);
    free_image(image);
    if (compressed_file == NULL)
    {
        printf("\033[1;31mError: could not compress file %s. There may be additional information above.\033[0m\n", input);
        return 6;
    }

    printf("Opening file %s for writing...\n", output);
    FILE *out = fopen(output, "wb");
    if (out == NULL)
    {
        printf("\033[1;31mError: could not open file %s\033[0m\n", output);
        return 7;
    }

    printf("Writing compressed file...\n");
    write_compressed_file(out, compressed_file);

    fclose(out);
    free_compressed_file(compressed_file);

    printf("\033[1;32mCompressed %s to %s!\033[0m\n", input, output);
    return 0;
}
