#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

struct Node
{
	int pow,coeff;
	struct Node *next;
	
};

struct Node* createNode()
{
	struct Node *n;
	n = (struct Node*)(malloc(sizeof(n)));
	n->next = NULL;
	return n;
}

struct Node *head1;
struct Node *head2;
struct Node *head3;
struct Node *head4;


int viewList(struct Node *head,int s,int number)
{
	if(head == NULL)
	{
		printf("0\n");
	}
	
	else
	{
		struct Node *temp;
		temp = head;
		while(temp!= NULL)
		{
			if(temp->coeff<0)
			{
				if (temp->pow != 0) printf("%dx^%d ",temp->coeff,temp->pow);
				else printf("%d ",temp->coeff);
			}
			
			else 
			{
				if (temp->pow != 0) printf("+ %dx^%d ",temp->coeff,temp->pow);
				else printf("+%d ",temp->coeff);
			}
			s+=temp->coeff*(pow(number,temp->pow));
			temp = temp->next;
		}
	}
	printf("\n");
	return s;
}

void Ins_Beg(int pow,int coeff,int para)
{
	struct Node **head;
	
	if(para == 1) head = &head1;
	if(para == 2) head = &head2;
	if(para == 3) head = &head3;
	if(para == 4) head = &head4;
	
	if (coeff != 0)
	{
	struct Node *p;
	p = createNode();
	
	p->pow = pow; 	
	p->coeff = coeff;
	
	if (*head == NULL)
	{
		*head = p;
		
	}
	
	else
	{
		struct Node *temp;
		
		temp = *head;
		*head = p;
		p->next = temp;
		
	}

	}
}


void Free_Fire(struct Node *head)
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
	struct Node *t1;
	struct Node *t2;
	struct Node *temp;
	struct Node *p;
	
	int i,n1,n2,coef,po,tc,s1,s2,s3,s4,number;
	
	scanf("%d",&tc);
	
	while(tc--)
	{
		s1 = 0;
		s2 = 0;
		s3 = 0;
		s4 = 0;
		
		head1 = NULL;
		head2 = NULL;
		head3 = NULL;
		head4 = NULL;
	
		
		scanf("%d",&n1);
		
		for(i = 0;i<=n1;i++)
		{
			po = n1-i;
			scanf("%d",&coef);
			
			Ins_Beg(po,coef,1);
			
		}
		
		scanf("%d",&n2);
		
		for(i = 0;i<=n2;i++)
		{
			po = n2-i;
			scanf("%d",&coef);
			
			Ins_Beg(po,coef,2);
		}
		
		scanf("%d",&number);
		t1 = head1;
		t2 = head2;
		
		while(t1 != NULL || t2 != NULL)
		{
			if (t1 != NULL && t2 != NULL)
			{
				if (t1->pow == t2->pow)
				{
					coef = t1->coeff + t2->coeff;
					
					Ins_Beg(t1->pow,coef,3);
					t1= t1->next;
					t2 = t2->next;
				}
				
				else if(t1->pow < t2->pow)
				{
					coef = t1->coeff;
					Ins_Beg(t1->pow,coef,3);
					t1 = t1->next;
				}
				
				else if(t2->pow < t1->pow)
				{
					coef = t2->coeff;
					Ins_Beg(t2->pow,coef,3);
					t2 = t2->next;
				}
			}
			
			else if(t1 == NULL)
			{
				coef = t2->coeff;
				Ins_Beg(t2->pow,coef,3);
				t2 = t2->next;
			}
			
			else if(t2 == NULL)
			{
				coef = t1->coeff;
				Ins_Beg(t1->pow,coef,3);
				t1 = t1->next;
			}
			
		}
		
		t1 = head1;
		t2 = head2;
		
		while(t1 != NULL || t2 != NULL)
		{
			
			if (t1 != NULL && t2 != NULL)
			{
				if (t1->pow == t2->pow)
				{
					coef = t1->coeff - t2->coeff;
					
					Ins_Beg(t1->pow,coef,4);
					t2 = t2->next;
					t1 = t1->next;
					
				}
				
				else if(t1->pow < t2->pow)
				{
					coef = t1->coeff;
					Ins_Beg(t1->pow,coef,4);
					t1 = t1->next;	
				}
				
				else if(t2->pow < t1->pow)
				{
					coef = t2->coeff;
					Ins_Beg(t2->pow,-coef,4);
					t2 = t2->next;
				}
			}
			
			else if(t1 == NULL)
			{
				coef = t2->coeff;
				Ins_Beg(t2->pow,-coef,4);
				t2 = t2->next;
			}
			
			else if(t2 == NULL)
			{
				coef = t1->coeff;
				Ins_Beg(t1->pow,coef,4);
				t1 = t1->next;
			}
			
		}
		printf("P1(x) : ");
		s1 = viewList(head1,0,number);
		printf("P2(x) : ");
		s2 = viewList(head2,0,number);
		printf("P3(x) : ");
		s3 = viewList(head3,0,number);
		printf("P4(x) : ");
		s4 = viewList(head4,0,number);
		
		printf("P(%d) = %d\n",number,s1);
		printf("P(%d) = %d\n",number,s2);
		printf("P(%d) = %d\n",number,s3);
		printf("P(%d) = %d\n",number,s4);
		
		Free_Fire(head1);
		Free_Fire(head2);
		Free_Fire(head3);
		Free_Fire(head4);
	}
	
}
