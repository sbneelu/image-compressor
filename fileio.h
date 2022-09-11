#pragma once

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
