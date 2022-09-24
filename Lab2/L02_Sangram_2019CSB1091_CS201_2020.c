#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


// Implementation of Stack Using Linked List
// S part
int Z;

struct Node
{
	int data;
	struct Node *next;
};

int size;
struct Node *head;
int sizeq;

struct Node *createNode()
{
	struct Node *p;
	p = (struct Node*)malloc(sizeof(struct Node));
	
	p->next = NULL;
	
	return p;
}


void Ins_Beg(int data)
{
	struct Node *p;
	p = createNode();
	
	p->data = data; 
		
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


void Del_First()
{
	
	if (head == NULL)
	{
		printf("-1");
	}
	
	else
	{
		int temp;
	
		temp = (head)->data;
		head = (head)->next;
		printf("%d ",temp);
		
	}
}
///////////////////////////////////////////

struct Node *front;
struct Node *rear;

void enQ(int data)
{
	struct Node *temp;
	temp = createNode();
	temp->data = data;
	
	if(rear == NULL && front == NULL)
	{
		rear = temp;
		front = temp;
	}
	
	else 
	{
		rear->next = temp;
		rear = temp;
	}
	 
	sizeq +=1;
}

void delQ()
{
	if(sizeq>0)
	{
	
		sizeq-=1;
	
		printf("%d ",front->data);
		front = front->next;
	}
	else printf("-1 ");
}

int golf = 0;
////for I part

int isOperand(char *a)
{
	
	if(a[0] == '-')
	{
		if(a[1] =='0' || a[1] =='1' || a[1] =='2' || a[1] =='3' || a[1] =='4' ||
			a[1] =='5' || a[1] =='6' || a[1] =='7' || a[1] =='8' || a[1] =='9')	
			{
				return 1;
			}
			
		else return 0;
			
	}
	
	else if(a[0] !='0' && a[0] !='1' && a[0] !='2' && a[0] !='3' && a[0] !='4' &&
	a[0] !='5' && a[0] !='6' && a[0] !='7' && a[0] !='8' && a[0] !='9' && a[0]!='-' )
	{
		return 0;
	}

	else return 1;
	
}
char pref[20][3] = {"*","/","%","+","-","<<",">>","<","<=",">",">=",
						"==","!=","&","^","|"};
int preff(char *a)
{
	int i;
	if(a[1] != '=' && a[0] !='<' && a[0]!='>')
	for(i = 0;i<20;i++)
	{
		if(pref[i][0] == a[0])
		return i;
	}
	
	else if(a[0] == '>')
	{
		if(a[1] == '>') return 6;
		else if(a[1] == '=') return 10;
		else return 9;	
	}
	
	else if(a[0] == '<')
	{
		if(a[1] == '<') return 5;
		else if(a[1] == '=') return 8;
		else return 7;
	}
	else if(a[1] == '=')
	{
		if(a[0] == '=') return 11;
		else if(a[0] == '!') return 12;
	
	}
}

int operation(int op1,int op2,char *o)
{

	if(o[0] == '*')
	{
		return op2*op1;
	}
	else if(o[0] == '+')
	{
		return op2 + op1;
	}
	else if(o[0] == '-')
	{
		return op2-op1;
	}
	else if(o[0] == '/')
	{
		if (op1!=0)
		return op2/op1;
		else golf = 1;
	}
	else if(o[0] == '%')
	{
		if(op1 !=0)
		return op2%op1;
		else golf = 1;
	}
	else if(o[0] == '&')
	{
		return op2&&op1;
	}
	else if(o[0] == '^')
	{
		return op2^op1;
	}
	else if(o[0] == '|')
	{
		return op2||op1;
	}
	else if(o[0] == '!')
	{
		return op2!=op1;
	}
	else if(o[0] == '<')
	{
		if(o[1] == '<')
		{
			return op2<<op1;
		}
		else if(o[1] == '=')
		{
			return op2<=op1;
		}
		else 
		{
			return op2<op1;
		}
	}
	else if(o[0] == '>')
	{
		if(o[1] == '>')
		{
			return op2>>op1;
		}
		else if(o[1] == '=')
		{
			return op2>=op1;
		}
		else 
		{
			return op2>op1;
		}
	}	
	else if(o[0] == '=')
	{
		return op2 == op1;
	}
}


////// P part 

unsigned long long int cat(unsigned int n) 
{ 
    unsigned long long int cat[n+1]; 
  	int i,j;
    cat[0] = cat[1] = 1; 
    for ( i=2; i<=n; i++) 
    { 
        cat[i] = 0; 
        for ( j=0; j<i; j++) 
            cat[i] += cat[j] * cat[i-j-1]; 
    } 
    return cat[n]; 
} 




int ch(int ip[], int op[], int n) 
{
	int stack[n] ;
	int top = -1;
	int i ;
	int opp = 0;
	
	for(i = 0;i<n;i++)
	{
		if(ip[i] == op[opp])
		{
			opp+=1;
			if(top!=-1)
			{
				int flag = 1;
				while(stack[top]==op[opp] && flag == 1)
				{
					top-=1;
					opp+=1;
					if(top == -1)
					flag = 0;
				}
			}
			
		}
		else
		{
			top+=1;
			stack[top] = ip[i];
		}
	}
	
	
	if (top == -1)
	{
		return 1;
	}
	else return 0;
}
unsigned long long int count = 0;

void nextp(int input[],int arr[],int l,unsigned long long int target)
{
	int i ;
	int x = -1;
	int y = -1;
	int temp;	
	
	if(ch(input,arr,l) == 1) count+=1;
	
	if (count == target)
	{
		for(i = 0;i<l;i++)
		{
			printf("%d ",arr[i]);
		}
	}
	

	for(i = l-2;i>=0;i--)
	{
		if(arr[i+1]>arr[i])
		{
			x = i;
			break;
		}
	}

	if (x!=-1)
	{
		for(i = l-1;i>=0;i--)
		{
			if(arr[x]<arr[i])
			{
				y = i;
				temp = arr[y];
				arr[y] = arr[x];
				arr[x] = temp;
				
				break;
			}
		}
			
		int p[l-x-1];
		for(i = x+1;i<l;i++)
		{
			p[i-(x+1)] = arr [i];
		}
		
		for(i = x+1;i<l;i++)
		{
			arr[i] = p[(l-x-2)-(i-(x+1))];
		}
		
	}
	if(count == target)x=-1;
	if(x!=-1) return nextp(input,arr,l,target);
	
}


//////



int main()
{

	int store;
	
	int nullI,indexI,iI,jI,qr,T,t;

	jI = 0;
	indexI = 0;
	
	char strI[100];
	
	char pref[20][3] = {"*","/","%","+","-","<<",">>","<","<=",">",">=",
						"==","!=","&","^","|"};
						
	char stackI[Z][5];
	
	char tempI[5];	
	char aI[30][5];
	
	char input;
 
 	scanf("%d %d",&T,&Z);
 	
 	
 	while(T--)
 	{
		scanf(" %c",&input);
		
		/////////////// for S
		if(input== 'S')
 		{
 			head = NULL;
 			size = 0;
 			qr = 0;
 			while(qr >=-3 )
 			{
 				scanf(" %d",&qr);
 				
 				if(qr>0) 
 				{
					Ins_Beg(qr);
					size +=1;
				}
				 
				else if(qr == 0)
				{
					if(size == 0) printf("E ");
					else printf("NE ");
				}
				
				else if(qr == -1)
				{
					if(size>0)
					{
						Del_First();
						size-=1;
						
					}
					else printf("E ");
				}
				
				else if(qr == -2)
				{
					printf("NF ");
				}
				
				else if(qr == -3)
				{
					printf("%d ",size);
				}
			}
			printf("\n");
		}
		//////////// end for S
		
		//////////// for Q
		
		else if(input == 'Q')
		{
			
			front = NULL;
			rear = NULL;
			sizeq = 0;
			qr = 0;
			
			while(qr>=-3)
			{
				scanf(" %d",&qr);
				if(qr >0)
				{
					struct Node *temp;
					enQ(qr);
					sizeq+=1;
					
				}
				
				else if(qr == 0)
				{
					if(sizeq = 0) printf("E ");
					else printf("NE ");
				}
				
				else if(qr == -1)
				{
					delQ();
					if(sizeq>0) sizeq-=1;
				}
				
				else if(qr == -2)
				{
					printf("NF ");
				}
				
				else if(qr == -3)
				{
					printf("%d ",sizeq);
				}
			}
			printf("\n");
		}
		/////////// end for Q
		
		/////////// for I
		
		
		if(input == 'I')
		{
			indexI = 0;
			jI = 0;
		
			memset(aI,'\0',sizeof(aI));
			
		    scanf(" %[^\n]%*c", strI);
			//////////////////////////////////////////////////////////////// is valid 
			int preev = 1; // 0 ->int 1->space 2->operator 3-> -
			int error = 0;
			int ls = strlen(strI);
			int i;
			for(i = 0;i<ls;i++)
			{
				if(strI[i] == ' ') 
				{
					preev = 1;
					
				}
				
				else if(strI[i] == '0' ||strI[i] == '1' ||strI[i] == '2' ||strI[i] == '3' ||strI[i] == '4' ||
				strI[i] == '5' ||strI[i] == '6' ||strI[i] == '7' ||strI[i] == '8' ||strI[i] == '9' )
				{
					// given is integer
					if(preev == 2)
					{
						error = 1;
					}
					preev = 0;
				}
				
				else if(strI[i] == '-')
				{
					if(preev!= 1)
					{
						error = 1;
						
					}
					preev = 3;
				}
				
				else 
				{
					if(preev == 0 || preev == 3)
					{
						error = 1;
					}
					else if(preev == 2)
					{
						if(strI[i]!= '=' && strI[i]!='<' && strI[i]!= '>' )
						{
							error = 1;
						}
					}
					preev = 2;
				}
			}
					
			/////////////////////////////////////////////////////////////////////////
			int top = -1;
			char ans[50][5];
			int ansi,staI;
			ansi = 0;
			
		   	if(error == 0)
		   	{
		   		memset(tempI, '\0', sizeof(tempI));
		   	
				int num = 0;
				preev = 0; // 1 means operator
			
			for(iI = 0;iI<100;iI++)
		   	{
		   		if((strI[iI]) != '#' && strI[iI]!=' ' && strI[iI]!= '\0')
		   		{
		   			
		   			tempI[indexI] = strI[iI];
		   			indexI+=1;
		   			num = 1;
				}
				
				else if(strI[iI] == ' ')
				{
					if (num == 1)
					{
						strcpy(aI[jI],tempI);
						jI+=1;
					}
					
					else 
					{
						error = 1;
					}
					
					num=0;
					memset(tempI, '\0', sizeof(tempI));
					indexI = 0;
					
				}
				
				else if(strI[iI] == '#')
				{
					nullI = jI;
					if(num!=0) 
					{
						error =1;
					}
					memset(tempI, '\0', sizeof(tempI));
					break;
				}
				
			}
			
			//////////
			int flag = 0; // 0->operator 1->operand
			
			for(iI = 0;iI<=nullI;iI++)
			{
				if(isOperand(aI[iI] ) == 0)	
				{
					if(flag == 0) error = 1;
					flag = 0 ;
				}
				else 
				{
					if(flag == 1) error = 1;
					flag = 1;
				}
			}
			
			
			/////////
			
			
		
			//// I2P conversion
			
		
			int pre = -1;
			
			int prev = 1; //1 means operator
			
			
			strcpy(aI[nullI],")");
			for(iI= 0;iI <= nullI;iI++) //traverse aI
			{
				if(aI[iI][0] == ')')
				{
					
					int tom;
					if(top!=-1)
					{
						
						for(tom = top ;tom >=0;tom--)
						{
							strcpy(ans[ansi+top-tom],stackI[tom]);
							
						}
						ansi+=top+1;
						top = -1;
						
					}
				}
				
				else if(!isOperand(aI[iI])) // not a number
				{
					if(prev == 1) 
					{
						error = 1;
					}
					pre = preff(aI[iI]);
					
					if(top != -1) //if stack isnot empty
					{
						int temp = top;
						for(staI = temp ;staI>=0;staI--)
						{
							if(preff(stackI[staI]) <= pre)
							{
								top-=1;
								strcpy(ans[ansi],stackI[staI]);
								ansi+=1;
							}
							
						}
						
						
						strcpy(stackI[top+1],aI[iI]);
						top+=1;
						if(top >=Z) 
						{
							error = 1;
						}
						
					}
					else 
					{
						
						strcpy(stackI[0],aI[iI]);
						top+=1;
						if(top>=Z) 
						{
							error = 1;
						}
					}	
					prev = 1;
				}

				else // is number
				{
					if(prev == 0) 
					{
						error = 1;
					}
					strcpy(ans[ansi],aI[iI]);
					ansi+=1;
					prev = 0;
				}
				
			}
			     	
			}
			
			if(top==-1 && error == 0)
			{
				for(iI = 0;iI<ansi;iI++)
				{
					printf("%s ",ans[iI]);
				}
			}
			else printf("Error"); 
			
			printf("\n");
			memset(ans,'\0',sizeof(ans));
			
			memset(strI,'\0',sizeof(strI));
		}
	
		if(input == 'E')
		{
			golf = 0;
			
			//// finding post fix expression
			indexI = 0;
			jI = 0;
		
			memset(aI,'\0',sizeof(aI));
			
		    scanf(" %[^\n]%*c", strI);
			//////////////////////////////////////////////////////////////// is valid 
			int preev = 1; // 0 ->int 1->space 2->operator 3-> -
			int error = 0;
			int ls = strlen(strI);
			int i;
			for(i = 0;i<ls;i++)
			{
				if(strI[i] == ' ') 
				{
					preev = 1;
					
				}
				
				else if(strI[i] == '0' ||strI[i] == '1' ||strI[i] == '2' ||strI[i] == '3' ||strI[i] == '4' ||
				strI[i] == '5' ||strI[i] == '6' ||strI[i] == '7' ||strI[i] == '8' ||strI[i] == '9' )
				{
					// given is integer
					if(preev == 2)
					{
						error = 1;
					}
					preev = 0;
				}
				
				else if(strI[i] == '-')
				{
					if(preev!= 1)
					{
						error = 1;
						
					}
					preev = 3;
				}
				
				else 
				{
					if(preev == 0 || preev == 3)
					{
						error = 1;
					}
					else if(preev == 2)
					{
						if(strI[i]!= '=' && strI[i]!='<' && strI[i]!= '>' )
						{
							error = 1;
						}
					}
					preev = 2;
				}
			}
					
			/////////////////////////////////////////////////////////////////////////
			int top = -1;
			char ans[50][5];
			int ansi,staI;
			ansi = 0;
			
		   	if(error == 0)
		   	{
		   		memset(tempI, '\0', sizeof(tempI));
		   	
			int num = 0;
			preev = 0; // 1 means operator
			
			for(iI = 0;iI<100;iI++)
		   	{
		   		if((strI[iI]) != '#' && strI[iI]!=' ' && strI[iI]!= '\0')
		   		{
		   			
		   			tempI[indexI] = strI[iI];
		   			indexI+=1;
		   			num = 1;
				}
				
				else if(strI[iI] == ' ')
				{
					if (num == 1)
					{
						strcpy(aI[jI],tempI);
						jI+=1;
					}
					
					else 
					{
						error = 1;
					}
					
					num=0;
					memset(tempI, '\0', sizeof(tempI));
					indexI = 0;
					
				}
				
				else if(strI[iI] == '#')
				{
					nullI = jI;
					if(num!=0) 
					{
						error =1;
					}
					memset(tempI, '\0', sizeof(tempI));
					break;
				}
				
			}
				
			//// I2P conversion
		
			int pre = -1;
			
			int prev = 1; //1 means operator
			
			int flag = 0; // 0->operator 1->operand
			
			for(iI = 0;iI<=nullI;iI++)
			{
				if(isOperand(aI[iI] ) == 0)	
				{
					if(flag == 0) error = 1;
					flag = 0 ;
				}
				else 
				{
					if(flag == 1) error = 1;
					flag = 1;
				}
			}
			
			
			strcpy(aI[nullI],")");
			for(iI= 0;iI <= nullI;iI++) //traverse aI
			{
				if(aI[iI][0] == ')')
				{
					int tom;
					if(top!=-1)
					{
						
						for(tom = top ;tom >=0;tom--)
						{
							strcpy(ans[ansi+top-tom],stackI[tom]);
							
						}
						ansi+=top+1;
						top = -1;
						
					}
				}
				
				else if(!isOperand(aI[iI])) // not a number
				{
					if(prev == 1) 
					{
						error = 1;
					}
					pre = preff(aI[iI]);
					
					if(top != -1) //if stack isnot empty
					{
						int temp = top;
						for(staI = temp ;staI>=0;staI--)
						{
							if(preff(stackI[staI]) <= pre)
							{
								top-=1;
								strcpy(ans[ansi],stackI[staI]);
								ansi+=1;
							}
							
						}
						strcpy(stackI[top+1],aI[iI]);
						top+=1;
						if(top >=Z) 
						{
							error = 1;
						}
						
					}
					else 
					{
						
						strcpy(stackI[0],aI[iI]);
						top+=1;
						if(top>=Z) 
						{
							error = 1;
						}
					}	
					prev = 1;
				}

				else // is number
				{
					if(prev == 0) 
					{
						error = 1;
					}
					strcpy(ans[ansi],aI[iI]);
					ansi+=1;
					prev = 0;
				}
				
			}
			     	
			}
			
			//// evaluating post fix expression ans ... last index ansi
			int stackE[Z];
			int op1;
			int op2;
			
			if(top ==-1 && error == 0)
			{
				top = -1;
				for(iI = 0;iI<ansi;iI++)	
				{
					if(ans[iI][0] == '0'|| ans[iI][0] == '1'|| ans[iI][0] == '2'|| ans[iI][0] == '3'||
					ans[iI][0] == '4'|| ans[iI][0] == '5'|| ans[iI][0] == '6'|| ans[iI][0] == '7'||
					ans[iI][0] == '8'||ans[iI][0] == '9') // number found
					{
						op1 = atoi(ans[iI]);
						stackE[top+1] = op1;
						top+=1;
					}
					
					else if(ans[iI][0] == '-')
					{
						if(ans[iI][1] == '0'|| ans[iI][1] == '1'|| ans[iI][1] == '2'|| ans[iI][1] == '3'||
						ans[iI][1] == '4'|| ans[iI][1] == '5'|| ans[iI][1] == '6'|| ans[iI][1] == '7'||
						ans[iI][1] == '8'||ans[iI][1] == '9')// number found
						{
							op1 = atoi(ans[iI]);
							stackE[top+1] = op1;
							top+=1;
						}
						
						else // operator found 
						{
							op1 = stackE[top];
							op2 = stackE[top-1];
							stackE[top-1] = operation(op1,op2,ans[iI]);
							top-=1;
						}
					}
					
					else // operator found
					{
						op1 = stackE[top];
						op2 = stackE[top-1];
						stackE[top-1] = operation(op1,op2,ans[iI]);
						top-=1;
					}
				}
			}
			////	
			if (golf == 1) error = 1;
			
			if(error == 0)
			printf("%d\n",stackE[top]);
			else printf("Error\n");
			memset(ans,'\0',sizeof(ans));
			memset(strI,'\0',sizeof(strI));
			
		}
		
		if(input == 'P') // for P
		{
			unsigned int N,K;
			count = 0;
			
			
			unsigned long long int store;
			scanf(" %u %u",&N,&K);
			store = cat(N);
			int input[N];
				int copy[N];
			int ind;
			for (ind = 0;ind<N;ind++)
			{
				input[ind] = ind+1;
				copy[ind] = ind+1;
			}
		
			printf("%llu ",store);
			nextp(copy,input,N,K);
			printf("\n");
			
		}
		
	}
	
	return 0;	

}

