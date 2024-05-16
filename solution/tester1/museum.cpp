#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int arr[MAXN], idx[MAXN], tag[MAXN];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> arr[i], idx[i] = i;
    sort(idx + 1, idx + n + 1, [&](int a, int b)
    {
         if (arr[a] != arr[b]) return arr[a] > arr[b];
         return a < b;
    });
    for (int i = 1; i <= k; i++)
        tag[idx[i]] = 1;
    long long ans = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (!tag[i]) cnt += 1;
        else ans += cnt;
    cout << ans << "\n";
}
