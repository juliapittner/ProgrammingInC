/*Copyright 2022 Neil Kirby. Not for disclosure*/
/* Julia Pittner */

#include "framerate.h"
#include "debug.h"
#include "code.h"
#include <stdio.h>

/* Determines the alien's color using the alien data(hex code). */
int alien_color(unsigned int alien_code)
{
	int color_value;

	color_value = extract_bits(alien_code, 3, 5);
	if(DEBUG) printf("alien_color: isolating 3 bits after shifting 5 on %X gives %i\n", alien_code, color_value);
	return color_value;
}

/* Determines the alien's type using the alien data(hex code). */
int alien_type(unsigned int alien_code)
{
	int type_value;

	type_value = extract_bits(alien_code, 3, 13);
	if(DEBUG) printf("alien_type: isolating 3 bits after shifting 12 on %X gives %i\n", alien_code, type_value);
	return type_value;
}

/* Determines the alien's points given the alien data(hex code). */
int alien_points(unsigned int alien_code)
{
	int points_value;

	points_value = extract_bits(alien_code, 9, 21);
	if(DEBUG) printf("alien_points: isolating 9 bits after shifting 20 on %X gives %i\n", alien_code, points_value);
	return points_value;
}

/*Masks the number of bits and use bitwise operator & to extract the bits staeting at a specific position */  
unsigned int extract_bits(int number, int number_bits, int position)
{
	return (((1 << number_bits) - 1) & (number >> (position - 1)));
}

/*Compares the elapsed time and runtime. Kirby's code */ 
int check_elapsed_time(double ET, double delta_time)
{
	int cur, prev, return_value;	
	 cur =  ET;

	
	prev =  ET - delta_time;
	

	return_value = ((ET == 0.0) || (cur != prev));
	
	
	if (DEBUG) printf("check_elapsed_time: cur = %i, prev = %i, elapsed_time = %f: returning 1\n",cur, prev, ET);
	return return_value;

}
