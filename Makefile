CC=gcc
DEBUG_FLAGS=-fsanitize=address -fsanitize=undefined -g -fno-omit-frame-pointer -Wall -pedantic


FILES_SOURCE_FILES=files/files.c
UTILS_SOURCE_FILES=utils/utils.c utils/kmeans/kmeans_utils.c utils/memory/memory_utils.c
COMPRESSOR_SOURCE_FILES=compressor/compressor.c compressor/simple_kmeans/simple_kmeans_compressor.c

SHARED_SOURCE_FILES=$(FILES_SOURCE_FILES) $(UTILS_SOURCE_FILES) $(COMPRESSOR_SOURCE_FILES)
COMPRESS_SOURCE_FILES=compress.c
DECOMPRESS_SOURCE_FILES=decompress.c


FILES_OBJECT_FILES=files.o
UTILS_OBJECT_FILES=utils.o kmeans_utils.o memory_utils.o
COMPRESSOR_OBJECT_FILES=compressor.o simple_kmeans_compressor.o

SHARED_OBJECT_FILES=$(FILES_OBJECT_FILES) $(UTILS_OBJECT_FILES) $(COMPRESSOR_OBJECT_FILES)
COMPRESS_OBJECT_FILES=compress.o
DECOMPRESS_OBJECT_FILES=decompress.o


all: compress decompress
	make compress
	make decompress

sane: compress decompress
	make compress-sane
	make decompress-sane

compress: $(COMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -c $(COMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -o compress $(COMPRESS_OBJECT_FILES) $(SHARED_OBJECT_FILES)

decompress: $(DECOMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -c $(DECOMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -o decompress $(DECOMPRESS_OBJECT_FILES) $(SHARED_OBJECT_FILES)

compress-sane: $(COMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -c $(DEBUG_FLAGS) $(COMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -o compress $(DEBUG_FLAGS) $(COMPRESS_OBJECT_FILES) $(SHARED_OBJECT_FILES)

decompress-sane: $(DECOMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -c $(DEBUG_FLAGS) $(DECOMPRESS_SOURCE_FILES) $(SHARED_SOURCE_FILES)
	$(CC) -o decompress $(DEBUG_FLAGS) $(DECOMPRESS_OBJECT_FILES) $(SHARED_OBJECT_FILES)

clean:
	rm -f *.o
	rm -f compress
	rm -f decompress
