#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 3005;

vector<int> G[MAXN];

int dfs(int u, const int &t) 
{
    if (u == t) return 0;
    if (G[u].empty()) return -1;
    int ans = -1;
    for (int i : G[u])
    {
        int res = dfs(i, t);
        if (res != -1)
            ans = res;
    }
    if (int(G[u].size()) > 1 && ans != -1)
        ans += 1;
    return ans;
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

    int ans = dfs(s, t);
    cout << ans << "\n";
}
