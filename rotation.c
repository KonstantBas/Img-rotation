#include <malloc.h>
#include <inttypes.h>
#include "rotation.h"
struct image rotate(struct image img){
    const uint64_t width = img.width;
    const uint64_t height = img.height;

    struct image new_img;

    new_img.height = width;
    new_img.width = height;

    size_t size = sizeof(struct pixel) * height * width;
    new_img.data = (struct pixel*)malloc(size);

    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++){
            new_img.data[j * height + i] = img.data[(i + 1) * width - j ];
        }
    }
    return new_img;
}