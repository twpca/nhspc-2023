#include <iostream>
using namespace std;

const int MAX_N = 200005;

int arr[MAX_N], brr[MAX_N];

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

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            int s = (P + arr[i] + 1 - brr[i]) % P;
            int t = (P + arr[j] + 1 - brr[j]) % P;
            int cur = 0;
            for (int k = 1; k <= n; k++)
            {
                if ((brr[k] + s) % P > arr[k] || (brr[k] + t) % P > arr[k])
                    cur += 1;
            }
            ans = max(ans, cur);
        }
    }

    cout << ans << "\n";
}
