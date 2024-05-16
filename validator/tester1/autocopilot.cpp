#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

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

constexpr int MIN_N = 1;
constexpr int MAX_N[] = {3'000, 3'000, 3'000, 100, 3'000};
constexpr int MIN_M = 1;
constexpr int MAX_M[] = {30'000, 3'000, 30'000, 1'000, 30'000};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readChar(' ');
    int m;
    if (s == 1) m = inf.readInt(n - 1, n - 1, "m");
    else m = inf.readInt(MIN_M, MAX_M[s], "m");
    inf.readChar('\n');
    
    std::vector<std::vector<int>> G(n);
    std::set<std::pair<int, int>> edges;
    for (int i = 1; i <= m; i++)
    {
        int u = inf.readInt(1, n, "u_" + std::to_string(i));
        inf.readChar(' ');
        int v = inf.readInt(1, n, "v_" + std::to_string(i));
        inf.readChar('\n');
        u--, v--;
        G[u].push_back(v);
        ensuref(edges.insert(std::make_pair(u, v)).second, "duplicate edges: (%d, %d)", u + 1, v + 1);
    }

    int start = inf.readInt(1, n, "s");
    inf.readChar(' ');
    int target = inf.readInt(1, n, "t");
    inf.readChar('\n');

    std::vector<int> stk, vis(n), pl(n);
    auto dfs = [&](auto _dfs, int u) -> void
    {
        vis[u] = 1;
        for (int i : G[u])
            if (!vis[i])
                _dfs(_dfs, i);
        pl[u] = stk.size();
        stk.push_back(u);
    };

    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(dfs, i);

    if (s == 1)
    {
        int r = stk.back();
        stk.clear();
        std::fill(vis.begin(), vis.end(), 0);
        dfs(dfs, r);
        ensuref(int(stk.size()) == n, "no vertex can reach all vertices");
    }
    if (s == 2)
    {
        for (auto [u, v] : edges)
            ensuref(pl[u] > pl[v], "there is cycle in the graph");
    }
    
    inf.readEof();
    return 0;
}
