#include <iostream>
using namespace std;

const int mod = 1e9 + 7;
const long long int LIMIT = 1000;

int partition[LIMIT + 1];
int even_pal[LIMIT + 1];
int ans[LIMIT + 1];

void init()
{
    partition[0] = 1;
    for (int i = 1; i <= LIMIT; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            partition[i] = (partition[i] + partition[i - j]) % mod;
        }
    }

    for (int i = 0; i <= LIMIT; i += 2)
    {
        even_pal[i] = partition[i / 2];
    }

    for (int i = 1; i <= LIMIT; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            ans[i] = (ans[i] + even_pal[i - j]) % mod;
        }
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
