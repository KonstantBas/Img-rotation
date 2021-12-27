#include <stdbool.h>
#include <stdio.h>
#include "bmp.h"
#include "rotation.h"



int main( int argc, char** argv )
{
    if (argc != 2) fprintf(stderr, "Usage: ./print_header BMP_FILE_NAME\n");

    FILE *file = fopen(argv[1], "rb");
    struct image img = {0};
    bool comlete = from_bmp(file, &img);
    if (comlete!=true) fprintf(stderr,"Error\n");
    struct image rotated_img = rotate(img);
    fclose(file);
    file = fopen("rotated_picture", "wb");
    comlete = to_bmp(file, &rotated_img);
    if (comlete!=true) fprintf(stderr,"Error\n");

    fclose(file);
    return 0;
}
