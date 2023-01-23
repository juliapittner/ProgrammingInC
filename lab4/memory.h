/* Julia Pittner */

#include "structs.h"

#ifndef MEMORY_H
#define MEMORY_H

struct Alien *allocate_alien();

void free_alien(void *alien);

#endif
