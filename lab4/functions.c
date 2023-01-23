/*Copyright 2022 Neil Kirby. Not for disclosure*/
/* Julia Pittner */
#define SAUCER 3
#define LEFTEDGE -39.0
#define RIGHTEDGE 39.0
#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"
#include "invaders.h"
#include "structs.h"
#include "debug.h"
#include "structs.h"
#include "motion.h"
#include "code.h"
#include "functions.h"
#include "memory.h"
/* Comparision function that determines which alien should go in the list first */
int goesInFrontOf(void *data1, void *data2) 
{
	Alien *alien1 = (Alien *) data1;
	Alien *alien2 = (Alien *) data2;
	return alien1->Y > alien2->Y;
}
int always_true(void *data, void *helper)
{
	return 1;
}
/* Floors Y to 0 */ 
int on_ground(void *alien, void *helper)
{
	struct Alien *AD = alien;
	if(AD->Y > 0.0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/* Moves the aliens and updates its coordinates */
void move_aliens(void *alien)
{
	struct Alien *AD = alien;
	AD->X = change_X(AD->X, AD->VX, AD->sim_ptr->delta_time);
	AD->Y = change_Y(AD->X, AD->Y, AD->VY, AD->sim_ptr->delta_time, AD->A);
	if(AD->type == SAUCER)return;
	
	if((AD->X >= 39.0 && AD->VX > 0.0)||(AD->X <= 39.0 && AD->VX < 0.0))
	{
		AD->VX = -(AD->VX);
		sub_from_Y(AD);
	}	
}

/* Determines if alien is a saucer and if it is over the edge */
int saucer_over_edge(void *alien, void *helper)
{
	struct Alien *AD = alien;
	if((AD->type == SAUCER)&&((AD->X <= LEFTEDGE && AD->VX < 0.0) || (AD->X >= RIGHTEDGE && AD->VX > 0.0)))
	{
		 return 1;	
	}
	else
	{
		return 0;
	}
}
/* Determines if the alien gets hit by the bolt and dies */
int defeated_alien(void *alien, void *helper)
{
	struct Alien *AD = alien;
	int base = AD->sim_ptr->base;
	int X =  AD->X;
	if(base == X)
	{
	return 1;

	}
	else
	{
		return 0;
	}
}
/*Removes the flying saucer and frees the memory. Kirby's code*/
void remove_saucer(void *data)
{
	struct Alien *AD = data;
	{
		if(TEXT)
		{
	printf("Flying saucer worth %i points escapes at ET = %f\n", AD->points, AD->sim_ptr->ET);
		}
		if(GRAPHICS)
		{
			sa_status("Flying saucer escapes!");
		}
		free_alien(AD);
	}
	
}

/* Removes the alien and frees the memory. Kirby's code*/
void remove_alien(void *alien)
{
	struct Alien *AD = alien;
	if(TEXT)
	{
		printf("Bolt hits alien at (%.51f, %.5lf), scores %d points!\n", AD->X, AD->Y, AD->points);
	}
	if(GRAPHICS)
	{
		sa_status("Bolt hits alien!");
	}
	AD->sim_ptr->score += AD->points;
	free_alien(AD);

	
}
/* Subtracts 3 from Y if the alien gets too close to the edge */
void sub_from_Y(void *alien)
{
	struct Alien *AD = alien;
	AD->Y = AD->Y - 3.0;
	if(AD->Y < 0.0)
	{
		AD->Y = 0.0;
	}
	printf("Alien %lf drops to (%lf, %lf), VX to %lf at ET %lf", AD->A, AD->X, AD->Y, AD->VX, AD->sim_ptr->ET);

}

