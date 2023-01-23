/* Julia Pittner */
#include <stdio.h>
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Sim{
	void *alien_data;
	double ET, base, delta_time;
	int score;
	FILE *input;
	int argc;
	char **argv;
}Sim;

typedef struct Alien{
	double X,Y,VX,VY;
	unsigned int A;
	int color,type,points;
	struct Sim *sim_ptr;
}Alien;

#endif
