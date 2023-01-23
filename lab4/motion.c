/*Copyright 2022 Neil Kirby. Not for disclosure.*/
/* Julia Pittner */
#include "debug.h"
#include "framerate.h"
#include "motion.h"
#include "output.h"
#include <stdio.h>

/* Updates the value of X using given formula */
double change_X(double X, double  VX, double delta_time)
{
	 double new_X; 
	 new_X = X + VX * delta_time;
	 return new_X;
}

/* Updates the value of VX based off of current X and VX and also outprints the necessary message */
double change_VX(int A, double X, double Y, double VX)
{
	if(X >= 39.0 & VX > 0.0)
	{
		VX = -(VX);
		printf("\nAlien 0x%-7X at (%9.5f, %9.5f) changes VX to %.5f\n", A, X, Y, VX); 
	}
	if(X <= -39.0 & VX < 0.0)
	{
		VX = -(VX);
		printf("\nAlien 0x%-7X at (%9.5f, %9.5f) changes VX to %+.5f\n", A, X, Y, VX);
	}

	return VX;
}
 
/* Updates the value of Y using given formula */
double change_Y(double X, double Y, double VY, double delta_time, unsigned int code)

{

	double new_Y;
	new_Y = Y + VY * delta_time;
	if(new_Y <= 0.0)
	{
		new_Y = 0.0;
		if(TEXT) printf("\nAlien 0x%08X touches down at X=%9.5lf!\n", code, X);
	}

	return new_Y;

}

