#pragma once

/**
 * @brief Performs the k-means clustering algorithm on an array of pixels.
 *
 * @param pixels: the array of pixels to cluster
 * @param num_of_pixels: the number of pixels in the array
 * @param k: the number of clusters to create
 * @param max_iterations: the maximum number of iterations to run the algorithm for
 * @param allocations: an array of ints to store the cluster allocations in
 * @param centroids: an array of pixels to store the centroids in
 *
 * @return the cost of the allocation (the sum of square distances from each pixel to its centroid)
 */
unsigned long long kmeans(
    const pixel_t *pixels, unsigned int num_of_pixels,
    unsigned int k,
    unsigned int max_iterations,
    unsigned int *assignments, pixel_t *centroids);

/**
 * @brief Determine the next value of k to try in the k-means algorithm.
 *
 * @param k a pointer to the current value of k
 * @param min_k the minimum value of k to try
 * @param max_k the maximum value of k to try
 * @param attempts the attempts made so far
 * @param costs the costs of the previous attempts
 * @param len the length of the attempts and costs arrays
 * @return true if the optimum value of k was found and the algorithm has finished, false otherwise
 */
bool determine_next_k(
    unsigned int *k,
    unsigned int min_k, unsigned int max_k,
    const unsigned int *attempts, const unsigned long long *costs, unsigned int len);

/**
 * @brief Attempt to find the optimum value of k and cluster the given pixels with this value of k using the k-means clustering algorithm.
 *
 * @param pixels the array of pixels to cluster
 * @param num_of_pixels the number of pixels in the array
 * @param min_k the minimum value of k to try
 * @param max_k the maximum value of k to try
 * @param max_attempts_to_optimize_k the maximum number of attempts to make to find the optimum value of k
 * @param max_iterations_per_k the maximum number of iterations to run the k-means algorithm for each value of k
 * @param assignments an array of ints to store the cluster allocations in
 * @param centroids an array of pixels to store the centroids in
 * @param k the value of k that was used (the number of centroids)
 */
void attempt_kmeans(
    const pixel_t *pixels, unsigned int num_of_pixels,
    unsigned int min_k, unsigned int max_k,
    unsigned int max_attempts_to_optimize_k, unsigned int max_iterations_per_k,
    unsigned int *assignments, pixel_t *centroids, unsigned int *k);
