#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define ll long long

int carry = 0;
struct Node
{
	int digit;	
	struct Node* next;
};

struct Node *head;

struct Node* createNode()
{
	struct Node *n;
	n = (struct Node*)(malloc(sizeof(struct Node)));
	n->next = NULL;
	return n;
}

void multiply(struct Node* new_node)
{
	struct Node *temp;
	temp = head;
		
	if(head == NULL) 
	{	
		head = new_node;
		new_node->next = NULL;
	}
	
	else
	{
		
		while(temp->next !=NULL)
		{
			int lol = (temp->digit)*(new_node->digit) + carry;
			
			temp->digit = lol%10;
			carry = lol/10;
			temp = temp->next;
			
		}
		
		int lol = (temp->digit)*(new_node->digit) + carry;
			
		temp->digit = lol%10;
		carry = lol/10;

        struct Node *local;
      
        
		while(carry != 0)	
		{
			local = createNode();
			
			local->digit = carry%10;
			
			carry = carry/10;
			temp->next = local;
			temp = temp->next;
		
		}
	
	}
}

int sizze()
{
	struct Node *temp3;
	int size = 0;
	
	temp3 = head ;
	
	while (temp3 != NULL)
	{
		
		size+=1;

		temp3 = temp3->next;
	}	
	
	return size;
}


void viewList() // printing all the nodes of the list
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
			printf("%d", temp3->digit);

			temp3 = temp3->next;
		}
	}
	printf("\n");
}

void countZeros()
{
	struct Node *temp;
	
	temp = head;
	int count = 0;
	bool  flag = true;
	while(temp!=NULL && flag == true)
	{
		if (temp->digit == 0)count+=1;
		else flag = false;
		temp= temp->next;
	}
	
	printf("%d ",count);
	
}

void reverse() 
{ 
    struct Node* t1 = NULL; 
    struct Node* t2 = head; 
    struct Node* next = NULL; 
    while (t2 != NULL) { 
    
        next = t2->next; 
  
        t2->next = t1; 
        
        t1 = t2; 
        t2 = next; 
    } 
    head = t1; 
} 

void pattern(char *pat, int ram)
{
	//////////////
	int size = 0;
	
	struct Node *temp1;
	temp1 = head;
	while(temp1!= NULL && size < 4)
	{
		size+=1;
		temp1 = temp1->next;
	}
	//////////////
	
	struct Node *temp;
	temp = head;
	
	int ans;
	ans = 0;
	
	
	if(ram == 1)
	{
		if(size>=1)
		{
			int x1 = pat[0] - '0';
			
			while(temp != NULL)
			{
				if (temp->digit == x1) ans+=1;
				temp = temp->next;
			}
		}
	}
	
	else if(ram == 2)
	{
		int x1 = pat[0] - '0';
		int x2 = pat[1] - '0';
		
		if(size > 1)
		{
			while(temp->next != NULL)
			{
				if(temp->digit == x1 && temp->next->digit == x2) ans+=1;
				temp = temp->next;
			}
		}
	}
	
	else if(ram == 3)
	{
		if (size > 2)
		{
			int x1 = pat[0] - '0';
			int x2 = pat[1] - '0';
			int x3 = pat[2] - '0';
	
			while(temp->next->next != NULL)
			{
				
				if(temp->digit == x1 && temp->next->digit == x2 && temp->next->next->digit == x3)
				ans +=1;
				temp = temp->next;
			}
		}
	}
	
	printf("%d ",ans);
	
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
	struct Node *p;
	int i,j,index,size;
	
	int T,n;
	char k[4];
	
	scanf("%d",&T);
	
	
	while(T--)
	{
		head = NULL;
		scanf("%d ",&n);
		
		scanf("%3s",&k);
		
		for(size = 0;size < 5;size++)
		{
			if(k[size] == '\0') break;
			
		}
		
		if(n == 0)
		{
			if (size == 1 && k[0] == '1') printf("0 1 1\n");
			else printf("0 0 1\n");
		}
		
		else 
		{
			
		for (i = 1;i<=n;i++)
		{
			p = createNode();
			p->digit = i;
		
			for (j = 0;j<i;j++)
			{
				multiply(p);
			}
		}
		
		countZeros();
		reverse();
		pattern(k,size);
		viewList();
		Free_Fire();
		
		}
	}

	return 0;
}

