#include"testlib.h"
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

int subtask(int argc, char **argv){
   for(int i=0; i+1<argc; ++i){
      if(!strcmp(argv[i], "--testcase")){
         return atoi(argv[i+1]);
      }
   }
   abort();
}

constexpr int N_MIN = 1;
constexpr int N_MAX = 3000;
constexpr int M_MIN = 1;
constexpr int M_MAX = 30000;

using i64 = long long;

void dfs1(vector<int> const *dag, vector<bool> &vis, int u, vector<int> &tsr){
   vis[u] = true;
   for(int v: dag[u]) if(!vis[v]){
      dfs1(dag, vis, v, tsr);
   }
   tsr.push_back(u);
}

bool acyclic(vector<int> const *grev, vector<bool> &vis, int u){
   vis[u] = true;
   for(int v: grev[u]) if(!vis[v]){
      return false;
   }
   return true;
}

int main(int argc, char **argv){
   registerValidation(argc, argv);
   int s = subtask(argc, argv);
   int n = inf.readInt(N_MIN, N_MAX, "n");
   inf.readChar(' ');
   int m = inf.readInt(M_MIN, M_MAX, "m");
   inf.readChar('\n');
   if(s == 1){
      ensuref(m == n-1, "G is not a rooted tree.");
   }
   unordered_map<i64, int> um;
   vector<vector<int>> g(n), grev(n);
   for(int i=1; i<=m; ++i){
      char var[16];
      sprintf(var, "u[%d]", i);
      int ui = inf.readInt(1, n, var);
      inf.readChar(' ');
      var[0] = 'v';
      int vi = inf.readInt(1, n, var);
      inf.readChar('\n');
      //ensuref(ui != vi, "u[%d] = v[%d] = %d.", i, i, ui);
      auto [jt, ok] = um.emplace((i64)ui*n+vi, i);
      ensuref(ok, "(u[%d], v[%d]) = (u[%d], v[%d]) = (%d, %d).", jt->second, jt->second, i, i, ui, vi);
      --ui; --vi;
      g[ui].push_back(vi);
      grev[vi].push_back(ui);
   }
   if(s==1 || s==2){
      vector<bool> vis(n);
      vector<int> tsr;
      for(int u=0; u<=n-1; ++u) if(!vis[u]){
         dfs1(g.data(), vis, u, tsr);
      }
      vis.flip();
      for(int i=n-1; i>=0; --i){
         ensuref(acyclic(grev.data(), vis, tsr[i]), "G contains a cycle.");
      }
      if(s == 1){
         vector<bool> indeg(n);
         for(int u=0; u<=n-1; ++u) for(int v: g[u]){
            ensuref(!indeg[v], "G is not a rooted tree.");
            indeg[v] = true;
         }
      }
   }
   inf.readInt(1, n, "s");
   inf.readChar(' ');
   inf.readInt(1, n, "t");
   inf.readChar('\n');
   inf.readEof();
}
