#include<stdlib.h>

#include<stdbool.h>

#include<stdio.h>
 // CS201 Assignment 3

int count_nodes = 0;
struct Node {
    struct BinNode * data;
    struct Node * next;
};
/*
struct intNode
{
	int data;
	struct intNode *next;
};
*/
struct BinNode {
    int data;
    struct BinNode * left;
    struct BinNode * right;
    int height;

};

struct BinNode * bstRoot;
struct BinNode * avlRoot;

struct BinNode * createBinNode(int data) {
    struct BinNode * b;
    b = (struct BinNode * ) malloc(sizeof(struct BinNode));
    b -> left = NULL;
    b -> right = NULL;
    b -> data = data;
    b -> height = 1;
    if (b == NULL) printf("Memory Error while Creating BinNode\n");
    else return b;
}

struct Node * createNode(struct BinNode * data) {
    struct Node * p;
    p = (struct Node * ) malloc(sizeof(struct Node));
    p -> next = NULL;
    p -> data = data;

    if (p == NULL) printf("Memory Error while Creating Node\n");
    else return p;
}
/////////////////////////////////////// F part start
int Find(struct BinNode * root, int data) {
    if (root == NULL) return 0;
    else {
        if (root -> data > data) return Find(root -> left, data);
        else if (root -> data < data) return Find(root -> right, data);
    }
    return 1;
}
/////////////////////////////////////// F part end
///////////////////////////////////////  T part start

void Insertion_bst(int data) {
    count_nodes += 1;
    struct BinNode * temp; // node created to insert in the tree
    temp = createBinNode(data);

    struct BinNode * trav;

    trav = bstRoot;
    int flag = 0;
    if (bstRoot == NULL) {

        bstRoot = temp;
        flag = 1;
    } else {
        while (trav != NULL) {

            if (trav -> data > data) {
                if (trav -> left == NULL) {
                    trav -> left = temp;
                    trav = NULL;
                } else trav = trav -> left;
            } else if (trav -> data < data) {
                if (trav -> right == NULL) {
                    trav -> right = temp;
                    trav = NULL;

                } else trav = trav -> right;
            } else if (trav -> data == data) {
                flag = 1;
                break;
            }

        }
        if (flag == 0) {
            trav = temp;
        }

    }

}

struct BinNode * getMax(struct BinNode * root) {
    struct BinNode * temp;
    temp = root;
    while (temp -> right != NULL) {
        temp = temp -> right;
    }
    return temp;
}

void Deletion_bst(int data) {
    struct BinNode ** temp;
    temp = & bstRoot;
    int flag;
    while ( * temp != NULL && flag == 0) {
        if (( * temp) -> data == data) {
            flag = 1;
        } else if (( * temp) -> data > data) {
            temp = & (( * temp) -> left);
        } else if (( * temp) -> data < data) {
            temp = & (( * temp) -> right);
        }

    }
    if (flag == 0) return;
    else {
        count_nodes -= 1;
        if (( * temp) -> left != NULL && ( * temp) -> right != NULL) {
            int delt;
            struct BinNode * del;
            del = getMax(( * temp) -> left);
            delt = del -> data;
            Deletion_bst(delt);
            ( * temp) -> data = delt;
        } else if ((( * temp) -> left == NULL && ( * temp) -> right != NULL) | (( * temp) -> left != NULL && ( * temp) -> right == NULL)) {
            if (( * temp) -> left == NULL && ( * temp) -> right != NULL) {
                ( * temp) = ( * temp) -> right;
            } else {
                ( * temp) = ( * temp) -> left;
            }
        } else if (( * temp) -> left == NULL && ( * temp) -> right == NULL) {
            * temp = NULL;
        }

    }
}
///////////////////////////////////////  T part end

struct Node * PreHead;

void InsBeg(struct BinNode * data) {
    struct Node * p;
    p = createNode(data);

    p -> data = data;

    if (PreHead == NULL) {
        PreHead = p;
    } else {
        struct Node * temp;

        temp = PreHead;
        PreHead = p;
        p -> next = temp;

    }

}
/////////////////////////////////////// P part start
void PreOrder(struct BinNode * root) // Iterative Code
{
    struct BinNode * temp;
    if (root == NULL) return;
    else {
        struct Node * temp1;
        temp1 = createNode(root);

        PreHead = temp1;
        while (PreHead != NULL) {
            temp = PreHead -> data; // Pop Operation
            printf("%d ", temp -> data);
            PreHead = PreHead -> next; // Pop Operation
            if (temp -> right != NULL) InsBeg(temp -> right);
            if (temp -> left != NULL) InsBeg(temp -> left);
        }
    }

}

void PreOrder1(struct BinNode * root) // Recursive Code
{
    if (root != NULL) {
        printf("%d ", root -> data);
        PreOrder1(root -> left);
        PreOrder1(root -> right);

    }
}

/////////////////////////////////////// P part end

/////////////////////////////////////// I part start
void InOrder(struct BinNode * root) {
    if (root != NULL) {
        InOrder(root -> left);
        printf("%d ", root -> data);
        InOrder(root -> right);
    }
}
/////////////////////////////////////// I part end

/////////////////////////////////////// S part start
void PostOrder(struct BinNode * root) {

    if (root != NULL) {
        PostOrder(root -> left);
        PostOrder(root -> right);
        printf("%d ", root -> data);
    }
}
/////////////////////////////////////// S part end

/////////////////////////////////////// L part start

struct Queue {
    struct Node * front;
    struct Node * rear;
};

struct Queue * createQueue() {
    struct Queue * Q;
    Q = (struct Queue * ) malloc(sizeof(struct Queue));
    Q -> front = NULL;
    Q -> rear = NULL;

    if (Q != NULL)
        return Q;

    else printf("Memory Error While Creating Queue\n");
}

void EnQ(struct Queue * Q, struct BinNode * data) // insert at the rear end
{
    struct Node * p;
    p = createNode(data);

    if (Q -> front == NULL && Q -> rear == NULL) // initial Condition
    {
        Q -> front = p;
        Q -> rear = p;
    } else {
        Q -> rear -> next = p;
        Q -> rear = Q -> rear -> next;
    }
}

struct BinNode * DeQ(struct Queue * Q) // delete from the front end
{
    struct BinNode * temp;
    if (Q -> front == NULL);

    else {
        struct Node * p;
        p = Q -> front;
        temp = Q -> front -> data;
        Q -> front = p -> next;
        if (Q -> front == NULL) Q -> rear = NULL;
    }

    return temp;
}
/*
void Display(struct Queue * Q)
{
	struct Node *temp;
	temp = Q->front;
	if(temp == NULL) return;
	else
	{
		while(temp!= NULL)
		{
			printf("%d ",temp->data);
			temp = temp->next;
		}
	}
}
*/
bool isEmptyQueue(struct Queue * Q) {
    if (Q -> front == NULL && Q) return 1;
    else return 0;
}
////////////////////////////////////////////////////////////////

void LevelOrder(struct BinNode * root) {
    struct BinNode * temp;
    struct Queue * Q = createQueue();

    if (root == NULL)
        return;

    EnQ(Q, root);
    while (Q -> front != NULL) {
        temp = DeQ(Q);

        printf("%d ", temp -> data); // printing data of current node

        if (temp -> left != NULL) {
            EnQ(Q, temp -> left);
        }
        if (temp -> right != NULL) {
            EnQ(Q, temp -> right);
        }
    }
}

/////////////////////////////////////// L part end

/////////////////////////////////////// Q part start
int count_leaves = 0; // counting leaves in tree

int leaves(struct BinNode * root) {
    if (root != NULL) {
        if (root -> left == NULL && root -> right == NULL) {
            count_leaves += 1;
        } else {
            if (root -> left != NULL) leaves(root -> left);
            if (root -> right != NULL) leaves(root -> right);

        }
    }
    return count_leaves;
}
/////////////////////////////////////// Q part end

/////////////////////////////////////// D part start

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}
int depth(struct BinNode * root) {

    if (root == NULL) return 0;
    else {
        return 1 + max(depth(root -> left), depth(root -> right));
    }
}
/////////////////////////////////////// D part end

/////////////////////////////////////// C part start

int lca(struct BinNode * root, int a, int b) {
    int fa = Find(root, a);
    int fb = Find(root, b);

    if (root -> data > a && root -> data > b) return lca(root -> left, a, b);
    else if (root -> data < b && root -> data < a) return lca(root -> right, a, b);
    else {
        if (fa == 1 && fb == 1) return root -> data;
        else return -1;
    }

}

/////////////////////////////////////// C part end

/////////////////////////////////////// R part start

void path(struct BinNode * root, int a, int b) {
    int source = 0;
    int dest = 0;
    int index = 0;
    int height = depth(root);
    struct BinNode * temp;
    temp = root;
    while (temp != NULL && source == 0) {
        if (temp -> data == a) {
            source = 1;
            break;
        } else {
            if (temp -> data > a) temp = temp -> left;
            else if (temp -> data < a) temp = temp -> right;
        }

    }
    if (source == 0) printf("Source Does Not Exists\n");
    else {
        if (Find(root, b) == 0) printf("Destination Does Not Exist\n");
        else {
            int endd;
            int arr[height + 1];
            while (temp != NULL && dest == 0) {
                arr[index] = temp -> data;
                index += 1;
                if (temp -> data == b) {
                    dest = 1;
                    endd = index;
                    break;
                } else {
                    if (temp -> data < b) temp = temp -> right;
                    else if (temp -> data > b) temp = temp -> left;
                }
            }

            if (dest == 0) printf("Unreachable\n");
            else {
                for (index = 0; index < endd; index += 1) printf("%d ", arr[index]);
                printf("\n");
            }
        }
    }

}

/////////////////////////////////////// R part end

/////////////////////////////////////// X part start
int Diameter(struct BinNode * root) {
    if (root == NULL) return 0;
    else {
        return max(depth(root -> left) + depth(root -> right) + 1, max(Diameter(root -> left), Diameter(root -> right)));
    }
}

/////////////////////////////////////// X part end

/////////////////////////////////////// H part start

int height(struct BinNode * N) {
    if (N == NULL)
        return 0;
    return N -> height;
}

struct BinNode * RR(struct BinNode * y) {
    struct BinNode * x = y -> left;
    struct BinNode * T2 = x -> right;

    x -> right = y;
    y -> left = T2;

    y -> height = max(height(y -> left), height(y -> right)) + 1;
    x -> height = max(height(x -> left), height(x -> right)) + 1;

    return x;
}

struct BinNode * LR(struct BinNode * x) {
    struct BinNode * y = x -> right;
    struct BinNode * T2 = y -> left;

    y -> left = x;
    x -> right = T2;

    x -> height = max(height(x -> left), height(x -> right)) + 1;
    y -> height = max(height(y -> left), height(y -> right)) + 1;

    return y;
}

int BF(struct BinNode * N) {
    if (N == NULL)
        return 0;
    return height(N -> left) - height(N -> right);
}

struct BinNode * Insert_avl(struct BinNode * root, int data) {
    if (root == NULL)
        return (createBinNode(data));

    if (data < root -> data)
        root -> left = Insert_avl(root -> left, data);
    else if (data > root -> data)
        root -> right = Insert_avl(root -> right, data);
    else
        return root;

    root -> height = 1 + max(height(root -> left),
        height(root -> right));

    int balance = BF(root);

    if (balance > 1 && data < root -> left -> data)
        return RR(root);

    if (balance < -1 && data > root -> right -> data)
        return LR(root);

    if (balance > 1 && data > root -> left -> data) {
        root -> left = LR(root -> left);
        return RR(root);
    }

    if (balance < -1 && data < root -> right -> data) {
        root -> right = RR(root -> right);
        return LR(root);
    }

    return root;
}

struct BinNode * min(struct BinNode * root) {
    struct BinNode * current = root;

    while (current -> left != NULL)
        current = current -> left;

    return current;
}

struct BinNode * Delete_avl(struct BinNode * root, int data) {

    if (root == NULL)
        return root;

    if (data < root -> data)
        root -> left = Delete_avl(root -> left, data);

    else if (data > root -> data)
        root -> right = Delete_avl(root -> right, data);

    else {
        if ((root -> left == NULL) || (root -> right == NULL)) {
            struct BinNode * temp = root -> left ? root -> left :
                root -> right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = * temp;

            free(temp);
        } else {
            struct BinNode * temp = min(root -> right);

            root -> data = temp -> data;

            root -> right = Delete_avl(root -> right, temp -> data);
        }
    }

    if (root == NULL)
        return root;

    root -> height = 1 + max(height(root -> left),
        height(root -> right));

    int balance = BF(root);

    if (balance > 1 && BF(root -> left) >= 0)
        return RR(root);

    if (balance > 1 && BF(root -> left) < 0) {
        root -> left = LR(root -> left);
        return RR(root);
    }

    if (balance < -1 && BF(root -> right) <= 0)
        return LR(root);

    if (balance < -1 && BF(root -> right) > 0) {
        root -> right = RR(root -> right);
        return LR(root);
    }

    return root;
}

/////////////////////////////////////// H part end
/////////////////////////////////////// Y part start
void printLeaves(struct BinNode * root) {
    if (root != NULL) {
        if (root -> left == NULL && root -> right == NULL) {
            printf("%d ", root -> data);
        } else {
            if (root -> right != NULL) printLeaves(root -> right);
            if (root -> left != NULL) printLeaves(root -> left);

        }
    }
}

void Boundary(struct BinNode * root) {
    PreHead = NULL;
    struct BinNode * temp;
    temp = root;
    while (temp -> right != NULL) {
        printf("%d ", temp -> data);
        temp = temp -> right;
    }

    printLeaves(root);

    temp = root;
    while (temp -> left != NULL) {
        if (temp != root)
            InsBeg(temp);
        temp = temp -> left;
    }

    struct Node * temp1;
    temp1 = PreHead;
    while (temp1 != NULL) {
        printf("%d ", temp1 -> data -> data);
        temp1 = temp1 -> next;
    }
}

/////////////////////////////////////// Y part end

/////////////////////////////////////// W part start
int width(struct BinNode * root) {
    int count, ans, temp;
    struct Queue * Q;
    struct BinNode * temp1;

    Q = createQueue();
    ans = 0;
    if (root != NULL) {
        EnQ(Q, root);

        count = 1;
        ans = 0;
        temp = 0;
        while (!isEmptyQueue(Q)) {
            if (count > ans) ans = count;

            while (count--) {
                temp1 = DeQ(Q);
                if (temp1 -> left != NULL) {
                    EnQ(Q, temp1 -> left);
                    temp += 1;
                }
                if (temp1 -> right != NULL) {
                    EnQ(Q, temp1 -> right);
                    temp += 1;
                }

            }
            count = temp;
            temp = 0;
        }
    }
    return ans;
}

void setter() {
    PreHead = NULL;
    count_leaves = 0;
    bstRoot = NULL;
    avlRoot = NULL;
    count_nodes = 0;
}

/////////////////////////////////////// W part end

/////////////////////////////////////// AVL  part start

/////////////////////////////////////// AVL part end
int main() {
    int t;
    int prev;
    prev = 0; // 0 means previous was bst else avl
    int num;
    char query, temp;
    scanf("%d ", & t);

    while (t--) {
        scanf("%c", & query);
        //printf("%c  here\n",query);
        if (query == 'T' | query == 'H' | query == 'U' | query == 'F' | query == 'C' | query == 'R') {

            if (query == 'T') {
                setter();
                prev = 0;
                do {
                    scanf("%d%c", & num, & temp);
                    if (num > 0) {
                        Insertion_bst(num);
                    } else if (num < 0) {
                        Deletion_bst(-num);
                    }

                } while (temp != '\n');

            } else if (query == 'H') {
                setter();

                prev = 1;
                do {
                    scanf("%d%c", & num, & temp);
                    if (num > 0) {
                        Insert_avl(avlRoot, num);
                    } else if (num < 0) {
                        Delete_avl(avlRoot, -num);
                    }

                } while (temp != '\n');
            } else if (query == 'A') {
                if (prev == 0) // previous tree is bst
                {
                    do {
                        scanf("%d%c", & num, & temp);
                        if (num > 0) {
                            Insertion_bst(num);
                        }

                    } while (temp != '\n');
                } else if (prev == 1) {
                    do {
                        scanf("%d%c", & num, & temp);
                        if (num > 0) {
                            Insert_avl(avlRoot, num);
                        }

                    } while (temp != '\n');
                }
            } else if (query == 'U') {
                if (prev == 0) // previous tree is bst
                {
                    do {
                        scanf("%d%c", & num, & temp);
                        if (num > 0) {
                            Deletion_bst(num);
                        }

                    } while (temp != '\n');
                } else if (prev == 1) {
                    do {
                        scanf("%d%c", & num, & temp);
                        if (num > 0) {
                            Delete_avl(avlRoot, num);
                        }

                    } while (temp != '\n');
                }
            } else if (query == 'F') {

                if (prev == 0) {
                    do {
                        scanf("%d%c", & num, & temp);
                        if (num > 0) {
                            int lol;
                            lol = Find(bstRoot, num);
                            if (lol == 0) printf("No\n");
                            else printf("Yes\n");

                        } else {
                            printf("No\n");
                        }

                    } while (temp != '\n');

                } else if (prev == 1) {

                    do {
                        scanf("%d%c", & num, & temp);
                        if (num > 0) {
                            int lol;
                            lol = Find(avlRoot, num);
                            if (lol == 0) printf("No\n");
                            else printf("Yesn");
                        } else {
                            printf("No\n");
                        }

                    } while (temp != '\n');

                }

            } else if (query == 'C') {
                int arr[2];
                int index = 0;
                if (prev == 0) {
                    do {
                        scanf("%d%c", & num, & temp);
                        arr[index] = num;
                        index += 1;

                    } while (temp != '\n');

                    index = lca(bstRoot, arr[0], arr[1]);
                    printf("%d\n", index);
                } else if (prev == 1) {
                    do {
                        scanf("%d%c", & num, & temp);
                        arr[index] = num;
                        index += 1;

                    } while (temp != '\n');

                    index = lca(avlRoot, arr[0], arr[1]);
                    printf("%d\n", index);
                }
            } else if (query == 'R') {
                int arr[2];
                int index = 0;
                if (prev == 0) {
                    do {
                        scanf("%d%c", & num, & temp);
                        arr[index] = num;
                        index += 1;

                    } while (temp != '\n');

                    path(bstRoot, arr[0], arr[1]);
                    printf("\n");
                } else if (prev == 1) {
                    do {
                        scanf("%d%c", & num, & temp);
                        arr[index] = num;
                        index += 1;

                    } while (temp != '\n');

                    path(avlRoot, arr[0], arr[1]);
                    printf("\n");
                }
            }
        } else {
            int ans;
            if (query == 'Q') {
                if (prev == 0) {
                    ans = leaves(bstRoot);
                    printf("%d\n", ans);
                    count_leaves = 0;
                } else if (prev == 1) {
                    ans = leaves(avlRoot);
                    printf("%d\n", ans);
                    count_leaves = 0;
                }
            } else if (query == 'N') {
                if (prev == 0) {
                    printf("%d\n", count_nodes);
                } else if (prev == 1) {
                    printf("%d\n", count_nodes);
                }
            } else if (query == 'P') {
                if (prev == 0) {
                    PreOrder(bstRoot);
                    printf("\n");

                } else if (prev == 1) {
                    PreOrder(avlRoot);
                    printf("\n");
                }
            } else if (query == 'I') {
                if (prev == 0) {
                    InOrder(bstRoot);
                    printf("\n");
                } else if (prev == 1) {
                    InOrder(avlRoot);
                    printf("\n");
                }
            } else if (query == 'S') {
                if (prev == 0) {
                    PostOrder(bstRoot);
                    printf("\n");
                } else if (prev == 1) {
                    PostOrder(avlRoot);
                    printf("\n");
                }
            } else if (query == 'L') {
                if (prev == 0) {
                    LevelOrder(bstRoot);
                    printf("\n");
                } else if (prev == 1) {
                    LevelOrder(avlRoot);
                    printf("\n");
                }
            } else if (query == 'D') {
                int Depth;
                if (prev == 0) {
                    Depth = depth(bstRoot);
                    printf("%d\n", Depth);
                } else if (prev == 1) {
                    Depth = depth(avlRoot);
                    printf("%d\n", Depth);
                }
            } else if (query == 'W') {
                int Width;
                if (prev == 0) {
                    Width = width(bstRoot);
                    printf("%d\n", Width);
                } else if (prev == 1) {
                    Width = width(avlRoot);
                    printf("%d\n", Width);
                }
            } else if (query == 'X') {
                int diameter;
                if (prev == 0) {
                    diameter = Diameter(bstRoot);
                    printf("%d\n", diameter);
                } else if (prev == 1) {
                    diameter = Diameter(avlRoot);
                    printf("%d\n", diameter);
                }
            } else if (query == 'Y') {

                if (prev == 0) {
                    Boundary(bstRoot);
                    printf("\n");
                } else if (prev == 1) {
                    Boundary(avlRoot);
                    printf("\n");
                }
            }
        }

    }

    return 0;

}
