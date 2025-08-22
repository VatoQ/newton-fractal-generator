#ifndef WRITE_CSV_H
#define WRITE_CSV_H

#include "color.h"

int write_csv(const char* filename, 
              Color* matrix,
              int width,
              int height);

#endif
