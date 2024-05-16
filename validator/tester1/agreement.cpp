#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <numeric>
#include <vector>

int subtask(int argc, char **argv)
{
   for (int i = 0; i + 1 < argc; i++) 
   {
      if (!strcmp(argv[i], "--testcase"))
      {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

constexpr int MIN_N = 2;
constexpr int MAX_N[] = {300, 300, 300, 30, 300};
constexpr int MIN_M = 0;
constexpr int MAX_S[] = {300, 300, 300, 30, 300};
constexpr int MIN_K = 0;
constexpr int MAX_K[] = {2, 0, 1, 2, 2};

struct DSU 
{
    int n, conn;
    std::vector<int> boss;
    DSU(int _n): n(_n), conn(_n), boss(n)
    {
        std::iota(boss.begin(), boss.end(), 0);
    }
    int get_boss(int x)
    {
        if (boss[x] == x) return x;
        return boss[x] = get_boss(boss[x]);
    }
    bool Union(int x, int y)
    {
        x = get_boss(x), y = get_boss(y);
        if (x == y) return false;
        boss[x] = y;
        conn--;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readChar(' ');
    int m1 = inf.readInt(MIN_M, MAX_S[s] - n, "m_1");
    inf.readChar(' ');
    int m2 = inf.readInt(MIN_M, MAX_S[s] - n, "m_2");
    inf.readChar(' ');
    int k = inf.readInt(MIN_K, MAX_K[s], "k");
    inf.readChar('\n');
    std::vector<int> deg1(n + m1), deg2(n + m2);
    DSU dsu1(n + m1), dsu2(n + m2);
    for (int i = 1; i < n + m1; i++)
    {
        int u = inf.readInt(1, n + m1, "u_" + std::to_string(i));
        inf.readChar(' '); 
        int v = inf.readInt(1, n + m1, "v_" + std::to_string(i));
        inf.readChar('\n');
        u--, v--;
        dsu1.Union(u, v);
        deg1[u]++, deg1[v]++;
    }
    for (int i = 1; i < n + m2; i++)
    {
        int u = inf.readInt(1, n + m2, "u'_" + std::to_string(i));
        inf.readChar(' '); 
        int v = inf.readInt(1, n + m2, "v'_" + std::to_string(i));
        inf.readChar('\n');
        u--, v--;
        dsu2.Union(u, v);
        deg2[u]++, deg2[v]++;
    }
    ensuref(dsu1.conn == 1, "T1 is not connected");
    ensuref(dsu2.conn == 1, "T2 is not connected");
    for (int i = 0; i < n; i++)
    {
        ensuref(deg1[i] == 1, "T1: deg %d != 1, which is %d", i + 1, deg1[i]);
        ensuref(deg2[i] == 1, "T2: deg %d != 1, which is %d", i + 1, deg2[i]);
    }
    for (int i = n; i < n + m1; i++)
        ensuref(deg1[i] >= 3, "T1: deg %d < 3, which is %d", i + 1, deg1[i]);
    for (int i = n; i < n + m2; i++)
        ensuref(deg2[i] >= 3, "T2: deg %d < 3, which is %d", i + 1, deg2[i]);
    inf.readEof();
    return 0;
}
