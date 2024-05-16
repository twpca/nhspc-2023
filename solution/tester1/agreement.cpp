#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include <random>
using namespace std;

const int MAXN = 305;

struct DSU 
{
    int boss[MAXN];
    void init(int n)
    {
        iota(boss + 1, boss + n + 1, 1);
    }
    int get_boss(int x)
    {
        if (boss[x] == x) return x;
        return boss[x] = get_boss(boss[x]);
    }
    bool Union(int x, int y)
    {
        x = get_boss(x), y = get_boss(y);
        if (x == y) return false;
        boss[x] = y;
        return true;
    }
} dsu1, dsu2;

unsigned long long seed;
unsigned long long shift(unsigned long long x) 
{
    x ^= x << 13; 
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

unsigned long long base[MAXN];
int vis[MAXN];

unsigned long long dfs(int u, int f, const vector<int> *G, const int &n, const int &boss) 
{
    vis[u] = 1;
    if (u <= n && u != f) 
    {
        if (boss) dsu1.Union(u, boss); 
        return base[u];
    }
    if (G[u].size() == 1 && u != f) return 0; 
    unsigned long long sum = 0;
    vector<unsigned long long> child;
    for (int i : G[u])
        if (i != f)
        {
            unsigned long long res = dfs(i, u, G, n, boss);
            if (res != 0)
                child.push_back(res);
        }
    if (int(child.size()) > 1) sum += seed;
    for (auto v : child)
    {
        if (int(child.size()) > 1)
            v = shift(v);
        sum += v;
    }       
    return sum;
}

vector<pair<int, int>> T1_edges;
vector<int> T2[MAXN], F1[MAXN], F2[MAXN], SG[MAXN];
int pa2[MAXN], in2[MAXN], out2[MAXN], dft2, stk[MAXN], stktp;
pair<int, int> dp[MAXN][5];

void cal(int u, int f, const int &k)
{
    for (int i = 0; i <= k; i++)
        dp[u][i] = make_pair(0, 0);
    if (vis[u]) dp[u][0].second = 1;
    else dp[u][0].first = 1;
    for (int i : SG[u])
        if (i != f) 
        {
            cal(i, u, k);
            for (int a = 0; a <= k + 1; a++)
                dp[0][a] = make_pair(0, 0);
            for (int a = 0; a <= k; a++)
                for (int b = 0; a + b <= k; b++)
                {
                    dp[0][a + b].first += dp[u][a].first * dp[i][b].first;
                    dp[0][a + b + 1].first += dp[u][a].first * (dp[i][b].first + dp[i][b].second);
                    dp[0][a + b].second += dp[u][a].first * dp[i][b].second;
                    dp[0][a + b].second += dp[u][a].second * dp[i][b].first;
                    dp[0][a + b + 1].second += dp[u][a].second * (dp[i][b].first + dp[i][b].second);
                }
            for (int a = 0; a <= k; a++)
                dp[u][a] = dp[0][a];
        }
}

void pre(int u, int f, const int &n)
{
    in2[u] = ++dft2, pa2[u] = f;
    if (u <= n)
        stk[++stktp] = u;
    for (int i : T2[u])
        if (i != f)
            pre(i, u, n);
    out2[u] = dft2;
}

bool ancestor2(int u, int v)
{
    return in2[u] <= in2[v] && out2[u] >= out2[v];
}

bool handle(vector<int> group)
{
    int lca = group[0];
    while (!ancestor2(lca, group.back()))
        lca = pa2[lca];
    if (vis[lca]) return false;
    vis[lca] = 1;
    for (int i : group)
        for (; i != lca; i = dsu2.get_boss(i))
        {
            if (vis[i]) return false;
            vis[i] = 1;
            F2[i].push_back(pa2[i]);
            F2[pa2[i]].push_back(i);
            dsu2.Union(i, pa2[i]);
        }
    return true;
}

unsigned long long val[MAXN];
vector<int> group[MAXN];

int solve(int n, int m1, int m2, int k)
{
    vector<int> mask(n + m1 - 1);
    for (int i = 1; i <= k; i++)
        mask[n + m1 - 1 - i] = 1;
    int ans = 0;

    auto check = [&]()
    {
        for (int i = 1; i <= n + m1; i++)
            F1[i].clear(), vis[i] = 0;
        for (int i = 1; i <= n; i++)
            group[i].clear();

        dsu1.init(n);
        for (int i = 0; i < n + m1 - 1; i++)
            if (!mask[i])
            {
                auto [u, v] = T1_edges[i];
                F1[u].push_back(v);
                F1[v].push_back(u);
            }
        for (int i = 1; i <= n; i++)
        {
            if (vis[i]) continue;
            val[i] = dfs(i, i, F1, n, i);
        }
        for (int i = 1; i <= n; i++)
        {
            group[dsu1.get_boss(stk[i])].push_back(stk[i]);
        }
        dsu2.init(n + m2);
        for (int i = 1; i <= n + m2; i++)
            vis[i] = 0, F2[i].clear();
        for (int i = 1; i <= n; i++)
        {
            if (dsu1.get_boss(i) == i)
            {
                if (!handle(group[i])) return 0;
                unsigned long long res = dfs(i, i, F2, n, 0);
                if (res != val[i]) return 0;
            }
        }
        for (int i = 1; i <= n + m2; i++)
            SG[i].clear(), group[i].clear(), vis[i] = 0;
        for (int i = 1; i <= n + m2; i++) 
            group[dsu2.get_boss(i)].push_back(i);
        for (int i = 1; i <= n + m2; i++)
        {
            if (dsu2.get_boss(i) != i) continue;
            vis[i] = 1;
            for (int j : group[i])
                for (int p : T2[j])
                    if (!vis[dsu2.get_boss(p)])
                    {
                        SG[i].push_back(dsu2.get_boss(p));
                        vis[dsu2.get_boss(p)] = 1;
                    }
            vis[i] = 0;
            for (int j : group[i])
                for (int p : T2[j])
                    vis[dsu2.get_boss(p)] = 0;
        }
        for (int i = 1; i <= n; i++)
            vis[dsu2.get_boss(i)] = 1;
        cal(dsu2.get_boss(1), dsu2.get_boss(1), k);
        return dp[dsu2.get_boss(1)][k].second;
    };

    do 
    {
        ans += check();
    } while (next_permutation(mask.begin(), mask.end()));
    return ans;
}

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m1, m2, k;
    cin >> n >> m1 >> m2 >> k;
    mt19937_64 rnd(20231208);
    seed = rnd();
    for (int i = 1; i <= n; i++)
        base[i] = rnd();
    for (int i = 1; i < n + m1; i++)
    {
        int u, v;
        cin >> u >> v;
        T1_edges.emplace_back(u, v);
    }
    for (int i = 1; i < n + m2; i++)
    {
        int u, v;
        cin >> u >> v;
        T2[u].push_back(v);
        T2[v].push_back(u);
    }
    pre(1, 1, n);
    for (int i = 0; i <= k; i++)
    {
        int res = solve(n, m1, m2, i);
        if (res > 0)
        {
            cout << i << "\n";
            if (i) cout << res << "\n";
            return 0;
        }
    }
    cout << "-1\n";
}
