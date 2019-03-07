#include <iostream>
#include <limits>
#include <cstdio>
#include "bits/stdc++.h"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ios>

using namespace std;

bool isBipartiteUtil(vector <vector<long int> > &G, long int src, long int colorArr[])
{
    colorArr[src] = 1;
    long int V = G.size();

    queue <long int> q;
    q.push(src);

    while (!q.empty())
    {
        long int u = q.front();
        q.pop();

        if (G[u][u] == 1)
            return false;

        for (long int v = 0; v < V; ++v)
        {
            if (G[u][v] && colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
    return true;
}

// Returns true if G[][] is Bipartite, else false
bool isBipartite(vector <vector<long int> > &G)
{
    long int V = G.size();
    long int colorArr[V];
    for (long int i = 0; i < V; ++i)
        colorArr[i] = -1;

    // This code is to handle disconnected graph
    for (long int i = 0; i < V; i++)
        if (colorArr[i] == -1)
            if (!isBipartiteUtil(G, i, colorArr))
                return false;

    return true;
}

int main(){

        while(true) {
            long int n, m, u, v;
			if (!(cin >> n >> m)) {
				break;
			}

            //cin >> n >> m;
            //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (n == ' ' || m == ' ') { cin >> n >> m; }
            vector<vector<long int> > G(n, vector<long int>(n));

            for (long int i = 0; i < m; i++) {
                cin >> u >> v;
                G[u][v] = 1;
                G[v][u] = 1;
                // cout << 1000;
            }
            if (isBipartite(G)) { cout << "bipartite" << "\n"; }
            else {
                cout << "not bipartite" << "\n";
            }
        }
    return 0;
    }
