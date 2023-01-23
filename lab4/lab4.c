/*Copyright 2022 Neil Kirby. Not for disclosure*/
/* Julia Pittner */

#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"
#include "invaders.h"

#include "structs.h"
#include "debug.h"
#include "framerate.h"

#include "actions.h"
#include "functions.h"
#include "memory.h"
#include "motion.h"
#include "output.h"
#include "code.h"

/*Clears the linked list at the end of the program. Kirby's code*/
void clean_world(struct Sim *sim_ptr)
{
	int aliens;

	if(TEXT)
	{
		printf("Clearing the attacking list...\n");
	}
	aliens = deleteSome(&sim_ptr->alien_data, always_true, NULL, free_alien, TEXT);
	if(TEXT)
	{
		printf("    ...%d cleared\n",aliens);
	}
}
/* Runs the simulation. Kirby's code with slight modification. */
void run_sim(struct Sim *sim_ptr)
{
	void *null_ptr = NULL;
	double run_time = 0.0;
	
	ActionFunction moveAliens = &move_aliens;
	CriteriaFunction saucerOverEdge = &saucer_over_edge;
	ActionFunction removeAlien = &remove_alien;
	ActionFunction removeSaucer = &remove_saucer;
		while(continue_fight(sim_ptr)) 
		{
			master_output(sim_ptr);
			sim_ptr->ET += sim_ptr->delta_time;
			iterate(sim_ptr->alien_data, moveAliens);
			fight_back(sim_ptr);
			deleteSome(&sim_ptr->alien_data, saucerOverEdge, null_ptr, removeSaucer, TEXT);
		}			
	final_output(sim_ptr);
	clean_world(sim_ptr);
}

/* Fill in alien structure with alien data */
void fill_alien_struct(Alien *alien, unsigned int A, double X, double Y, double VX, double VY, Sim *sim_ptr)
{
	alien->A = A;
	alien->X = X;
	alien->Y = Y;
	alien->VX = VX;
	alien->VY = VY;
	alien->color = alien_color(alien->A);
	alien->points = alien_points(alien->A);
	alien->type = alien_type(alien->A);
	alien->sim_ptr = sim_ptr;
}

/* Dynamically allocate memory and add alien to list */
void add_alien(unsigned int A, double X, double Y, double VX, double VY, Sim *sim_ptr) 
{
	int inserted;
	Alien *alien = allocate_alien();
	if (alien != NULL)
	{
		fill_alien_struct(alien, A, X, Y, VX, VY, sim_ptr);
	
		inserted = insert(&(sim_ptr->alien_data), alien, goesInFrontOf, TEXT); 	
		if (inserted == 0)
		{
			free_alien(alien);
			printf("ERROR:add_alien: alien not inserted\n");
			
		}
	}
}


/* Reads in the alien data from the input file */
void input_aliens(Sim *sim_ptr)
{
	unsigned int A;
	double X, Y, VX, VY;
	int scanf_input = 5;
	
	while(scanf_input == 5)
	{
		scanf_input = fscanf(sim_ptr->input, "%x %lf %lf %lf %lf", &A, &X, &Y, &VX, &VY);
		
		if (scanf_input == 5) add_alien(A, X, Y, VX, VY, sim_ptr);
	}
	printf("Input terminated: scanf returned %i\n", scanf_input);
}
 

/* Initializes simulation */
void init_sim(int argc, char *argv[])
{
	struct Sim sim_ptr;
	sim_ptr.alien_data = NULL;
	sim_ptr.ET = 0.0;
	sim_ptr.base = 0.0;
	sim_ptr.delta_time = DT;
	sim_ptr.score = 0;
	sim_ptr.input = NULL;
	sim_ptr.argc = argc;
	sim_ptr.argv = argv;
	sim_ptr.input = fopen(sim_ptr.argv[1], "r");
	if(sim_ptr.input != NULL)
	{
		printf("DIAGNOSTIC:Successfully opened %s for input.\n", sim_ptr.argv[1]);
		printf("\n");
		input_aliens(&sim_ptr);
		run_sim(&sim_ptr);
		fclose(sim_ptr.input);
		printf("DIAGNOSTIC:Closed input file %s.\n", sim_ptr.argv[1]);
	}
	else
	{
		printf("ERROR:Unable to open %s for input.\n", sim_ptr.argv[1]);	
	}
}
/*Runs the entire program*/
int main (int argc, char *argv[])
{

	double start_time;
	double end_time;
	double final_time;
	start_time = now();

	if(argc == 0)
	{
		printf("ERROR:main: No command line arguments\n");
	}
	else
	{
		if(TEXT || (GRAPHICS && sa_initialize(4)))
		{
			init_sim(argc, argv);
			if(GRAPHICS) sa_teardown();
		}
		else
		{		
			printf("ERROR:main: Initialization failed\n");
		}	
	}
	end_time = now();
	final_time = end_time - start_time;
	printf("Total runtime is %f seconds\n", final_time); 
	return 0;
}    
