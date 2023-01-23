/*Copyright 2022 Neil Kirby. Not for disclosure. */
/* Julia Pittner */

#include <stdio.h>
#include "invaders.h"
#include "debug.h"
#include "framerate.h"
#include "structs.h"
#include "linkedlist.h"
#include "code.h"
#include "output.h"

/* Prints out alien header */
void print_alien_header(Sim *sim_ptr)
{
	printf("\n");
	printf("%-11s%-2s%-2s%-4s%11s%11s%11s%11s%4s%9.5f\n", "Code", "T", "C", "Pts", "( __X_____,", " __Y_____)", "( __VX____,","__VY____)", "ET=", sim_ptr->ET);
	
}
/*Determines if it is time print when in TEXT mode*/
int ok_to_print(double ET, double delta_time)
{
	int return_value;

	return_value = check_elapsed_time(ET, delta_time);
	if (VERBOSE || return_value == 1 || ET == 0.0)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
/*Determines which kind of output needs to be called. Kirby's code.*/
void master_output(struct Sim *sim_ptr)
{
	if(TEXT) 
	{
		if(ok_to_print(sim_ptr->ET, sim_ptr->delta_time) || DEBUG)
		{
			text_output(sim_ptr);
		}
	}
	if(GRAPHICS)
	{
		graphic_output(sim_ptr);
	}
}

/*Prints out the final output when in TEXT mode and continues to display the graphic for an additional 4 seconds when in GRAPHICS mode. Kirby's code*/
void final_output(struct Sim *sim_ptr)
{
	if(TEXT)
	{
		text_output(sim_ptr);
		if(sim_ptr->alien_data)
		{
			printf("Defeat! Aliens land at ET = %.5lf\n", sim_ptr->ET);
		}
		else 
		{
			printf("Victory! No attackers remain at ET = %.5lf\n", sim_ptr->ET);
		}
		printf("Total score is %d points\n", sim_ptr->score);
	}
	if(GRAPHICS)
	{
		keep_drawing(sim_ptr);
	}
}
/*Prints the text output. Kirby's code*/
void text_output (struct Sim *sim_ptr)
{

	printf("\n");

	if(sim_ptr->alien_data)
	{
		printf("%-10s T C Pts (%9s, %8s) (%9s, %9s) ET=%9.5lf\n", "Code", "__X____", "__Y____", "__VX____", "__VY____", sim_ptr->ET);
		iterate(sim_ptr->alien_data, print_alien);
	}
	printf("\n");
}
/*Prints the alien data.*/
void print_alien(void *alien) 
{
        struct Alien *AD = alien; 
	int color;
	int type;
	int points;
	
	color = alien_color(AD->A);
	type = alien_type(AD->A);
	points = alien_points(AD->A);
	printf("0x%-9X%-2d%-2d%3d%2s%9.5f%2s%9.5f%2s%9.5f%1s%10.5f%1s\n",AD->A, type, color, points," (",AD->X,", ",AD->Y,")(",AD->VX,",",AD->VY,")");
}
/*Draws all the graphics. Kirby's code.*/
void graphic_output(struct Sim *sim_ptr)
{
	int sim_time = 1000.0 * sim_ptr->ET;
	unsigned int sleep_time = 1000000.0 * sim_ptr->delta_time; 

	sa_clear();

	draw_alien(sim_ptr);
	sa_score(sim_ptr->score);
	sa_time(sim_time);
	sa_refresh();
	microsleep(sleep_time);
}
/*Draws the aliens, base and bolt. Kirby's code.*/
void draw_alien(struct Sim *sim_ptr)
{
	iterate(sim_ptr->alien_data, display_alien);
	base_and_bolt(sim_ptr->ET, sim_ptr->delta_time);
}
/*Assigns each alien to its appropriate color, type, X coordinate and Y coordinate. Kirby's code.*/
void display_alien(void *data)
{
	struct Alien *AD = data;
	sa_alien(AD->type, AD->color, AD->X, AD->Y);
}
/*Draws the base and shoots the bolt at every even second. Kirby's code*/
void base_and_bolt(double ET, double delta_time)
{
	double X = 0.0;

	sa_base(X);

	if(check_elapsed_time(ET, delta_time))
	{
		sa_bolt(X);
	}
}
/*Displays the graphics for an additional 4 seconds. Kirby's code*/
void keep_drawing(struct Sim *sim_ptr)
{
	double delay_time = sim_ptr->ET + SIMDELAY;

	while(delay_time > sim_ptr->ET)
	{
		graphic_output(sim_ptr);
		delay_time -= sim_ptr->delta_time;
	}
}
