#include <iostream>
using namespace std;

const int mod = 1e9 + 7;
const long long int LIMIT = 1000000;

int partition[LIMIT + 1];
int even_pal[LIMIT + 1];
int ans[LIMIT + 1];

void init()
{
    partition[0] = partition[1] = 1;
    for (int i = 2; i <= LIMIT; i++)
    {
        partition[i] = (partition[i - 1] + partition[i - 1]) % mod;
    }

    for (int i = 0; i <= LIMIT; i += 2)
    {
        even_pal[i] = partition[i / 2];
    }

    ans[0] = 1;
    for (int i = 1; i <= LIMIT; i++)
    {
        ans[i] = (ans[i - 1] + even_pal[i]) % mod;
    }
}

void solve()
{
    long long int n;
    cin >> n;
    if (n > LIMIT) exit(0);
    cout << ans[n] << "\n";
}

int main() 
{
    init();
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++)
    {
        solve();
    }
    return 0;
}
