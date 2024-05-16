#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 5005;

int arr[MAX_N], brr[MAX_N];
int vis[MAX_N], shot[MAX_N][MAX_N], cnt[MAX_N];

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
    for (int i = 1; i <= n; i++)
    {
        vals.push_back((P + arr[i] + 1 - brr[i]) % P);
    }
    sort(vals.begin(), vals.end()), vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (int i = 0; i < int(vals.size()); i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if ((brr[j] + vals[i]) % P > arr[j])
                shot[i][j] = 1, cnt[i] += 1;
        }
    }
    int ans = 0, cur = 0;
    for (int i = 0; i < int(vals.size()); i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (vis[j] != shot[i][j])
            {
                int v = 2 * shot[i][j] - 1;
                cur += v;
                for (int k = 0; k < int(vals.size()); k++)
                    cnt[k] -= shot[k][j] * v;
                vis[j] = shot[i][j];
            }
        }
        for (int j = 0; j < int(vals.size()); j++)
        {
            ans = max(ans, cur + cnt[j]);
        }
    }

    cout << ans << "\n";
}
