#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    // weight, index, flag
    vector<tuple<int, int, int>> c;

    for (int i = 0; i < N; ++i) {
        int weight;
        cin >> weight;
        c.emplace_back(weight, i, 0);
    }

#define flag(idx) get<2>(c[(idx)])
    stable_sort(c.begin(), c.end(), [](auto a, auto b) {
        if (get<0>(a) != get<0>(b))
            return get<0>(a) > get<0>(b);
        return get<1>(a) < get<1>(b);
    });
    for (int i = 0; i < K; ++i)
        flag(i) = 1;

    sort(c.begin(), c.end(), [](auto a, auto b) {
        // sort by index
        return get<1>(a) < get<1>(b);
    });

    // move distance max to (10^6)^2
    long long ans = 0;
    int j = 0;
    for (int i = 0; i < K; ++i) {
        if (flag(i) == 0) {
            j = max(j, i + 1);
            while (flag(j) == 0)
                j++;
            swap(c[i], c[j]);
            ans += j - i;
        }
    }

    cout << ans << '\n';
}