/*Julia Pittner*/
#include <stdio.h>
#include "altmem.h"
#include "debug.h"
#include "node.h"
#include "linkedlist.h"

/*Iterates through the linked list and passes each node's data to the ActionFunction*/
void iterate(void *head, ActionFunction doThis)
{
	struct Node *p = head;
	while(p != NULL)
	{
		doThis(p->data);	
		p = p->next;
	}
}

/*Iterates through the linked list and passes each node's data to the CriteriaFunction*/
int any(void *head, CriteriaFunction yes, void *helper)
{
	struct Node *p = head;
	while(p != NULL)
	{
		if (yes(p->data, NULL))
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

/*Allocates memory for a node*/
static struct Node *allocateNode()
{
	struct Node *dynamic = alternative_calloc(1, sizeof(struct Node));
	static int allocations = 0;
	
	if(dynamic)
	{
		allocations++;
		if(TEXT)printf("allocateNode: %d allocated\n", allocations);
	}
	else 
	{
		if(TEXT)printf("ERROR:allocateNode: failed to allocate\n");
		/*alternative_free(dynamic);*/
	}
	return dynamic;
}

/*Inserts a node in the appropriate place in the linked list*/
int insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, int text)
{
	struct Node *newNode;
	struct Node **p = p2head;
	/*newNode = allocateNode();
	newNode->data = data;*/
	if(newNode = allocateNode())
	{
		newNode->data = data;
	
		while(*p != NULL && (goesInFrontOf((**p).data, newNode->data)))
		{
			p = &((**p).next);
		}
			newNode->next = *p;
			*p = newNode;
			return 1;
	}
	

		alternative_free(newNode);
		return 0;
	
}

/*Deletes the appropriate node from the linked list*/
int deleteSome(void *p2head, CriteriaFunction mustGo, void *helper, ActionFunction disposal, int text)
{
	struct Node **p = p2head;
	struct Node *temp;
	if(*p != NULL && (mustGo((**p).data, NULL)))
	{
		disposal((**p).data);
		temp = *p;
		*p =(*p)->next;
		alternative_free(temp);
		return 1;
	}
	return 0;
}







