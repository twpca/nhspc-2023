#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

const int MAXN = 3005;

vector<int> G[MAXN], RG[MAXN], topo;
int reachable[MAXN], ans[MAXN];
int done[MAXN], vis[MAXN];

void dfs(int u) 
{
    reachable[u] = 1;
    for (int i : RG[u])
        if (!reachable[i])
            dfs(i);
}

void topo_order(int u) 
{
    vis[u] = 1;
    for (int i : RG[u])
        if (!vis[i] && !done[i])
            topo_order(i);
    topo.push_back(u);
}

int random_for_last_SCC(int u, int t) 
{
    vis[u] = t;
    int res = 0;
    for (int i : G[u])
        if (vis[i] < t)
            res = max(res, ans[i]);
        else if (vis[i] > t)
            res = max(res, random_for_last_SCC(i, t));
    return res;
}

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, s, t;
    cin >> n >> m;
    while (m--) 
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        RG[v].push_back(u);
    }
    cin >> s >> t;

    int remain = n;

    fill_n(ans + 1, n, n + 1);
    dfs(t);
    for (int i = 1; i <= n; i++)
        if (!reachable[i])
            done[i] = 1, --remain;

    auto relax = [&](int u, int d) 
    {
        if (ans[u] > d) 
        {
            ans[u] = d;
        }
    };

    auto random_walk = [&]() 
    {
        fill_n(vis + 1, n, 0);
        topo.clear();
        for (int i = 1; i <= n; i++)
            if (!vis[i] && !done[i])
                topo_order(i);
        fill_n(vis + 1, n, n + 1);
        for (int i = 1; i <= n; i++)
            if (done[i])
                vis[i] = 0;
        for (int ti = 1; !topo.empty(); ti++) 
        {
            int val = random_for_last_SCC(topo.back(), ti);
            while (!topo.empty() && vis[topo.back()] == ti) 
            {
                relax(topo.back(), val);
                topo.pop_back();
            }
        }
    };

    relax(t, 0);
    while (remain > 0) 
    {
        int best = -1, best_val = n + 2;
        for (int i = 1; i <= n; i++)
            if (!done[i]) 
            {
                if (best_val > ans[i])
                    best = i, best_val = ans[i];
            }
        done[best] = 1, --remain;
        for (int i : RG[best])
            relax(i, ans[best] + 1);
        random_walk();
    }

    if (ans[s] == n + 1) cout << "-1\n";
    else cout << ans[s] << "\n";
}
