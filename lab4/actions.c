/*Copyright 2022 Neil Kirby. Not for disclosure*/
/*Julia Pittner*/

#include <stdlib.h>

#include "debug.h"
#include "structs.h"
#include "linkedlist.h"

#include "actions.h"
#include "functions.h"
#include "motion.h"
#include "output.h"
#include "code.h"
/*Checks to see if a even second has passed and if it has delete any aliens that got hit. Kirby's code */
void fight_back(struct Sim *sim_ptr)
{
	void *null_ptr = NULL;
	CriteriaFunction defeatedAlien = &defeated_alien;
	ActionFunction removeAlien = &remove_alien;
	

	if(check_elapsed_time(sim_ptr->ET, sim_ptr->delta_time))
	{
		deleteSome(&sim_ptr->alien_data, defeatedAlien, null_ptr, removeAlien, TEXT);
	}
}

/*Determines whether the fight should continue. Checks to see if the program has reached the end of the list or if any of the aliens are on the ground. Kirby's code*/
int continue_fight(struct Sim *sim_ptr)

{
	CriteriaFunction onGround = &on_ground;
	if(sim_ptr->alien_data == NULL) return 0;

	if( any(sim_ptr->alien_data, onGround, NULL)) return 0;

	return 1;
}
