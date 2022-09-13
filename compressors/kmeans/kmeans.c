#include <stdio.h> // TODO Remove this
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../../shared.h"
#include "../../image.h"
#include "kmeans.h"

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
    const pixel_t *pixels, int num_of_pixels,
    int k,
    int max_iterations,
    byte *assignments, pixel_t *centroids)
{
    for (int i = 0; i < k; i++)
        pixel_copy(centroids[i], pixels[rand() % num_of_pixels]);
    pixel_t *prev_centroids = malloc(sizeof(pixel_t) * k);
    for (int i = 0; i < k; i++)
        prev_centroids[i] = malloc(sizeof(struct pixel));

    for (int i = 0; i < max_iterations; i++)
    {
        pixel_array_copy(prev_centroids, centroids, k);

        // For each pixel find the nearest centroid
        for (int j = 0; j < num_of_pixels; j++)
        {
            pixel_t pixel = pixels[j];
            int min_distance = INT_MAX;
            byte min_index = 0;
            for (int l = 0; l < k; l++)
            {
                pixel_t centroid = centroids[l];
                int distance = square_distance(pixel, centroid);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = l;
                }
            }
            assignments[j] = min_index;
        }

        // For each centroid find the new mean of its cluster
        for (byte j = 0; j < k; j++)
        {
            int num_of_pixels_in_cluster = 0;
            int r = 0;
            int g = 0;
            int b = 0;
            for (int l = 0; l < num_of_pixels; l++)
            {
                if (assignments[l] == j)
                {
                    num_of_pixels_in_cluster++;
                    r += pixels[l]->r;
                    g += pixels[l]->g;
                    b += pixels[l]->b;
                }
            }
            if (num_of_pixels_in_cluster > 0)
            {
                centroids[j]->r = r / num_of_pixels_in_cluster;
                centroids[j]->g = g / num_of_pixels_in_cluster;
                centroids[j]->b = b / num_of_pixels_in_cluster;
            }
        }

        // Check whether the centroids have settled and break early if so
        if (pixel_arrays_equal(prev_centroids, centroids, k))
            break;
    }

    // Calculate cost function
    unsigned long long cost = 0;
    for (int i = 0; i < num_of_pixels; i++)
    {
        pixel_t pixel = pixels[i];
        pixel_t centroid = centroids[assignments[i]];
        int distance = square_distance(pixel, centroid);
        if (cost + distance < cost)
            cost = ULLONG_MAX;
        else
            cost += distance;
    }

    for (int i = 0; i < k; i++)
        free(prev_centroids[i]);
    free(prev_centroids);

    return cost;
}

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
    int *k,
    int min_k, int max_k,
    const int *attempts, const unsigned long long *costs, int len)
{
    if (len == 0)
        return false;
    else
    {
        // TODO
        *k = attempts[len - 1];
        return false;
    }
}

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
    const pixel_t *pixels, int num_of_pixels,
    int min_k, int max_k,
    int max_attempts_to_optimize_k, int max_iterations_per_k,
    byte *assignments, pixel_t *centroids, int *k)
{
    int *attempts = malloc(sizeof(int) * max_attempts_to_optimize_k);
    unsigned long long *costs = malloc(sizeof(unsigned long long) * max_attempts_to_optimize_k);

    if (min_k > num_of_pixels)
        min_k = num_of_pixels;

    if (max_k > num_of_pixels)
        max_k = num_of_pixels;

    if (max_k > 255)
        max_k = 255;

    if (min_k > max_k)
        min_k = max_k;

    *k = min_k;

    for (int i = 0; i < max_attempts_to_optimize_k; i++)
    {
        bool finished = determine_next_k(k, min_k, max_k, attempts, costs, i);
        if (finished)
            break;

        unsigned long long cost = kmeans(
            pixels, num_of_pixels,
            *k,
            max_iterations_per_k,
            assignments, centroids);
        attempts[i] = *k;
        costs[i] = cost;
    }

    free(attempts);
    free(costs);
}

kmeans_compressed_image_t compress_with_kmeans(image_t image)
{
    int num_of_pixels = image->width * image->height;
    byte *assignments = malloc(num_of_pixels);
    pixel_t *centroids = malloc(sizeof(pixel_t) * MAX_K);
    int k;

    for (int i = 0; i < MAX_K; i++)
        centroids[i] = malloc(sizeof(struct pixel));

    attempt_kmeans(
        image->pixels, num_of_pixels,
        MIN_K, MAX_K,
        MAX_ATTEMPTS_TO_OPTIMIZE_K, MAX_ITERATIONS_PER_K,
        assignments, centroids, &k);

    kmeans_compressed_image_t compressed_image = malloc(sizeof(struct kmeans_compressed_image));
    compressed_image->width = image->width;
    compressed_image->height = image->height;
    compressed_image->k = k;
    compressed_image->centroids = malloc(sizeof(pixel_t) * k);
    compressed_image->assignments = malloc(num_of_pixels);
    for (int i = 0; i < k; i++)
        compressed_image->centroids[i] = malloc(sizeof(struct pixel));
    pixel_array_copy(compressed_image->centroids, centroids, k);
    for (int i = 0; i < num_of_pixels; i++)
        compressed_image->assignments[i] = assignments[i];

    free(assignments);
    for (int i = 0; i < MAX_K; i++)
        free(centroids[i]);
    free(centroids);

    return compressed_image;
}
