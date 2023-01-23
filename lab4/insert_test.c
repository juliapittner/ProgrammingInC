
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	struct Node *next;
	int data;
	}Node;

int main()
{
	int len, i;
	struct Node *head, *newNode, *secondNode;
	printf("Enter a length for the linked list: ");

	scanf("%d", &len);

	for(i = 0; i < len;  i++)
	{
		int num;
		newNode =(Node *) malloc(sizeof(Node));
		printf("Enter a number: ");
		scanf("%d", &num);
		
		newNode->data = num;

		if (i == 0)
		{
			secondNode = newNode;
			head = secondNode;
		}
		else
		{
			secondNode->next = newNode;
			secondNode = newNode;
		}
	}

	secondNode = head;
	while(secondNode != NULL)
	{
		printf("%d\n", secondNode->data);
		secondNode = secondNode->next;
	}
	return 0;
}
