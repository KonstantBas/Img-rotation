#include "bmp.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define bBC  24
#define bT  0x4D42

uint32_t getPadding(const uint64_t w) {
    const size_t widthSize = w * sizeof(struct pixel);
    if (widthSize % 4 == 0) return 0;
    return 4 - (widthSize % 4);
}

bool from_bmp(FILE* in, struct image* img) {
    struct bmp_header header = {0};
    const uint32_t hSize = sizeof(struct bmp_header);
    const uint32_t pSize = sizeof(struct pixel);
    if (fread(&header, hSize, 1, in) < 1) {
        if (feof(in)) return false;
        return false;
    }
    if (fseek(in, header.bOffBits, SEEK_SET) != 0) return false;
    if (header.biBitCount != bBC) return false;
    if (header.bfType != bT) return false;

    img->height = header.biHeight;
    img->width = header.biWidth;

    size_t size = img->width * img->height * pSize;
    img->data = malloc(size);

    const uint32_t padding = getPadding(img->width);
    for (size_t j = 0; j < img->height; j++)
    {
        if (fread(img->data + j * img->width, pSize, img->width, in) < pSize) return false;
        if (fseek(in, padding, SEEK_CUR) != 0) return false;
    }
    if (fseek(in, 0, SEEK_SET) != 0) return false;
    return true;
}

bool to_bmp(FILE* out, struct image const* img) {

    size_t imgSize = (sizeof(struct pixel) * img->width + img->width % 4) * img->height;
    size_t bfileSize = sizeof(struct bmp_header) + imgSize;
    struct bmp_header header =
            {
                    .bfType = bT,
                    .biBitCount = bBC,
                    .biHeight = img->height,
                    .biWidth = img->width,
                    .bOffBits = sizeof(struct bmp_header),
                    .bfileSize = bfileSize,
                    .biSizeImage = img->width * img->height * sizeof(struct pixel),
                    .biSize = 40,
                    .biPlanes = 1
            };
    size_t tmp = fwrite(&header, sizeof(struct bmp_header), 1, out);
    if (tmp != 1){ return false; }
    const uint32_t hSize = sizeof(struct bmp_header);
    const uint32_t pSize = sizeof(struct pixel);

    if (fwrite(&header, hSize, 1, out) < 1) return false;

    char paddingBytes[3] = {0};
    const uint32_t padding = getPadding(img->width);

    for (size_t j = 0; j < img->height; j++) {
        if (fwrite(img->data + j * img->width, pSize, img->width, out) != img->width) return false;
        if (fwrite(paddingBytes, padding, 1, out) != 1 && padding != 0) return false;
        if (fflush(out) != 0) return false;
    }
    if (fseek(out, 0, SEEK_SET) != 0) return false;
    return true;
}
