/* Julia Pittner */

#include "structs.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int goesInFrontOf(void *data1, void *data2);
int always_true(void *data, void *helper);
int on_ground(void *alien, void *helper);
void move_aliens(void *alien);
int saucer_over_edge(void *alien, void *helper);
void sub_from_Y(void *alien);
int defeated_alien(void *alien, void *helper);
void remove_saucer(void *data);
void remove_alien(void *alien);


#endif
