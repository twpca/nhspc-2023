#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

const int MAXN = 3005;

vector<int> G[MAXN], RG[MAXN];
int reachable[MAXN], ans[MAXN];
int done[MAXN], vis[MAXN];

void dfs(int u, int *tag) 
{
    tag[u] = 1;
    for (int i : RG[u])
        if (!tag[i])
            dfs(i, tag);
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
    dfs(t, reachable);
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

    auto random_walk = [&](int current) 
    {
        fill_n(vis + 1, n, 0);
        for (int i = 1; i <= n; i++)
            if (reachable[i] && done[i])
                vis[i] = 1;
        for (int i = 1; i <= n; i++)
            if (!reachable[i] && !vis[i])
                dfs(i, vis);
        for (int i = 1; i <= n; i++)
            if (!done[i] && !vis[i])
                relax(i, current);
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
        random_walk(ans[best]);
    }

    if (ans[s] == n + 1) cout << "-1\n";
    else cout << ans[s] << "\n";
}
