#include<bits\stdc++.h>

using namespace std;
///////////////// Fibonnaci Heap
int no_nodes= 0;

struct fNode
{
    int wt;
    int to;
    int rank;
    fNode* par;
    fNode* chd;
    fNode* left;
    fNode* right;
};

struct fNode* createHeap()
{
    struct fNode* p = NULL;
    return p;
}

struct fNode *H = createHeap(); // global Fibonacci Heap

struct fNode* Create_node(int data,int to)
{
    struct fNode* x = new fNode;
    
	x->wt = data;
    x->to = to;
    
    return x;
}

struct fNode* Insert(struct fNode* H, struct fNode* x)
{
    x->rank = 0;
    x->par = NULL;
    x->chd = NULL;
    x->left = x;
    x->right = x;
    
	if (H != NULL) // Heap is intially empty
    {
        (H->left)->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        if (x->wt < H->wt)
            H = x;
    }
    else
    {
        H = x;
    }
    no_nodes += 1;
    return H;
}

int Fibonnaci_link(fNode* H1, fNode* y, fNode* z)
{
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if (z->right == z)
        H1 = z;
    y->left = y;
    y->right = y;
    y->par = z;
    if (z->chd == NULL)
        z->chd = y;
    y->right = z->chd;
    y->left = (z->chd)->left;
    ((z->chd)->left)->right = y;
    (z->chd)->left = y;
    if (y->wt < (z->chd)->wt)
        z->chd = y;
    z->rank++;
}

struct fNode* Union(fNode* x, fNode* y)
{
    struct fNode* p;
    struct fNode* H = createHeap();
    H = x;
    (H->left)->right = y;
    (y->left)->right = H;
    p = H->left;
    H->left = y->left;
    y->left = p;
    return H;
}

int  Consolidate(struct fNode* a)
{
    int d, i;
    float f = (log(no_nodes)) / (log(2));
    int D = f;
    struct fNode* A[D];
    for (i = 0; i <= D; i++)
        A[i] = NULL;
    fNode* x = a;
    fNode* y;
    fNode* np;
    fNode* pt = x;
    do
    {
        pt = pt->right;
        d = x->rank;
        while (A[d] != NULL)
        {
            y = A[d];
            if (x->wt > y->wt)
            {
                np = x;
                x = y;
                y = np;
            }
            if (y == a)
                a = x;
            Fibonnaci_link(a, y, x);
            if (x->right == x)
                a = x;
                A[d] = NULL;
            d = d + 1;
        }
        A[d] = x;
        x = x->right;
    }
    while (x != a);
    H = NULL;
    for (int j = 0; j <= D; j++)
    {
        if (A[j] != NULL)
        {
            A[j]->left = A[j];
            A[j]->right =A[j];
            if (H != NULL)
            {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->wt < H->wt)
                H = A[j];
            }
            else
            {
                H = A[j];
            }
            if(H == NULL)
                H = A[j];
            else if (A[j]->wt < H->wt)
                H = A[j];
        }
    }
}
 
/////////////////////////////////////////// 
int Display(fNode* H)
{
    fNode* p = H;
    if (p == NULL)
    {
        cout<<"The Heap is Empty"<<endl;
        return 0;
    }
    cout<<"The root nodes of Heap are: "<<endl;
    do
    {
        cout<<p->wt;
        p = p->right;
        if (p != H)
        {
            cout<<"-->";
        }
    }
    while (p != H && p->right != NULL);
    cout<<endl;
}

struct fNode* Extract_Min(struct fNode* a)
{
    struct fNode* p;
    struct fNode* ptr;
    struct fNode* z = a;
    p = z;
    ptr = z;
    if (z == NULL)
        return z;
    fNode* x;
    fNode* np;
    x = NULL;
    if (z->chd != NULL)
        x = z->chd;
    if (x != NULL)
    {
        ptr = x;
        do
        {
            np = x->right;
            (a->left)->right = x;
            x->right = a;
            x->left = a->left;
            a->left = x;
            if (x->wt < a->wt)
                a = x;
            x->par = NULL;
            x = np;
        }
        while (np != ptr);
    }
    (z->left)->right = z->right;
    (z->right)->left = z->left;
    a = z->right;
    if (z == z->right && z->chd == NULL)
        H = NULL;
    else
    {
        a = z->right;
        Consolidate(a);
    }
    no_nodes -= 1;
    return p;
}



int main()
{
	struct fNode* temp = Create_node(12,1);
	H = Insert(H,temp);
	temp = Create_node(11,2);
	H = Insert(H,temp);
	temp = Create_node(13,3);
	H = Insert(H,temp);
	temp = Create_node(200,4);
	H = Insert(H,temp);
	
	temp = Create_node(100,9);
	H = Insert(H,temp);
	
	temp = Create_node(500,8);
	H = Insert(H,temp);
	
	temp = Create_node(50,48);
	H = Insert(H,temp);
	
	temp = Create_node(300,7);
	H = Insert(H,temp);
	
	temp = Create_node(400,6);
	H = Insert(H,temp);
	
	
	temp = Create_node(10,6);
	H = Insert(H,temp);
	
	temp = Create_node(0,6);
	H = Insert(H,temp);
	
	
	temp = Create_node(4,6);
	H = Insert(H,temp);
	
	
	temp = Create_node(0,6);
	H = Insert(H,temp);
	Display(H);

	struct fNode* t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	Display(H);
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;

	Display(H);
	cout<<no_nodes<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);
	cout<<no_nodes<<endl;
	cout<<t->wt<<" "<<t->to<<endl;
	t = Extract_Min(H);

	
	Display(H);
     return 0;
}

