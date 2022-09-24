#include<bits\stdc++.h>
#define INF 1000000000 
#define MAX 10000
using namespace std;

// Arboresence Assignment

struct Edge
{
	int u;  
	int v;
	int wt;
	
};

struct Edge* createEdge(int u,int v,int w)
{
	struct Edge *p = (struct Edge *)malloc(sizeof(struct Edge));
	p->u = u;
	p->v = v;
	p->wt = w;
	return p;
}
int ans = 0;

void  Arb(vector<Edge*>store,int root,int e,int v) // v: #vertices e: #edges 
{
	int cost[v];
	int flag = 0;
	
	vector<int> par(v);
	vector<int> id(v);
	vector<int> done(v);
	
	for(int i = 0;i<v;i++) 
	{
		cost[i] = INF;
		id[i] = -1;
		done[i] = -1;
		
	}
	cost[root] = 0;
	int newnode = 0;
    
	for(int i = 0;i<e;i++) 
	{
		if(cost[store[i]->v] > store[i]->wt && store[i]->u!= store[i]->v) 
		{
			cost[store[i]->v] = store[i]->wt;
			par[store[i]->v] = store[i]->u;
		}
	}
    	
	for (int i = 0; i < v; i++) 
    {
    	if(cost[i]!= INF) 
    	{
    		ans+=cost[i];
		}
		 
		 
        int temp = i;  
        cout<<"sangarn\n";
        while (done[temp] != i && id[temp] == -1 && temp != root)
	    {  
            done[temp] = i;  
            temp = par[temp];  
        }  
        cout<<"hrere"<<endl;
        if (temp != root && id[temp] == -1) 
		{  
            for (int u = par[temp]; u != temp; u = par[temp])  
            id[u] = newnode;  
            id[temp] = newnode++;
        } 
        
    }
    if(newnode == 0) return 	; 
    cout<<ans<<" ans "<<endl;
    for(int i = 0;i<v;i++)
    {
    	if(id[i] == -1)
    	{
    		id[i] = newnode;
    		newnode+=1;
		}
	}
	for (int i = 0; i < e; i++) 
	{
        int ve = store[i]->v;  
        store[i]->u = id[store[i]->u];  
        store[i]->v = id[store[i]->v];  
        if (store[i]->u != store[i]->v) 
		{
			store[i]->wt -= cost[ve];  
		} 
    }  
	
	root = id[root];
	v = newnode;
	Arb(store,root,e,v);

}    


int main()
{
	int T;
	
	cin>>T;
	
	while(T--)
	{
		ans = 0;
		int N,M,s;
		int u,v,w,flag,e;
		cin>>N>>M>>s;
		vector<Edge*> Edges;
		
		e = M; // e = number of edges
		
		for(int i = 0;i<M;i++)
		{
			cin>>u>>v>>w;
			if(w>0)
			{
				if(v!=s )
				{
					struct Edge* p = createEdge(u-1,v-1,w);
					Edges.push_back(p);
				}
				else e--; // decreasing count of edges by one
				
					
			}
			else
			{
				flag = 1;
			}
			
		}
	
		if(flag == 1)  // Negative Edge Found
		{
			cout<<-1<<endl;
		}
		
		else // No Negative Edge Found
		{
			Arb(Edges,s-1,e,v);
			cout<<ans<<endl;
		}
	}
     return 0;
}

