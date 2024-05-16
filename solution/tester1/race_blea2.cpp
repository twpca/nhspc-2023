#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

const int MAX_N = 200005;

class Segtree 
{
private:
    struct node 
    {
        int mx, lazy;
    } seg[MAX_N << 3];
    int n;
    void up(int rt) 
    {
        seg[rt].mx = max(seg[rt << 1].mx, seg[rt << 1 | 1].mx);
    }
    void give_tag(int rt, int v)
    {
        seg[rt].mx += v;
        seg[rt].lazy += v;
    }
    void down(int rt)
    {
        give_tag(rt << 1, seg[rt].lazy);
        give_tag(rt << 1 | 1, seg[rt].lazy);
        seg[rt].lazy = 0;
    }
    void build(int l, int r, int rt) 
    {
        seg[rt].mx = seg[rt].lazy = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
    }
    void modify(int L, int R, int l, int r, int rt, int v)
    {
        if (L <= l && R >= r) return give_tag(rt, v);
        down(rt);
        int mid = (l + r) >> 1;
        if (L <= mid) modify(L, R, l, mid, rt << 1, v);
        if (R > mid) modify(L, R, mid + 1, r, rt << 1 | 1, v);
        up(rt);
    }
public:
    void init(int _n)
    {
        n = _n;
        build(1, n, 1);
    }
    void modify(int l, int r, int v)
    {
        if (l <= r)
            modify(l, r, 1, n, 1, v);
    }
    int get_max()
    {
        return seg[1].mx;
    }
} segtree;

int arr[MAX_N], brr[MAX_N];
pair<int, int> itv[MAX_N]; // [l, r)
vector<int> addition[MAX_N * 2], deletion[MAX_N * 2];

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, P;
    cin >> n >> P;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> brr[i];
    }

    vector<int> vals;
    vals.push_back(0), vals.push_back(P);
    for (int i = 1; i <= n; i++)
    {
        if (brr[i] > arr[i]) 
        {
            itv[i] = make_pair(P + arr[i] - brr[i] + 1, P);
        }
        else
        {
            itv[i] = make_pair(arr[i] - brr[i] + 1, P - brr[i]);
        }
        vals.push_back(itv[i].first);
        vals.push_back(itv[i].second);
    }
    sort(vals.begin(), vals.end()), vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    segtree.init(vals.size());
    for (int i = 1; i <= n; i++)
    {
        itv[i].first = upper_bound(vals.begin(), vals.end(), itv[i].first) - vals.begin();
        itv[i].second = upper_bound(vals.begin(), vals.end(), itv[i].second) - vals.begin();
        addition[itv[i].first].push_back(i);
        deletion[itv[i].second].push_back(i);
        segtree.modify(itv[i].first, itv[i].second - 1, 1);
    }

    int ans = 0, cnt = 0;
    for (int i = 1; i < int(vals.size()); i++)
    {
        for (int j : addition[i])
        {
            cnt += 1;
            segtree.modify(itv[j].first, itv[j].second - 1, -1);
        }
        for (int j : deletion[i])
        {
            cnt -= 1;
            segtree.modify(itv[j].first, itv[j].second - 1, 1);
        }
        ans = max(ans, cnt + segtree.get_max()); 
    }

    cout << ans << "\n";
}
