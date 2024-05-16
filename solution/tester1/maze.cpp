#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXN = 15;
const int INF = 1e9;

struct Coord 
{
    int x, y, z, dir;  
};

int dis[MAXN * MAXN + 1][MAXN * MAXN + 1][MAXN * MAXN + 1][4];
int num[MAXN][MAXN], nxt[MAXN * MAXN + 1][4];
pair<int, int> org[MAXN * MAXN + 1];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
char mp[MAXN][MAXN];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, tp = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mp[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            org[tp] = make_pair(i, j);
            num[i][j] = tp;
            fill_n(nxt[tp], 4, -1); 
            tp++;
        }
    for (int d = 0; d < 4; ++d)
    {
        auto dfs = [&](auto _dfs, int x, int y)
        {
            if (x < 0 || y < 0 || x >= n || y >= m) return tp;
            if (mp[x][y] == 'w') return -1;
            if (nxt[num[x][y]][d] != -1) return nxt[num[x][y]][d];
            int res = _dfs(_dfs, x + dx[d], y + dy[d]);
            if (res == -1) res = num[x][y];
            return nxt[num[x][y]][d] = res;
        };
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                dfs(dfs, i, j);
    }
    fill_n(nxt[tp], 4, tp);
    int sx = tp, sy = tp, sz = tp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mp[i][j] == 'b')
            {
                if (sx == tp) sx = num[i][j];
                else if (sy == tp) sy = num[i][j];
                else sz = num[i][j];
            }

    for (int i = 0; i <= tp; i++)
        for (int j = 0; j <= tp; j++)
            for (int k = 0; k <= tp; k++)
                 fill_n(dis[i][j][k], 4, INF);

    queue<Coord> q;

    auto prv = [&](int u, int d)
    {
        if (u == tp) return tp; 
        auto [x, y] = org[u];
        d ^= 2;
        return num[x + dx[d]][y + dy[d]];
    };

    auto relax = [&](int x, int y, int z, int dir, int d)
    {
        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);
        if (x >= 0 && y >= 0 && z >= 0) 
        {
            if (x == y) y = prv(y, dir);
            if (z == x || z == y) z = prv(y, dir);
            if (x > y) swap(x, y);
            if (y > z) swap(y, z);
            if (x > y) swap(x, y);
            if (dis[x][y][z][dir] > d) {
                dis[x][y][z][dir] = d;
                q.push(Coord{x, y, z, dir});
            }
        }
    };

    relax(sx, sy, sz, 0, 0);
    while (!q.empty())
    {
        auto [x, y, z, dir] = q.front();
        q.pop();
        int u = (dir + 3) % 4, v = (dir + 1) % 4, d = dis[x][y][z][dir];
        relax(nxt[x][u], nxt[y][u], nxt[z][u], u, d + 1);
        relax(nxt[x][v], nxt[y][v], nxt[z][v], v, d + 1);
    }

    int ans = *min_element(dis[tp][tp][tp], dis[tp][tp][tp] + 4);
    if (ans == INF) cout << "-1\n";
    else cout << ans << "\n";
}
