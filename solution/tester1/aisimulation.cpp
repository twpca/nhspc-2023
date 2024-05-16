#include <iostream>
#include <string>
using namespace std;

int arr[105];
int vis[1 << 10];

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, k, t;
    cin >> n >> k >> t;
    for (int i = 0; i < n; i++)
    {
        string x;
        cin >> x;
        for (char c : x)
        {
            arr[i] <<= 1;
            if (c == '1') arr[i] |= 1;
        }
        vis[arr[i]] = 1;
    }
    for (int i = 0; i < (1 << k); i++)
    {
        if (vis[i] || __builtin_popcount(i) > 3) continue;
        int flag = 1;
        for (int j = 0; j < (1 << k) && flag; j++)
            if (__builtin_popcount(j) == t)
            {
                int cur = 0;
                for (int p = 0; p < n && !cur; p++)
                    if ((arr[p] & j) == (i & j))
                        cur = 1;
                flag &= cur;
            }
        if (flag) 
        {
            for (int j = k - 1; j >= 0; --j)
                cout << (i >> j & 1);
            cout << "\n";
            return 0;
        }
    }
    cout << "none\n";
}
