#include <bits/stdc++.h>
#include "testlib.h"

using bset = std::vector<std::string>;

void print(int T, const bset &bt) {
    std::cout << bt.size() << ' ' << bt[0].size() << ' ' << T << '\n';
    for (auto b: bt) {
        std::cout << b << '\n';
    }
}

bset rndCase(int n, int k, int min1 = 0, int max1 = -1) {
    bset res;

    if (max1 == -1) max1 = k;

    {
        if (min1 <= 1 && n >= 10) {
            auto tmp = std::string(k, '0');
            for (int i=0;i<k;++i) {
                tmp[i] = '1';
                res.emplace_back(tmp);
                n--;
                tmp[i] = '0';
            }
            
        }
    }
    while (n--) {
        int one = rnd.next(min1, max1);
        int zero = k - one;

        std::string b = std::string(zero, '0') + std::string(one, '1');
        shuffle(b.begin(), b.end());
        res.emplace_back(b);
    }

    return res;
}

bset all1Case(int n, int k) {
    return rndCase(n,k,k);
}
bset all0Case(int n, int k) {
    bset res;

    while (n--) {
        int one = 0;
        int zero = k - one;

        std::string b = std::string(zero, '0') + std::string(one, '1');
        shuffle(b.begin(), b.end());
        res.emplace_back(b);
    }

    return res;
}
bset MaskCase(int n, int k) {
    bset res;

    std::string base;
    {
        int one = 3;
        int zero = k - one;
        base = std::string(zero, '0') + std::string(one, '1');
        shuffle(base.begin(), base.end());
    }
    while (n--) {
        int one = rnd.next(k);
        int zero = k - one;

        std::string b = std::string(zero, '0') + std::string(one, '1');
        shuffle(b.begin(), b.end());
        for (int i=0;i<k;++i) {
            if (base[i] == '0')
                b[i] = '0';
        }
        res.emplace_back(b);
    }

    return res;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int c = opt<int>(1);
    int n = opt<int>(2);
    int k = opt<int>(3);
    int t = opt<int>(4);

    switch (c) {
    case 1:
        print(t, rndCase(n, k, 4, 4));
        break;
    case 2:
        print(t, rndCase(n, k));
        break;
    case 3:
        print(t, all1Case(n, k));
        break;
    case 4:
        print(t, all0Case(n, k));
        break;
    case 5:
        print(t, rndCase(n, k, 0, 3));
        break;
    case 6:
        print(t, rndCase(n, k, 0, 4));
        break;
    case 7:
        print(t, rndCase(n, k, 0, k));
        break;
    case 8:
        print(t, MaskCase(n,k));
        break;
    default:
        __builtin_unreachable();
    }
}