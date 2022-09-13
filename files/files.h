#pragma once

struct pixel
{
    byte r;
    byte g;
    byte b;
};

/**
 * @brief A pixel
 *
 * @param r: the red value
 * @param g: the green value
 * @param b: the blue value
 */
typedef struct pixel *pixel_t;

struct image
{
    unsigned int width;
    unsigned int height;
    pixel_t *pixels;
};

/**
 * @brief An image
 *
 * @param width The width of the image
 * @param height The height of the image
 * @param pixels The pixels of the image
 */
typedef struct image *image_t;

struct compressed_file
{
    byte format_identifier[4];
    byte *content;
    unsigned int content_size;
};
/**
 * @brief A compressed file
 *
 * @param format_identifier The identifier of the compression format
 * @param content The content of the compressed file
 * @param content_size The size of the content
 */
typedef struct compressed_file *compressed_file_t;

/**
 * @brief Read an image from a file pointer.
 *
 * @param fp: the file pointer to read from
 * @return the image read from the file pointer
 */
image_t read_image(FILE *fp);

/**
 * @brief Write an image to a file pointer.
 *
 * @param fp: the file pointer to write to
 * @param image: the image to write
 */
void write_image(FILE *fp, image_t image);

/**
 * @brief Read a compressed file from a file pointer.
 *
 * @param fp: the file pointer to read from
 * @return the compressed file read from the file pointer
 */
compressed_file_t read_compressed_file(FILE *fp);

/**
 * @brief Write a compressed file to a file pointer.
 *
 * @param fp: the file pointer to write to
 * @param cf: the compressed file to write
 */
void write_compressed_file(FILE *fp, compressed_file_t cf);
