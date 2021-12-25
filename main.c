#include <stdbool.h>
#include <stdio.h>
#include "bmp.h"
#include "rotation.h"


int main( int argc, char** argv )
{
    if (argc != 2) fprintf(stderr, "Usage: ./print_header BMP_FILE_NAME\n");

    FILE *f = fopen(argv[1], "rb");
    if (!f) fprintf(stderr,"Failed to open file\n");
    struct image img = {0};
    bool comlete = from_bmp(f, &img);
    if (comlete!=1) fprintf(stderr,"Error\n");
    struct image rotated_img = rotate(img);
    fclose(f);
    f = fopen("rotated_picture", "wb");
    comlete = to_bmp(f, &rotated_img);
    if (comlete!=1) fprintf(stderr,"Error\n");

    fclose(f);
    return 0;
}
