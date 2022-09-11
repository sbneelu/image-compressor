/**
 * @brief Convert a pixel to bytes
 * 
 * @param pixel: the pixel to convert to bytes
 * @param bytes: the byte array to put the converted pixel into
 */
void pixel_to_bytes(pixel_t pixel, byte *bytes);

/**
 * @brief Convert a byte array to a pixel
 * 
 * @param bytes: the byte array to convert to a pixel 
 * @return the pixel represented by the byte array
 */
pixel_t bytes_to_pixel(byte *bytes);

/**
 * @brief Convert an integer to bytes
 * 
 * @param i: the integer to convert to a byte array
 * @param bytes: the byte array to put the converted integer into
 */
void int_to_bytes(int i, byte *bytes);

/**
 * @brief Convert a byte array to an integer
 * 
 * @param bytes: the byte array to convert to an integer
 * @return the integer represented by the byte array
 */
int bytes_to_int(byte *bytes);
