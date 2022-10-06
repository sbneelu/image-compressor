#pragma once

/**
 * @brief Checks whether the given format identifier is valid
 *
 * @param format_identifier
 * @return true if the format identifier is valid, and false if not
 */
bool is_valid_format(byte format_identifier[4]);

/**
 * @brief Compress an image
 *
 * @param image: the image to compress
 * @param format_identifier: the identifier of the compression format
 * @param argc: the number of arguments
 * @param argv: the arguments
 * @return the compressed file of the image
 */
compressed_file_t compress(image_t image, byte format_identifier[4], int argc, char **argv);

/**
 * @brief Decompress an image
 *
 * @param compressed_file: the compressed file to decompress
 * @param format_identifier: the identifier of the compression format
 * @param argc: the number of arguments
 * @param argv: the arguments
 * @return the decompressed image
 */
image_t decompress(compressed_file_t compressed_file, int argc, char **argv);
