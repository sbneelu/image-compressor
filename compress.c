#include <stdio.h>
#include <stdbool.h>
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
        fclose(in);
        return 3;
    }

    image_t image = read_image(in);
    if (image == NULL)
    {
        printf("Error: could not read image %s\n", input);
        fclose(in);
        fclose(out);
        return 4;
    }

    byte format[4] = {format_identifier[0], format_identifier[1], format_identifier[2], format_identifier[3]};
    if (!is_valid_format(format))
    {
        printf("Error: invalid format identifier %s\n", format_identifier);
        fclose(in);
        fclose(out);
        free_image(image);
        return 5;
    }

    compressed_file_t compressed_file = compress(image, format, argc - 4, argv + 4);
    if (compressed_file == NULL)
    {
        printf("Error: could not compress file %s. There may be additional information above.\n", input);
        fclose(in);
        fclose(out);
        free_image(image);
        return 6;
    }

    write_compressed_file(out, compressed_file);

    fclose(in);
    fclose(out);

    free_image(image);
    free_compressed_file(compressed_file);

    printf("Compressed %s to %s!\n", input, output);
    return 0;
}
