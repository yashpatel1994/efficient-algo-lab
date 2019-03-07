#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

struct Edge {
    int to,cap,rev;
};

const int MAX_N = 56;
const int MAX_M = 1106;
const int INF = 1e9 + 7;

Edge MP(int _to,int _cap,int _rev) {
    return (Edge){_to,_cap,_rev};
}

vector<Edge> edg[MAX_M];
int iter[MAX_M];
int level[MAX_M];

void add_edge(int from,int to,int cap) {
    edg[from].push_back(MP(to,cap,edg[to].size()));
    edg[to].push_back(MP(from,0,edg[from].size()-1));
}

void bfs(int s) {
    memset(level,-1,sizeof(level));
    level[s]=0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int t=que.front();
        //cout<<"t = "<<t<<" , length = "<<edg[t].size()<<endl;
        que.pop();
        int len=edg[t].size();
        for (int i=0;len>i;i++) {
            Edge e=edg[t][i];
            //cout<<"e.to = "<<e.to<<" , e.cap = "<<e.cap<<endl;
            if (level[e.to] < 0 &&e.cap>0) {
                //cout<<"in "<<e.to<<endl;
                level[e.to] = level[t] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v,int t,int f) {
    if (v==t) return f;
    int len=edg[v].size();
    for (int &i=iter[v];len>i;i++) {
        Edge &e = edg[v][i];
        if (level[e.to] > level[v] && e.cap > 0) {
            int d=dfs(e.to,t,min(e.cap,f));
            if (d>0) {
                e.cap -= d;
                edg[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int Dinic(int s,int t) {
    int flow=0;
    while (true) {
        bfs(s);
        if (level[t] == -1) break;
        //cout<<"hello, world\n";
        memset(iter,0,sizeof(iter));
        int f;
        while ((f=dfs(s,t,INF)) > 0) {
            flow += f;
        }
    }
    return flow;
}

int main () {
    int m,w;
    while (scanf("%d %d",&m,&w) != EOF) {
        if (!m && !w) break;
        for (int x=0;MAX_M>x;x++) {
            edg[x].clear();
        }
        for (int i=2;m-1>=i;i++) {
            int a,b;
            scanf("%d %d",&a,&b);
            add_edge(a,a+m,b);
            add_edge(a+m,a,b);
        }
        for (int x=0;w>x;x++) {
            int i,j,k;
            scanf("%d %d %d",&i,&j,&k);
            if (i>j) swap(i,j);
            if (i==1 && j==m) {
                add_edge(i,j,k);
            }
            else if (i == 1) {
                add_edge(i,j+m,k);
            }
            else if (j==m) {
                add_edge(i,j,k);
            }
            else {
                add_edge(i,j+m,k);
                add_edge(j,i+m,k);
            }
        }
        printf("%d\n",Dinic(1,m));
    }
}