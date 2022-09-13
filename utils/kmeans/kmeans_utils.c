#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../../shared.h"
#include "../../files/files.h"
#include "../utils.h"
#include "kmeans_utils.h"


unsigned long long kmeans(
    const pixel_t *pixels, unsigned int num_of_pixels,
    unsigned int k,
    unsigned int max_iterations,
    unsigned int *assignments, pixel_t *centroids)
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


bool determine_next_k(
    unsigned int *k,
    unsigned int min_k, unsigned int max_k,
    const unsigned int *attempts, const unsigned long long *costs, unsigned int len)
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


void attempt_kmeans(
    const pixel_t *pixels, unsigned int num_of_pixels,
    unsigned int min_k, unsigned int max_k,
    unsigned int max_attempts_to_optimize_k, unsigned int max_iterations_per_k,
    unsigned int *assignments, pixel_t *centroids, unsigned int *k)
{
    unsigned int *attempts = malloc(sizeof(int) * max_attempts_to_optimize_k);
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
