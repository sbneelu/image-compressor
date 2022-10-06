#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <png.h>
#include "../shared.h"
#include "files.h"

image_t read_image(FILE *fp)
{
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
        return NULL;

    png_infop info = png_create_info_struct(png);
    if (!info)
        return NULL;

    if (setjmp(png_jmpbuf(png)))
        return NULL;

    png_init_io(png, fp);
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    pixel_t *pixels = malloc(sizeof(pixel_t) * width * height);
    png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
    for (int i = 0; i < height; i++)
        row_pointers[i] = (png_bytep)malloc(png_get_rowbytes(png, info));

    png_read_image(png, row_pointers);

    for (int i = 0; i < height; i++)
    {
        png_bytep row = row_pointers[i];
        for (int j = 0; j < width; j++)
        {
            png_bytep px = &(row[j * 4]);
            pixel_t pixel = malloc(sizeof(struct pixel));
            pixel->r = px[0];
            pixel->g = px[1];
            pixel->b = px[2];
            pixels[i * width + j] = pixel;
        }
    }

    for (int i = 0; i < height; i++)
        free(row_pointers[i]);
    free(row_pointers);

    png_destroy_read_struct(&png, &info, NULL);

    image_t image = malloc(sizeof(struct image));
    image->width = width;
    image->height = height;
    image->pixels = pixels;

    return image;
}

bool write_image(FILE *fp, image_t image)
{
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
        return false;

    png_infop info = png_create_info_struct(png);
    if (!info)
        return false;

    if (setjmp(png_jmpbuf(png)))
        return false;

    png_init_io(png, fp);

    png_set_IHDR(
        png,
        info,
        image->width,
        image->height,
        8,
        PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    png_bytep *row_pointers = malloc(sizeof(png_bytep) * image->height);
    for (int i = 0; i < image->height; i++)
    {
        row_pointers[i] = (png_bytep)malloc(png_get_rowbytes(png, info));
        png_bytep row = row_pointers[i];
        for (int j = 0; j < image->width; j++)
        {
            png_bytep px = &(row[j * 3]);
            pixel_t pixel = image->pixels[i * image->width + j];
            px[0] = pixel->r;
            px[1] = pixel->g;
            px[2] = pixel->b;
        }
    }

    png_write_image(png, row_pointers);

    for (int i = 0; i < image->height; i++)
        free(row_pointers[i]);
    free(row_pointers);

    png_destroy_write_struct(&png, &info);
    return true;
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
