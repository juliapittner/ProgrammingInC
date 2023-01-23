/*Julia Pittner*/

#include "structs.h"
#include "memory.h"
#include "altmem.h"

int main()
{
	int i;
	struct Alien *AD;
	int numAliens = 5;
	int numAllocated = 0;

	for(i = 0; i < 5; i++)
	{
		AD  = allocate_alien();
		if(AD != NULL)
		{
			numAllocated++;
		}
		printf("Number of aliens allocated: %d\n", numAllocated);
	}
	return 0;
}
