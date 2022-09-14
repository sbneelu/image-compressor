/**
 * @brief Free the memory allocated for the image.
 *
 * @param image: the image to free
 */
void free_image(image_t image);

/**
 * @brief Free the memory allocated for the compressed file.
 *
 * @param compressed_file: the compressed file to free
 */
void free_compressed_file(compressed_file_t compressed_file);

/**
 * @brief Copy a pixel.
 *
 * @param to: the pixel to copy to
 * @param from: the pixel to copy from
 */
void pixel_copy(pixel_t to, const pixel_t from);

/**
 * @brief Copy an array of pixels.
 *
 * @param to: the array of pixels to copy to
 * @param from: the array of pixels to copy from
 * @param len: the length of the arrays
 */
void pixel_array_copy(pixel_t *to, const pixel_t *from, unsigned int len);

/**
 * @brief Check if two arrays of pixels are equal.
 *
 * @param a: the first array of pixels
 * @param b: the second array of pixels
 * @param len: the length of the arrays
 * @return true if the arrays are equal, false otherwise
 */
bool pixel_arrays_equal(const pixel_t *a, const pixel_t *b, unsigned int len);

/**
 * @brief Compute the square of the cartesian distance between two pixels.
 *
 * @param a: the first pixel
 * @param b: the second pixel
 * @return the square of the cartesian distance between the two pixels
 */
unsigned int square_distance(pixel_t a, pixel_t b);
