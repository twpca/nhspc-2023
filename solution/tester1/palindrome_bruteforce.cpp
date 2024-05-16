#include <iostream>
using namespace std;

const int mod = 1e9 + 7;

int cal(long long int n) 
{
    int res = 0;
    for (long long int i = 1; i * 2 <= n; i++) 
    {
        res += cal(n - i * 2);
        res %= mod;
    }
    res += 1;
    res %= mod;
    return res;
}

void solve()
{
    long long int n;
    cin >> n;
    cout << cal(n) << "\n";
}

int main() 
{
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++)
    {
        solve();
    }
    return 0;
}
