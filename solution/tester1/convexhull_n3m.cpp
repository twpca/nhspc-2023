#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
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

const int MAXA = 800;
const int MAXC = 30;
const int MAXN = 45;

int vis[MAXC][MAXC], ans[MAXA + 1];
Point s1[MAXN], s2[MAXN];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> s1[i].first >> s1[i].second;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> s2[i].first >> s2[i].second;

    }

    for (int i = 0; i < m; i++)
    {
        vis[s2[i].first][s2[i].second] = 1;
    }

    auto check_vis = [&](Point p)
    {
        if (p.first < 0 || p.second < 0 || p.first >= MAXC || p.second >= MAXC) return 0;
        return vis[p.first][p.second];
    };

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++) 
            {
                int area = abs(cross(s1[k] - s1[i], s1[j] - s1[i]));
                if (area == 0) continue;
                for (int t = 0; t < m; t++)
                {
                    Point diff = s2[t] - s1[i];
                    if (check_vis(diff + s1[j]) && check_vis(diff + s1[k]))
                        ans[area] = 1;
                }
            }

    cout << accumulate(ans + 1, ans + MAXA + 1, 0) << "\n";
    for (int i = 1; i <= MAXA; i++)
        if (ans[i])
            cout << i << "\n";
}
