#pragma once

/**
 * @brief Compress an image
 * 
 * @param image: the image to compress
 * @return the compressed file of the image
 */
compressed_file_t compress(image_t image);

/**
 * @brief Decompress an image
 * 
 * @param compressed_file: the compressed file to decompress
 * @return the decompressed image
 */
image_t decompress(compressed_file_t compressed_file);
