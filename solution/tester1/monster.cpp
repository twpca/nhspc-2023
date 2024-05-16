#include <iostream>
#include <queue>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAXN = 200005;

struct Coord
{
    int x, y, z;  
};

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &e) const 
    {
        return w > e.w;
    }
};

struct DSU 
{
    int sz[MAXN], boss[MAXN], up[MAXN];
    void init(int n)
    {
        iota(boss, boss + n, 0);
        fill_n(sz, n, 1);
    }
    int get_boss(int x)
    {
        while (x != boss[x])
            x = boss[x];
        return x;
    }
    bool Union(int x, int y, int v)
    {
        x = get_boss(x), y = get_boss(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) swap(x, y);
        boss[x] = y;
        up[x] = v;
        sz[y] += sz[x];
        return true;
    }
    int get_min(int x, int y)
    {
        int res = INF;
        while (x != y)
        {
            if (sz[x] > sz[y]) swap(x, y);
            res = min(res, up[x]);
            x = boss[x];
        }
        return res;
    }
} dsu;

int dx[6] = {1, -1, 0, 0, 0, 0}, dy[6] = {0, 0, 1, -1, 0, 0}, dz[6] = {0, 0, 0, 0, 1, -1};

int main()
{
    int f, m, n;
    cin >> f >> m >> n;
    vector<vector<vector<int>>> dis(f, vector<vector<int>>(m, vector<int>(n, INF)));
    vector<vector<vector<int>>> num(f, vector<vector<int>>(m, vector<int>(n, -1)));
    queue<Coord> q;

    auto check = [&](int x, int y, int z)
    {
        return !(x < 0 || x >= f || y < 0 || y >= m || z < 0 || z >= n);  
    };

    auto relax = [&](int x, int y, int z, int d)
    {
        if (check(x, y, z) && dis[x][y][z] > d)
        {
            dis[x][y][z] = d;
            q.push(Coord{x, y, z});
        }
    };

    int r;
    cin >> r;
    while (r--) 
    {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--, z--;
        relax(x, y, z, 0);
    }

    while (!q.empty())
    {
        auto [x, y, z] = q.front();
        q.pop();
        for (int i = 0; i < 6; i++)
        {
            relax(x + dx[i], y + dy[i], z + dz[i], dis[x][y][z] + 1);
        }
    }

    int tp = 0;
    for (int i = 0; i < f; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                num[i][j][k] = tp++;

    vector<Edge> edges;

    auto add_edge = [&](int x1, int y1, int z1, int x2, int y2, int z2)
    {
        if (!check(x2, y2, z2)) return;
        int u = num[x1][y1][z1];
        int v = num[x2][y2][z2];
        int w = min(dis[x1][y1][z1], dis[x2][y2][z2]);
        edges.push_back(Edge{u, v, w});
    };

    for (int i = 0; i < f; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                for (int d = 0; d < 6; d++)
                    add_edge(i, j, k, i + dx[d], j + dy[d], k + dz[d]);

    sort(edges.begin(), edges.end());
    dsu.init(f * m * n);
    for (auto [u, v, w] : edges)
        dsu.Union(u, v, w);

    int querys;
    cin >> querys;
    while (querys--)
    {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        x1--, y1--, z1--, x2--, y2--, z2--;
        int ans = dsu.get_min(num[x1][y1][z1], num[x2][y2][z2]);
        ans = min(ans, dis[x1][y1][z1]);
        ans = min(ans, dis[x2][y2][z2]);
        cout << ans << "\n";
    }
}
