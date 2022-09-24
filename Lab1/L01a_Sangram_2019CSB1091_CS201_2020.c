#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


int size = 0;

struct Node
{
	int info;
	struct Node *next;
	
};

struct Node* head = NULL;

struct Node* createNode()
{
	struct Node *n;
	
	n = (struct Node*)(malloc(sizeof(n)));
	
	n->next = NULL;
	size += 1;
	return n;
}

void Ins_Beg(int data)
{
	struct Node *p;
	p = createNode();
	
	p->info = data; 	
	if (head == NULL)
	{
		head = p;
		
	}
	
	else
	{
		struct Node *temp;
		
		temp = head;
		head = p;
		p->next = temp;
		
	}

}


void viewList() 
{	struct Node *temp3;

	if(head== NULL)
	{
		printf("\tEmpty\n");
		
	}
	
	else 
	{
	
		temp3 = head ;
		
		while (temp3 != NULL)
		{
			if(temp3->next !=NULL) printf("%d => ", temp3->info);
			else printf("%d",temp3->info);
			temp3 = temp3->next;
		}
	}
	printf("\n");
}

void Ins_End(int data)
{
	struct Node *p;
	p = createNode();
	
	p->info = data;
	
	
	if(head == NULL)
	{
		head = p;	
	}
	
	else
	{
		struct Node *temp;
	
		temp = head;
	
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
	
			temp->next = p;
	}
	
	
}

void Del_First()
{
	if (head == NULL)
	{
		printf("\tCannot delete as NO nodes in the linked-list \n");
	}
	
	else
	{
		struct Node *temp;
		head = head->next;
		
		size-=1;	
		
	}
	
}

void Del_Last()
{
	if (head == NULL)
	{
		printf("\tCannot delete as NO nodes in the linked-list \n");
	}
	
	else
	{
		struct Node *temp;
		temp = head;
		
		if (head->next == NULL)
		{
			head = NULL;
		}
		else
		{
			while(temp->next->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = NULL;
		}
		
	size -= 1 ;	
	
	}
	
}

void find( int data)
{
	bool present = false;
	int index = 1;
	struct Node *temp;
	temp = head;
	struct Node *x;
	
	if (head != NULL)
	{
		
		while(temp!= NULL && present == false)
		{
			if (temp->info == data)
			{
				present = true;
				x = temp;
				
			}
			else 
			{
				temp = temp->next;
				index+=1;
			}
			
		}
	
	}
	
	if(present == true)
	{	
		printf("\tValue %d node is at position %d in the linked list .\n",data,index);
		printf("\tDifference in its allocated memory to that of cuurent head : %d\n",x - head);
		
		
	}
	else printf("\tCannot find any such node in the linked-list\n");
	
}

void Del_Spec(int data)
{
	bool present = false;
	bool deleted = false;
	struct Node *temp;
	temp = head;
	
	if (head != NULL)
	{
	if (head->info == data )
	{
		
		head = head->next;	
		present = true;
		deleted = true;
		size-=1;
	}

		while(temp->next!= NULL && present == false)
		{
			if (temp->next->info == data)
			{
				present = true;
			}
			
			else temp = temp->next;
				
		}	
	}
	

	if(present == true && deleted == false )
	{
		struct Node *temp1;
		temp1 = temp->next->next;
		temp->next = temp1;
		
		size-=1;
	}
	else printf("\tCannot delete as No such node in the linked-list\n");
}

void Free_Fire()
{
	struct Node *temp;
	struct Node *temp1;
	
	temp = head;
	
	while(temp != NULL)
	{
		temp1 = temp->next;
		free(temp);
		temp = temp1;
	}
	
}

int main()
{
	int quer = -1;
	int num;
	
	while(quer!=0)
	{
		printf("Enter the choice:\n");
		
		scanf("%d",&quer);
		
		if(quer == 0)
		{
			Free_Fire();
			
		}
		
		else if(quer == 1)
		{
			printf("Enter the data value:\n");
			scanf("%d",&num);
			Ins_Beg(num);
		}
		
		else if(quer == 2)
		{
			printf("Enter the data value:\n");
			scanf("%d",&num);
			Ins_End(num);
		}
		
		else if(quer == 3)
		{
			Del_First();
		}
		
		else if(quer == 4)
		{
			Del_Last();
		}
		
		else if(quer == 5)
		{
			printf("Enter the data value:\n");
			scanf("%d",&num);
			Del_Spec(num);
		
			
		}
		
		else if(quer == 6)
		{
			printf("Enter the data value:\n");
			scanf("%d",&num);
			find(num);
		}
		
		else if(quer == 7)
		{
			
			printf("\tSize of the linked-list = %d\n",size);
		}
		
		else if(quer == 8)
		{
			printf("\tlinked-list : ");
			viewList();
		}
		
		else 
		{
			printf("\tWrong Input. \n\tEnter your choice again:\n");
		}
			
	}
	
	return 0;

}

