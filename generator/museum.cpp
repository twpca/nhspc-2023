#include <bits/stdc++.h>
#include "testlib.h"

const int MAX_C = 1'000'000'000;
int LIM_C = MAX_C;
int UNI;
const int MAX_K = 100'000;
const int MAX_N = 100'000;

std::mt19937_64 rng;

void print(int K, const std::vector<int> &c) {
    std::cout << c.size() << ' ' << K << '\n';
    for (size_t i = 0; i < c.size(); ++i) {
        if (i != 0)
            std::cout << ' ';
        std::cout << c[i];
    }
    std::cout << '\n';
}

std::vector<int> rnduniCase(int n) {
    std::vector<int> v;
    std::set<int> st;
    while (v.size() < n) {
        auto r = rnd.next(1, LIM_C);
        if (st.find(r) != st.end())
            continue;
        st.emplace(r);
        v.emplace_back(r);
    }
    return v;
}

std::vector<int> rndCase(int n) {
    if (UNI) return rnduniCase(n);
    std::vector<int> v;
    while (n--)
        v.emplace_back(rnd.next(1, LIM_C));
    return v;
}

std::vector<int> invCase1(int n) {
    auto x = rndCase(n);
    sort(x.begin(), x.end(), std::greater<int>());
    return x;
}

std::vector<int> invCase2(int n) {
    auto x = rndCase(n);
    sort(x.begin(), x.end());
    return x;
}

std::vector<int> invCase3(int n) {
    auto x = invCase2(n);
    int q = sqrt(n);
    while (q--) {
        int i = rnd.next(n);
        int j = rnd.next(n);
        std::swap(x[i], x[j]);
    }
    return x;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int c = opt<int>(1);
    int k = opt<int>(2);
    int n = opt<int>(3);
    int mx = opt<int>(4);
    int uni = opt<int>(5); 

    LIM_C = std::min(mx, LIM_C);
    UNI = !!uni;

    switch (c) {
    case 1:
        print(k, rndCase(n));
        break;
    case 2:
        print(k, invCase1(n));
        break;
    case 3:
        print(k, invCase2(n));
        break;
    case 4:
        print(k, invCase3(n));
        break;
    default:
        __builtin_unreachable();
    }
}
