#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 3005;

vector<int> G[MAXN];
int ans[MAXN], vis[MAXN];

void dfs(int u) 
{
    vis[u] = 1;
    if (G[u].empty()) return;
    int mi = MAXN, mx = 0;
    for (int i : G[u])
    {
        if (!vis[i])
            dfs(i);
        mi = min(mi, ans[i] + 1);
        mx = max(mx, ans[i]);
    }
    ans[u] = min(mi, mx);
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
    }
    cin >> s >> t;

    fill_n(ans + 1, n, n + 1);
    ans[t] = 0, vis[t] = 1;

    if (!vis[s])
        dfs(s);

    if (ans[s] == n + 1) cout << "-1\n";
    else cout << ans[s] << "\n";
}
