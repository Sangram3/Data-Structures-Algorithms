#include<bits\stdc++.h>

#define INF 999999
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////// 1 start
int be, fe, ce, te;

struct Node {
  int data;
  struct Node * next;
};

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

struct Node * createNode(int data) {
  struct Node * p;
  p = (struct Node * ) malloc(sizeof(struct Node));
  p -> data = data;
  p -> next = NULL;
  if (p != NULL)
    return p;

  else printf("Memory Error While Creating Node\n");
}

void EnQ(struct Queue * Q, int data) // insert at the rear end
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

int DeQ(struct Queue * Q) // delete from the front end
{
  int temp;
  if (Q -> front == NULL) printf("Queue Is Empty\n");

  else {
    struct Node * p;
    p = Q -> front;
    temp = Q -> front -> data;
    Q -> front = p -> next;
    if (Q -> front == NULL) Q -> rear = NULL;
    free(p);
  }

  return temp;
}





bool isEmptyQueue(struct Queue * Q) {
  if (Q -> front == NULL) return 1;
  else return 0;
}
void BFS(int s, vector < vector < int > > adj, int vis[], int par[], int depth[], int type) {
  be = 0;
  fe = 0;
  ce = 0;
  te = 0;

  if (type == 1) // Directed Graph
  {
    struct Queue * Q;
    int count, temp, temp1, i, dep, b;
    dep = 0;

    count = 1;
    temp1 = 0;

    Q = createQueue();
    EnQ(Q, s);
    vis[s] = 1;
    par[s] = s;
    depth[s] = dep;
    bool flag = 0;
    while (!(Q -> front == NULL)) {
      dep += 1;

      if (flag == 1)
        cout << count << " ";
      flag = 1;
      while (count--) {
        temp = DeQ(Q);
        for (i = 0; i < adj[temp].size(); i++) {
          b = adj[temp][i];
          if (vis[b] == 0) {
            te += 1;

            vis[b] = 1;
            depth[b] = dep;
            par[b] = temp;
            temp1 += 1;
            EnQ(Q, b);

          } else {
            while (depth[temp] > depth[b]) {
              temp = par[temp];
            }
            while (depth[b] > depth[temp]) {
              b = par[b];
            }

            if (temp == b) be += 1;
            else ce += 1;
          }
        }

      }
      count = temp1;
      temp1 = 0;

    }
    cout << 0 << " ";
  } else // Undirected Graph
  {
    struct Queue * Q;
    int count, temp, temp1, i, dep, b;
    count = 1;
    temp1 = 0;

    Q = createQueue();
    EnQ(Q, s);
    vis[s] = 1;
    bool flag = 0;
    while (!(Q -> front == NULL)) {
      dep += 1;
      if (flag == 1)
        cout << count << " ";
      flag = 1;
      while (count--) {
        temp = DeQ(Q);
        par[temp] = 1;
        for (i = 0; i < adj[temp].size(); i++) {
          b = adj[temp][i];
          if (vis[b] == 0) {
            te += 1;
            vis[b] = 1;
            temp1 += 1;
            EnQ(Q, b);

          }

        }

      }
      count = temp1;
      temp1 = 0;

    }
    cout << 0 << " ";

  }
}

////////////////////////////////////////////////////////////////////////////////////////////// 1 end

////////////////////////////////////////////////////////////////////////////////////////////// 2 start 

int timer = 1;
int tempd = 0;
void DFS(int s, vector < vector < int > > adj, int type, int N, int topped[], int popped[], int in [], int out[]) {
  stack < int > st;
  st.push(s);

  while (!st.empty()) {
    int temp = st.top();
    if (topped[temp] == 0) {
      tempd += 1;
      topped[temp] = 1;
      if ( in [temp] == -1) {
        in [temp] = timer;
        timer += 1;
      }
      int cnt = 0;

      for (int i = adj[temp].size() - 1; i >= 0; i--) {
        if (topped[adj[temp][i]] == 0) {
          st.push(adj[temp][i]);
          cnt += 1;
        }

      }
      if (cnt == 0) {
        if (popped[temp] == 0) {
          out[temp] = timer;
          timer += 1;
          popped[temp] = 1;
        }
        st.pop();
      }
    } else {
      if (popped[temp] == 0) {
        out[temp] = timer;
        timer += 1;
        popped[temp] = 1;
      }
      st.pop();
    }

  }

}

////////////////////////////////////////////////////////////////////////////////////////////// 2 end

////////////////////////////////////////////////////////////////////////////////////////////// 3 start

// toplogical sorting

vector < int > stac;
int topo_timer;
int topological_sort(int s, vector < vector < int > > adj, int vis[], int in [], int out[]) {
  vis[s] = 1; in [s] = topo_timer;
  topo_timer += 1;
  for (int i = 0; i < adj[s].size(); i++) {
    if (vis[adj[s][i]] == 0) {
      topological_sort(adj[s][i], adj, vis, in , out);
    } else {
      if ( in [s] > in [adj[s][i]] && out[adj[s][i]] == -1) return 0;
    }

  }
  out[s] = topo_timer;
  topo_timer += 1;
  stac.push_back(s);
  return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////// 3 end

////////////////////////////////////////////////////////////////////////////////////////////// 5 start
// Bellman Ford Algorithm

int relax = 0;
int perform = 0;
struct Edge {
  int to;
  int wt;
};

struct Edge * createEdge(int to, int wt) {
  struct Edge * p = (struct Edge * ) malloc(sizeof(struct Edge));
  p -> to = to;
  p -> wt = wt;
  return p;
}

void BellmanFord(int s, vector < vector < struct Edge * > > adj, int N) {
  int dist[N], present[N], count[N];

  for (int i = 0; i < N; i++) {
    if (i == s) dist[i] = 0;
    else dist[i] = INF;
    count[i] = 0;
    present[i] = 0;
  }

  queue < int > q;
  q.push(s);
  present[s] = 1;
  int flag = 0;
  while (!q.empty() && flag == 0) {
    int temp = q.front();
    q.pop();

    present[temp] = 0;
    for (int i = 0; i < adj[temp].size(); i++) {
      perform += 1;
      struct Edge * e = adj[temp][i];
      if (dist[e -> to] > dist[temp] + e -> wt) {
        dist[e -> to] = dist[temp] + e -> wt;
        relax += 1;
        if (present[e -> to] == 0) {
          q.push(e -> to);
          present[e -> to] = 1;
          count[e -> to] += 1;
          if (count[e -> to] > N) flag = 1;
        }
      }
    }
  }

  if (flag == 0) {
    for (int i = 0; i < N; i++) cout << dist[i] << " ";
    cout << perform << " " << relax << endl;
  } else cout << -1 << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////// 5 end
int main() {
  int T, Q, N, D, s, edge; // D = 1 Directed
  cin >> T;
  while (T--) {
    cin >> Q;

    if (Q == 1) {
      cin >> N >> D >> s;
      vector < vector < int > > adj;
      int edges = 0;
      int edge;
      int par[N];
      int depth[N];
      int vis[N];
      for (int i = 0; i < N; i++) vis[i] = 0;
      for (int i = 0; i < N; i++) {
        vector < int > vec;
        for (int j = 0; j < N; j++) {
          cin >> edge;

          if (edge == 1) {
            vec.push_back(j);
            edges += 1;
          }
        }
        adj.push_back(vec);
      }
      BFS(s - 1, adj, vis, par, depth, D);
      if (D == 1)
        cout << te << " " << be << " " << fe << " " << ce << endl;
      else {
        ce = edges / 2 - te;
        cout << te << " " << ce << endl;
      }
    }

    if (Q == 2) {
      cin >> N >> D >> s;
      int in [N];
      int out[N];
      int topped[N];
      int popped[N];

      for (int i = 0; i < N; i++) {
        out[i] = -1;
        topped[i] = 0;
        popped[i] = 0; in [i] = -1;
      }
      timer = 1;
      te = be = ce = fe = 0;

      vector < vector < int > > adj;
      int edges = 0;
      for (int i = 0; i < N; i++) {
        vector < int > vec;
        for (int j = 0; j < N; j++) {
          cin >> edge;

          if (edge == 1) {
            vec.push_back(j);
            edges += 1;
          }
        }
        adj.push_back(vec);
      }

      tempd = 0;
      DFS(s - 1, adj, D, N, topped, popped, in , out);
      if (tempd != 0)
        te += tempd - 1;
      for (int i = 0; i < N; i++) {
        if (topped[i] == 0) {
          tempd = 0;
          DFS(i, adj, D, N, topped, popped, in , out);
          if (tempd != 0)
            te += tempd;
        }
      }

      if (D == 1) {
        for (int i = 0; i < N; i++) {
          for (int j = 0; j < adj[i].size(); j++) {
            if (out[i] > out[adj[i][j]]) {
              if ( in [i] < in [adj[i][j]]) te += 1;
              else ce += 1;
            } else {
              if ( in [i] > in [adj[i][j]])
                be += 1;
            }
          }
          if (te > N - 1) {
            fe = te - (N - 1);
            te = N - 1;
          }

        }
        cout << out[s - 1] << " " << te << " " << be << " " << fe << " " << ce << endl;
      }
      if (D == 0) {
        // only te and back ward edges
        cout << out[s - 1] << " " << te << " " << edges / 2 - te << endl;
      }
    }

    if (Q == 3) {
      stac.clear();
      cin >> N;
      int edge;
      int vis[N];
      int in [N];
      int out[N];
      topo_timer = 0;
      vector < vector < int > > adj;

      for (int i = 0; i < N; i++) {
        vis[i] = 0; in [i] = -1;
        out[i] = -1;
      }

      for (int i = 0; i < N; i++) {
        vector < int > vec;
        for (int j = 0; j < N; j++) {
          cin >> edge;

          if (edge == 1) {
            vec.push_back(j);
          }
        }
        adj.push_back(vec);
      }
      int flag;
      for (int i = 0; i < N; i++) {
        if (vis[i] == 0) {
          flag = topological_sort(i, adj, vis, in , out);
          if (flag == 0) break;
        }
      }
      if (flag == 1) {
        for (int i = N - 1; i >= 0; i--) {
          cout << stac[i] + 1 << " ";
        }
        cout << endl;
      } else cout << -1 << endl;
    }

    if (Q == 4) {
      int N, D, s, wt;
      cin >> N >> D >> s;
      vector < pair < int, int > > adj[N];
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          cin >> wt;
          if (wt != INF && wt != 0) {
            adj[i].push_back({
              j,
              wt
            });
          }
        }
      }

      priority_queue < pair < int, int > , vector < pair < int, int > > , greater < pair < int, int > > > pq;

      vector < int > dist(N, INF);
      pq.push({
        0,
        s - 1
      }); // source is s-1 , distance = 0
      dist[s - 1] = 0;
      int flag = 0;
      while (!pq.empty() && flag == 0) {
        int curr = pq.top().second; // current node
        int curr_d = pq.top().first; // current distance
        pq.pop();

        for (pair < int, int > edge: adj[curr]) // traversing adjacenecy list of curr node
        {

          if (curr_d + edge.second < dist[edge.first]) {
            dist[edge.first] = curr_d + edge.second;
            pq.push({
              dist[edge.first],
              edge.first
            });
          }

          if (dist[edge.first] < 0) {
            flag = 1;
            break;
          }
        }

      }
      if (flag == 0) {
        for (int i = 0; i < N; i++) cout << dist[i] << " ";
        cout << endl;
      } else cout << -1 << endl;
    }

    if (Q == 5) {
      int N, D, s, wt;
      relax = 0;
      perform = 0;
      struct Edge * edge;
      cin >> N >> D >> s;

      vector < vector < struct Edge * >> adj;
      for (int i = 0; i < N; i++) {
        vector < struct Edge * > vec;
        for (int j = 0; j < N; j++) {
          cin >> wt;
          if (wt != 0 && wt != INF) {
            edge = createEdge(j, wt);
            vec.push_back(edge);
          }

        }
        adj.push_back(vec);
      }

      BellmanFord(s - 1, adj, N);

    }
  }
}
