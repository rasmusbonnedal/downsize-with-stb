#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <memory.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    char *out_ext = strrchr(argv[2], '.');
    if (!out_ext || strcmp(out_ext, ".png")) {
        printf("Error: Only .png output file format supported\n");
        return 1;
    }

    int x, y, n;
    unsigned char *data = stbi_load(argv[1], &x, &y, &n, 0);
    if (data == 0) {
        printf("Error opening %s\n", argv[1]);
        return 1;
    }
    printf("Loaded %s\n", argv[1]);
    int out_x = 1024;
    int out_y = 1024;
    unsigned char *output = (unsigned char*) malloc(out_x * out_y * n);
    stbir_resize_uint8(data, x, y, 0, output, out_x, out_y, 0, n);

    int result = stbi_write_png(argv[2], out_x, out_y, n, output, 0);
    if (result == 0) {
        printf("Error writing %s\n", argv[2]);
    } else {
        printf("Wrote %s\n", argv[2]);
    }

    stbi_image_free(data);
    free(output);
    return 0;
}
