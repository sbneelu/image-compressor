/**
 * @brief Convert a pixel to bytes
 *
 * @param pixel: the pixel to convert to bytes
 * @param bytes: the byte array to put the converted pixel into
 * @return the byte array
 */
byte *pixel_to_bytes(pixel_t pixel, byte *bytes);

/**
 * @brief Convert a byte array to a pixel
 *
 * @param bytes: the byte array to convert to a pixel
 * @return the pixel represented by the byte array
 */
pixel_t bytes_to_pixel(byte *bytes);

/**
 * @brief Convert an unsigned integer to bytes
 *
 * @param i: the unsigned integer to convert to a byte array
 * @param bytes: the byte array to put the converted unsigned integer into
 * @return the byte array
 */
byte *unsigned_int_to_bytes(unsigned int i, byte *bytes);

/**
 * @brief Convert a byte array to an unsigned integer
 *
 * @param bytes: the byte array to convert to an unsigned integer
 * @return the unsigned integer represented by the byte array
 */
unsigned int bytes_to_unsigned_int(byte *bytes);

/**
 * @brief Compute the square of the cartesian distance between two pixels.
 *
 * @param a: the first pixel
 * @param b: the second pixel
 * @return the square of the cartesian distance between the two pixels
 */
int square_distance(pixel_t a, pixel_t b);

/**
 * @brief Copy a pixel.
 *
 * @param to: the pixel to copy to
 * @param from: the pixel to copy from
 * @return the pixel copied to
 */
pixel_t pixel_copy(pixel_t to, const pixel_t from);

/**
 * @brief Copy an array of pixels.
 *
 * @param to: the array of pixels to copy to
 * @param from: the array of pixels to copy from
 * @param len: the length of the arrays
 * @return the array of pixels copied to
 */
pixel_t *pixel_array_copy(pixel_t *to, const pixel_t *from, int len);

/**
 * @brief Check if two arrays of pixels are equal.
 *
 * @param a: the first array of pixels
 * @param b: the second array of pixels
 * @param len: the length of the arrays
 * @return true if the arrays are equal, false otherwise
 */
bool pixel_arrays_equal(const pixel_t *a, const pixel_t *b, int len);

/**
 * @brief Check if two arrays of bytes are equal.
 *
 * @param a: the first array of bytes
 * @param b: the second array of bytes
 * @param len: the length of the arrays
 * @return true if the arrays are equal, false otherwise
 */
bool byte_arrays_equal(const byte *a, const byte *b, int len);

/**
 * @brief Copy an array of bytes.
 *
 * @param to: the array of bytes to copy to
 * @param from: the array of bytes to copy from
 * @param len: the length of the arrays
 * @return the array of bytes copied to
 */
byte *byte_array_copy(byte *to, const byte *from, int len);
