#include <iostream>
#include <utility>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

typedef pair<int, int> Point;

Point operator+(const Point &p, const Point &q) 
{
    return Point(p.first + q.first, p.second + q.second);
}
Point operator-(const Point &p, const Point &q) 
{
    return Point(p.first - q.first, p.second - q.second);
}
int cross(const Point &p, const Point &q)
{
    return p.first * q.second - p.second * q.first;
}

const int RANGEA = 1605;
const int MINA = 800;
const int MAXC = 30;
const int MAXN = 45;

int vis[MAXC][MAXC];
Point s1[MAXN], s2[MAXN];
bitset<RANGEA> dp[MAXN], ans;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> s1[i].first >> s1[i].second;
        vis[s1[i].first][s1[i].second] = 1;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> s2[i].first >> s2[i].second;
    }
    vector<pair<int, int>> vec;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i != j)
                vec.emplace_back(i, j);
        }
    }

    sort(vec.begin(), vec.end(), [&](pair<int, int> u, pair<int, int> v) 
    {
        Point vec_u = s2[u.second] - s2[u.first];
        Point vec_v = s2[v.second] - s2[v.first];
        int U = (vec_u.second < 0 || (vec_u.second == 0 && vec_u.first < 0)); 
        int V = (vec_v.second < 0 || (vec_v.second == 0 && vec_v.first < 0)); 
        if (U != V)
            return U < V;
        return cross(vec_u, vec_v) > 0;
    });

    auto check_vis = [&](Point p)
    {
        if (p.first < 0 || p.second < 0 || p.first >= MAXC || p.second >= MAXC) return 0;
        return vis[p.first][p.second];
    };

    for (int b = 0; b < n; b++)
    {
        for (int r = 0; r < m; r++)
        {
            // Enumerate the lowest point s2[r], and its bijection is s1[b]
            Point diff = s1[b] - s2[r];
            for (int i = 0; i < m; i++)
                dp[i].reset();
            /*
            Convex hull can be constructed by edges in increasing polar angle order, starting with the lowest point s2[r].

            Sort all edges (i, j) by the polar angle of \vec{i, j},
            dp[e][u][a] := Consider 1st ~ e-th edges, when the convex hull construction stops at point u halfway through with the use of e-th edge, whether the current area given by the Shoelace formula can be a?

            Implementation: Since e.second == u, we can eliminate the first dimension of the state to speed up the transition.

            Time complexity: O(m^2A / w), where A is the range of area, w is the word size.
            */
            for (auto [i, j] : vec) 
            {
                if (!check_vis(s2[j] + diff)) continue;
                int cur = cross(s2[i], s2[j]);
                if (cur > 0)
                    dp[j] |= dp[i] << cur; 
                else 
                    dp[j] |= dp[i] >> -cur;
                if (i == r)
                    dp[j][cur + MINA] = 1;
            }
            ans |= dp[r];
        }
    }
    ans >>= MINA, ans[0] = 0;
    cout << ans.count() << "\n";
    for (int i = 1; i <= MINA; i++)
        if (ans[i])
            cout << i << "\n";
}
