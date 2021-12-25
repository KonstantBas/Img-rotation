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
    from_bmp(f, &img);
    struct image rotated_img = rotate(img);
    fclose(f);
    f = fopen("rotated_picture", "wb");
    to_bmp(f, &rotated_img);

    fclose(f);
    return 0;
}
