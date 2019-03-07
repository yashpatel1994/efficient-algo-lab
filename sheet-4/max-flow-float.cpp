#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

using node = int;

struct arc {
    node tail, head; 	// tail -> head
    int rev; 			// reverse arc index in head's incidence list
    float f, cap; 		// flow & capacity
    arc(node u, node v, int rev_, float cap_) : tail(u), head(v), rev(rev_), f(0), cap(cap_) { }
};

using graph = vector<vector<arc>>;

void add_arc(graph& G, node u, node v, float cap, float rcap=0) {
// Add to G a directed arc (u,v) of capacity cap
// and a reverse arc (v,u) of capacity rcap
    int uv_pos = G[u].size();
    int vu_pos = G[v].size();
    G[u].push_back( arc(u,v,vu_pos,cap) );
    G[v].push_back( arc(v,u,uv_pos,rcap) ); // reverse arc (crucial!)
}


struct dinic {
    graph& G; 				// input -- graph
    vector<node> dist; 	// BFS distance labels
    vector<int> work;		// DFS "next arc" counters
    float value; 			// output -- max flow value

    float dinic_dfs(node u, node t, float f) {
        // Try pushing f units of flow from u to t via a DFS
        // Return the amount of routed flow
        if (u == t) return f;
        int deg_u = G[u].size();
        for(int &i = work[u]; i < deg_u; i++) {
            arc &e = G[u][i];
            node v = e.head;
            if (e.f < e.cap && dist[v] == dist[u] + 1) {
                float df = dinic_dfs(v, t, min(f, e.cap - e.f));
                if (df > 0) { // Augmenting path found: update the flow
                    e.f += df;
                    G[e.head][e.rev].f -= df;
                    return df;
                }
            }
        }
        return 0; // Disconnected residual graph
    }

    bool dinic_bfs(node s, node t) {
        // Compute distance labels of a BFS rooted at s, store them in dist[0..n-1]
        // Return true iff t is reachable from s in the residual graph
        int n = G.size();
        dist.assign(n, -1);
        dist[s] = 0;
        queue<node> q; q.push(s);
        while(!q.empty()) {
            node u = q.front(); q.pop();
            for(auto& e: G[u]) {
                node v = e.head;
                if (dist[v] == -1 && e.f < e.cap) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist[t] != -1;
    }

    dinic(graph& G_, node s, node t) : G(G_), dist(G.size()), work(G.size()) {
        // Compute a maximum s-t flow in G
        int n = G.size();
        value = 0;
        float df;
        while (dinic_bfs(s, t)) {
            work.assign(n, 0); // reset DFS
            do {
                df = dinic_dfs(s, t, std::numeric_limits<float>::max());
                value += df;
            } while(df > 0);
        }
    }
};


int main() {

    int tc;

    cin >> tc;

    while(tc--){
        int n, m, s, t, en1, en2;
        cin >> n >> m;
        graph G(n+3);

        std::string l1;
        std::string l2;

        vector<int> source;
        vector<int> sink;

        cin >> s;
        cin.get();
        std::getline(cin, l1);

        std::istringstream iss(l1);
        while (iss >> en1) {
            source.push_back(en1);
        }

        cin >> t;
        cin.get();
        std::getline(cin, l2);

        std::istringstream iss1(l2);
        while (iss1 >> en2) {
            sink.push_back(en2);
        }


        for (int i = 0; i < s; i++) {
            add_arc(G, n+1, source[i], INFINITY);
        }

        for (int j = 0; j < t; j++) {
            add_arc(G, sink[j], n+2, INFINITY);
        }


        while(m--) {
            node u, v; float c;
            cin >> u >> v >> c;
            add_arc(G, u, v, c);
        }
        dinic max_flow(G, n+1, n+2);

        cout << std::fixed;
        cout << std::setprecision(2);

        cout << max_flow.value << "\n";
    }
}
