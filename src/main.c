#include <string.h>
#include <errno.h>

#include "bmp.h"
#include "transform.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source> <dest> <transformation>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        fprintf(stderr, "Failed to open input file\n");
        return ENOENT;
    }

    struct image img;
    enum read_status read_status = from_bmp(in, &img);
    fclose(in);

    if (read_status != READ_OK) {
        return ENOMEM;
    }

    struct image transformed;
    if (strcmp(argv[3], "none") == 0) {
        transformed = img;
        FILE *out = fopen(argv[2], "wb");
        if (!out) {
            fprintf(stderr, "Failed to open output file\n");
            exit(EXIT_FAILURE);
        }
        if (to_bmp(out, &transformed) != WRITE_OK) {
            fprintf(stderr, "Failed to write BMP\n");
            exit(EXIT_FAILURE);
        }
        fclose(out);

        destroy_image(&img);
        return EXIT_SUCCESS;
    } else if (strcmp(argv[3], "cw90") == 0) {
        transformed = rotate_cw90(&img);
    } else if (strcmp(argv[3], "ccw90") == 0) {
        transformed = rotate_ccw90(&img);
    } else if (strcmp(argv[3], "fliph") == 0) {
        transformed = flip_h(&img);
    } else if (strcmp(argv[3], "flipv") == 0) {
        transformed = flip_v(&img);
    } else {
        fprintf(stderr, "Unsupported transformation: %s\n", argv[3]);
        destroy_image(&img);
        return ENOENT;
    }

    FILE *out = fopen(argv[2], "wb");
    if (!out) {
        fprintf(stderr, "Failed to open output file\n");
        exit(EXIT_FAILURE);
    }
    if (to_bmp(out, &transformed) != WRITE_OK) {
        fprintf(stderr, "Failed to write BMP\n");
        exit(EXIT_FAILURE);
    }
    fclose(out);

    destroy_image(&transformed);
    if (transformed.data != img.data) {
        destroy_image(&img);
    }
    return EXIT_SUCCESS;
}
