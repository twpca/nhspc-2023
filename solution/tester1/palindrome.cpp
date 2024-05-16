#include <iostream>
using namespace std;

const int mod = 1e9 + 7;

int mod_pow(int a, long long int n) 
{
    if (n == 0) return 1;
    int half = mod_pow(a, n / 2);
    half = (long long int)half * half % mod;
    if (n % 2 == 1) half = (long long int)half * a % mod;
    return half;
}

void solve()
{
    long long int n;
    cin >> n;
    cout << mod_pow(2, n / 2) << "\n";
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
