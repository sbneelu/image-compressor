#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../shared.h"
#include "files.h"

image_t read_image(FILE *fp)
{
    image_t image = malloc(sizeof(struct image));
    fscanf(fp, "%u", &image->width);
    fscanf(fp, "%u", &image->height);
    image->pixels = malloc(sizeof(pixel_t) * image->width * image->height);
    for (unsigned int i = 0; i < image->height * image->width; i++)
    {
        image->pixels[i] = malloc(sizeof(struct pixel));
        fscanf(fp, "%hhu %hhu %hhu", &image->pixels[i]->r, &image->pixels[i]->g, &image->pixels[i]->b);
    }
    return image;
}

void write_image(FILE *fp, image_t image)
{
    fprintf(fp, "%u %u\n", image->width, image->height);
    for (unsigned int i = 0; i < image->height * image->width; i++)
        fprintf(fp, "%hhu %hhu %hhu\n", image->pixels[i]->r, image->pixels[i]->g, image->pixels[i]->b);
}

compressed_file_t read_compressed_file(FILE *fp)
{
    compressed_file_t cf = malloc(sizeof(struct compressed_file));
    fread(cf->format_identifier, 1, 4, fp);
    fread(&cf->content_size, 1, 4, fp);
    cf->content = malloc(sizeof(byte) * cf->content_size);
    fread(cf->content, 1, cf->content_size, fp);
    return cf;
}

void write_compressed_file(FILE *fp, compressed_file_t cf)
{
    fwrite(cf->format_identifier, 1, 4, fp);
    fwrite(&cf->content_size, sizeof(unsigned int), 1, fp);
    fwrite(cf->content, 1, cf->content_size, fp);
}
