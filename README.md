# Image compressor

An image compressor which can easily be extended to add additional compression algorithms.

The compressor only supports the PNG format at the moment but work is in progress to support more formats.

## Setup

### Dependencies

- [gcc](https://gcc.gnu.org/) (can be interchanged with another similar C compiler such as [clang](https://clang.llvm.org/))
- [libpng](http://www.libpng.org/pub/png/libpng.html)

### Building

If you would like to compile with another compressor such as clang, you can do so by changing the `CC` variable in the `Makefile`.

To build the compressor, run:

```bash
make
```

To build the compressor with debug symbols and sanitizers, run:

```bash
make sane
```

This will create two binaries: `compress` and `decompress`.

## Usage

The compressor contains a `compress` tool which converts images to a custom compressed file format, and a `decompress` tool which converts the compressed file back to an image.

### Compression

To compress an image, run:

```bash
./compress <input file> <output file> <format identifier> [<format-specific arguments>]
```

See the [Compression Formats](#compression-formats) section for more information on the format identifier and format-specific arguments.

### Decompression

To decompress a compressed file back into an image, run:

```bash
./decompress <input file> <output file>
```

This will automatically detect the compression format used and decompress the image.

## Compressed File Format

The first 4 bytes of the compressed file are the format identifier. The rest of the file is the compressed data. See the [Compression Formats](#compression-formats) section for more information on the format identifier and the way compressed data is structured for each format.

## Compression Formats

### Simple k-means

Format identifier: `KMNS`

Format-specific arguments:

1. `max_iterations`: The maximum number of iterations to run the k-means algorithm for.
2. `k`: The number of clusters to use. This will also be the number of colors in the output image.

#### Description

This uses a simple [k-means clustering](TODO) based algorithm to compress the image. It takes in the value for `k` and does not try to optimize it. It also takes in the maximum number of iterations to run the algorithm for. If the algorithm converges before the maximum number of iterations, it will stop early.

#### Compressed data structure

The compressed data is as follows:

- The first 4 bytes are the image width.
- The next 4 bytes are the image height.
- The next byte is k (the number of clusters).
- The next 3k bytes are the colors of each cluster. Each color is represented by 3 bytes, one for each channel (red, green, blue).
- The rest of the file is the compressed image data. Each pixel is represented by 1 byte, which is the index of the cluster it belongs to.

This can be visualized as follows:

```txt
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
  0 |       Width       |       Height      | k |R1 |G1 |B1 |R2 |G2 |
  1 |B2 |R3 |B3 |G3 |                      ...                      |
    |                             ...                               |
    |                        ...                        |Rk |Gk |Bk |
    |i1 |i2 |i3 |i4 |i5 |i6 |                 ...                   |
```

This means that the compressed data is 9 + 3k + width x height bytes long, so the total compressed file is 13 + 3k + width x height bytes long.

### Advanced k-means

Work in progress...

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
