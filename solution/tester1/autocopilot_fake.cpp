#include<bits/stdc++.h>
using namespace std;
const int N = 200005, S = 200005;
vector<int> adj[N], Revadj[N], ord;
vector<int> SCC[S];
bool vis[N]; 
int SCC_id[N], out_degree[N], n, m;
bool used[N];
void RevDFS(int x) {
    vis[x] = 1;
    for(auto v : Revadj[x]) {
        if(!vis[v]) RevDFS(v);
    }
    ord.push_back(x);
}

void mark_scc(int x, int id) {
    SCC_id[x] = id;
    SCC[id].push_back(x);
}
void DFS(int x, int id) {
    mark_scc(x, id);
    for(auto v : adj[x]) {
        if(!SCC_id[v]) DFS(v, id);
    }
}
int scc_id;
void Kosaraju() {
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) RevDFS(i);
    }

    scc_id = 0;
    for(int i = n - 1; i >= 0; i--) {
        int x = ord[i];
        if(!SCC_id[x]) DFS(x, ++scc_id);
    }
}
void add_edge(int a, int b) {
    adj[a].push_back(b);
    Revadj[b].push_back(a);
}

int dp[N];
int main() {
    cin >> n >> m;
    vector<pair<int, int>> tmp_edges;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        tmp_edges.emplace_back(u, v);
    }

    int src, dst;
    cin >> src >> dst;

    for(pair<int, int> edge : tmp_edges) {
        int u = edge.first, v = edge.second;

        if(u == dst) continue; // Remove all outgoing edges from t.
        add_edge(u, v);
        out_degree[u]++;
    }

    Kosaraju(); // Compute all SCCs
    // the id of SCC is 1 ~ scc_id
    // SCC_id[x] = vertex x in the SCC SCC_id[x]
    // SCC[s] stores which vertex in SCC s

    const int INF = 0x3f3f3f3f;
    memset(dp, INF, sizeof(dp)); // ans
    memset(used, false, sizeof(used));

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Q
    map<int, vector<int>> exit_to_x; // exit_to_x[v] store the edge from x (which in SCC s) to exit v 
    
    // Proceed in the reversed topological order
    for(int s = 1; s <= scc_id; s++) {
        if(SCC_id[dst] == s) {
            dp[dst] = 0;
            assert(SCC[s].size() == 1);
            continue;
        }

        // init
        while(!pq.empty()) pq.pop();
        exit_to_x.clear();

        int max_dp = -1; // X
        // maximum dp[] value among all exit points
        for(int x : SCC[s]) {
            for(int v : adj[x]) {
                if(SCC_id[x] == SCC_id[v]) continue;
                // find an exit v: x -> v
                max_dp = max(max_dp, dp[v]);
                exit_to_x[v].push_back(x);
                used[v] = false;
                pq.push({dp[v], v});
            }
        }

        if(max_dp != -1) {
            for(int x : SCC[s]) {
                dp[x] = max_dp;
            }
        }

        // calculate the dp in SCC s
        // run dijkstra-like
        while(!pq.empty()) {
            int v = pq.top().second;
            pq.pop();
            
            if(used[v]) continue;
            used[v] = true;

            // two case:
            // 1. v is an exit
            // 2. v is in SCC s
            for(int x : ((SCC_id[v] == s) ? Revadj[v] : exit_to_x[v])) {
                if(SCC_id[x] != s) continue;
                out_degree[x]--;
                bool relax = false;
                if(out_degree[x] == 0) {
                    if(dp[x] > dp[v]) {
                        dp[x] = dp[v];
                        relax = true;
                    }
                } else {
                    if(dp[x] > dp[v] + 1) {
                        dp[x] = dp[v] + 1;
                        relax = true;
                    }
                }

                if(relax) pq.push({dp[x], x});
            }
        }
    }

    if(dp[src] >= INF) cout << "-1\n";
    else cout << dp[src] << "\n";
}