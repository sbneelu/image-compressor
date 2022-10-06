/**
 * @brief Compress an image using the KMNS (simple k-means) compressor.
 *
 * @param image: the image to compress
 * @param compressed_file: the file to write the compressed image to
 * @param max_iterations: the maximum number of iterations to run the k-means algorithm
 * @param k: the number of clusters to use
 *
 * @return the compressed file
 */
compressed_file_t compress_simple_kmeans(image_t image, compressed_file_t compressed_file, unsigned int max_iterations, int k);

/**
 * @brief Decompress an image using the KMNS (simple k-means) compressor.
 *
 * @param compressed_file: the file to read the compressed image from
 * @param image: the image write the decompressed file to
 * @return the decompressed image
 */
image_t decompress_simple_kmeans(compressed_file_t compressed_file, image_t image);
