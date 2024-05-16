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
    for (int i = 0; i < P; i++)
    {
        for (int j = i; j < P; j++)
        {
            int cur = 0;
            for (int k = 1; k <= n; k++)
            {
                if ((brr[k] + i) % P > arr[k] || (brr[k] + j) % P > arr[k])
                    cur += 1;
            }
            ans = max(ans, cur);
        }
    }

    cout << ans << "\n";
}
