#include <bitset>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int N, K, T;
vector<uint32_t> users;
set<uint32_t> users_set;

bool check(uint32_t q) {
    if (users_set.find(q) != users_set.end())
        return false;

    string mask = string(K - T, '0') + string(T, '1');
    do {
        uint32_t bmask = bitset<32>(mask).to_ulong();
        bool ok = false;
        for (auto &u: users)
            if ( (q&bmask) == (u&bmask) ) {
                ok = true;
                break;
            }
        if (!ok) return false;
    } while (next_permutation(mask.begin(), mask.end()));
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> K >> T;

    for (int i = 0; i < N; ++i) {
        bitset<16> b;
        cin >> b;

        users.emplace_back(b.to_ulong());
        users_set.emplace(b.to_ulong());
    }

    // O(K^3 * C(K,T) * n)
    uint32_t q = 0;
    do {
        // 0 bits
        if (check(q = 0))
            goto end_of_search;
        // 1 bits
        for (int i = 0; i < K; ++i)
            if (check(q = (1 << i)))
                goto end_of_search;
        // 2 bits
        for (int i = 0; i < K; ++i)
            for (int j = i + 1; j < K; ++j)
                if (check(q = (1 << i) | (1 << j)))
                    goto end_of_search;
        // 3 bits
        for (int i = 0; i < K; ++i)
            for (int j = i + 1; j < K; ++j)
                for (int k = j + 1; k < K; ++k)
                    if (check(q = (1 << i) | (1 << j) | (1 << k)))
                        goto end_of_search;
        // fail
        q = -1;
    end_of_search:
        break;
    } while (false);

    if (q == -1)
        cout << "none\n";
    else {
        for (int i = K-1; i >= 0; --i) {
            cout << ((q >> i) & 1);
        }
        cout << '\n';
    }
}