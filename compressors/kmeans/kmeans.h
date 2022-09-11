#pragma once

/*
    STRUCTURE:
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
    |     WIDTH     |     HEIGHT    |
    | K |    C1     |    C2     | C3|
    |  C3   |     C4    |    C5     |
    |            ...                |
    |A1 |A2 |A3 |A4 |A5 |A6 |A7 |A8 |
    |            ...                |

    W: width of the image (4 bytes - int)
    H: height of the image (4 bytes - int)
    K: number of clusters (1 byte - int)
    C: centroid (3 bytes - R, G, B)
    A: assignment (1 byte - index of centroid)

    SIZE: 4 + 4 + 1 + 3K + W*H
*/

struct kmeans_compressed_image
{
    int width;
    int height;
    byte *assignments;
    pixel_t *centroids;
    byte k;
};
/**
 * @brief An image compressed with k-means
 *
 * @param width The width of the image
 * @param height The height of the image
 * @param assignments The assignments of the pixels to the centroids
 * @param centroids The centroids of the image
 * @param k The number of centroids
 */
typedef struct kmeans_compressed_image *kmeans_compressed_image_t;

/**
 * @brief Compresses an image using the k-means algorithm.
 *
 * @param image the image to compress
 * @return the compressed image
 */
kmeans_compressed_image_t compress_with_kmeans(image_t image);
