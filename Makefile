DEBUG_FLAGS=-fsanitize=address -fsanitize=undefined -g -fno-omit-frame-pointer -Wall -pedantic

SHARED_SOURCE_FILES=fileio.c image.c
SHARED_OBJECT_FILES=fileio.o image.o

KMEANS_COMPRESSOR_SOURCE_FILES=compressors/kmeans/compressor.c compressors/kmeans/kmeans.c compressors/kmeans/utils.c
KMEANS_COMPRESSOR_OBJECT_FILES=compressor.o kmeans.o utils.o

all:
	make kmeans

sane:
	make kmeans-sane

kmeans:
	make kmeans-compress
	make kmeans-decompress

kmeans-sane:
	make kmeans-compress-sane
	make kmeans-decompress-sane

kmeans-compress: ${SHARED_SOURCE_FILES} ${SHARED_HEADER_FILES}
	gcc -c compress.c ${SHARED_SOURCE_FILES} ${KMEANS_COMPRESSOR_SOURCE_FILES}
	gcc -o compress compress.o ${SHARED_OBJECT_FILES} ${KMEANS_COMPRESSOR_OBJECT_FILES}

kmeans-decompress: ${SHARED_SOURCE_FILES} ${SHARED_HEADER_FILES}
	gcc -c decompress.c ${SHARED_SOURCE_FILES} ${KMEANS_COMPRESSOR_SOURCE_FILES}
	gcc -o decompress decompress.o ${SHARED_OBJECT_FILES} ${KMEANS_COMPRESSOR_OBJECT_FILES}

kmeans-compress-sane: ${SHARED_SOURCE_FILES} ${SHARED_HEADER_FILES}
	gcc -c compress.c ${SHARED_SOURCE_FILES} ${KMEANS_COMPRESSOR_SOURCE_FILES} ${DEBUG_FLAGS}
	gcc -o compress compress.o ${SHARED_OBJECT_FILES} ${KMEANS_COMPRESSOR_OBJECT_FILES} ${DEBUG_FLAGS}

kmeans-decompress-sane: ${SHARED_SOURCE_FILES} ${SHARED_HEADER_FILES}
	gcc -c decompress.c ${SHARED_SOURCE_FILES} ${KMEANS_COMPRESSOR_SOURCE_FILES} ${DEBUG_FLAGS}
	gcc -o decompress decompress.o ${SHARED_OBJECT_FILES} ${KMEANS_COMPRESSOR_OBJECT_FILES} ${DEBUG_FLAGS}

clean:
	rm -f *.o
	rm -f compress
	rm -f decompress
