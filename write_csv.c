#include "write_csv.h"
#include <stdio.h>

int write_csv(const char *filename, 
              Color *matrix,
              int width,
              int height)
{
    FILE* fpt;

    fpt = fopen(filename, "w");

    fprintf(fpt, "R;G;B;%d;%d\n", width, height);

    int i;

    for (i = 0; i < width * height; i++)
    {
        Color pixel = matrix[i];

        fprintf(fpt, "%d;%d;%d\n", pixel.r, pixel.g, pixel.b);
    }
    fclose(fpt);

    return 0;
}
