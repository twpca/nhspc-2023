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

const int RANGEA = 1605;
const int MINA = 800;
const int MAXC = 30;
const int MAXN = 45;

int vis[MAXC][MAXC], ans[MINA + 1];
Point s1[MAXN], s2[MAXN];

vector<Point> convex_hull(vector<Point> arr) 
{
    sort(arr.begin(), arr.end());
    vector<Point> res(1, arr[0]);
    for (int i = 1; i < int(arr.size()); i++)
    {
        while (int(res.size()) > 1 && cross(res.back() - res[int(res.size()) - 2], arr[i] - res[int(res.size()) - 2]) <= 0)
            res.pop_back();
        res.push_back(arr[i]);
    }
    reverse(arr.begin(), arr.end());
    for (int i = 1, t = res.size(); i < int(arr.size()); i++)
    {
        while (int(res.size()) > t && cross(res.back() - res[int(res.size()) - 2], arr[i] - res[int(res.size()) - 2]) <= 0)
            res.pop_back();
        res.push_back(arr[i]);
    }
    if (int(arr.size()) > 1) res.pop_back();
    return res;
}

int get_area(const vector<Point> &convex) 
{
    int res = 0;
    for (int i = 0; i < int(convex.size()); i++)
    {
        res += cross(convex[i], convex[(i + 1) % int(convex.size())]);
    }
    return res;
}

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

    if (n > m) 
    { 
        swap(n, m);
        for (int i = 0; i < m; i++)
            swap(s1[i], s2[i]);
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

    for (long long int i = 1; i < (1LL << n); i++)
    {
        if ((i & (i - 1)) == 0) continue;
        vector<Point> arr;
        for (int j = 0; j < n; j++)
            if (i >> j & 1)
                arr.push_back(s1[j]);
        arr = convex_hull(arr);
        int cur = get_area(arr);
        if (cur == 0) continue;
        for (int j = 0; j < m; j++)
        {
            int flag = 1;
            Point diff = s2[j] - arr[0];
            for (Point p : arr)
                if (!check_vis(p + diff))
                {
                    flag = 0;
                    break;
                }
            if (flag) {
                ans[cur] = 1;
                break;
            }
        }
    }
    cout << accumulate(ans + 1, ans + MINA + 1, 0) << "\n";
    for (int i = 1; i <= MINA; i++)
        if (ans[i])
            cout << i << "\n";
}
