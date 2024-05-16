#include <bitset>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "testlib_cms.h"

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

int main(int argc, char *argv[]) {
    inf.maxFileSize = 1024 * 1024 * 1024; // 1024MB
    setName("aisimulation special judge");
    registerTestlibCmd(argc, argv);

    // read inputs
    N = inf.readInt();
    K = inf.readInt();
    T = inf.readInt();
    inf.readEoln();
    for (int i = 0; i < N; ++i) {
        string s = inf.readString();

        users.emplace_back(bitset<16>(s).to_ulong());
        users_set.emplace(bitset<16>(s).to_ulong());
    }
    // read ans (for none)
    string answer = ans.readString();

    // read user output
    uint32_t q = 0;
    {
        string buf = ouf.readString();
        long long buf_len = buf.size();

#define T_NONE "none"
        if (answer == T_NONE) {
            if (buf == T_NONE) {
                quitf(_ok, "LGTM");
            } else {
                quitf(_wa, "WA");
            }
        }

        if (buf == T_NONE) {
            quitf(_wa, "WA");
        }

        if (buf_len != K) {
            quitf(_wa, "output size not match, should be %d, not %lld", K, buf_len);
        }

        int one = 0;
        for (char c: buf) {
            if ( c !='0' && c!= '1' ) {
                quitf(_wa, "not a binary string with char = int(%d)", int(c));
            }
            if (c == '1') {
                one ++;
            }
            if (one > 3) {
                quitf(_wa, "I am very poor QQ. too many '1'.");
            }
        }
        q = bitset<16>(buf).to_ulong();
    }

    if (check(q)) {
        quitf(_ok, "LGTM");
    } else {
        quitf(_wa, "WA");
    }
}
