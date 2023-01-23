/*Copyright 2022 Neil Kirby. Not for disclosure.*/
/*Julia Pittner*/

#include <stdio.h>
#include <stdlib.h>
#include "altmem.h"
#include "structs.h"
#include "debug.h"

/* Allocates memeory for one alien. Kirby's code. */
struct Alien *allocate_alien()
{
	static int allocations;
	struct Alien *alien_ptr = alternative_calloc(1, sizeof(struct Alien));
	if(alien_ptr == NULL)
	{
		printf("ERROR:allocate_alien: failed to allocate\n");
	}
	else
	{
		++allocations;
		if (TEXT) printf("allocate_alien: %d allocated.\n",allocations);
	}
	return alien_ptr;
}
/* Frees the memory for one alien */
void free_alien(void *alien) 
{
	static int freed;
	alternative_free(alien);
	freed++;
	printf("free_alien: %d freed\n", freed);
}
