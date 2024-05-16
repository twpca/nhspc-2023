#include<algorithm>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

constexpr int INF = 1'000'000'000;

void tsr_get(vector<int> *dag, vector<bool> &vis, int u, vector<int> &tsr){
   vis[u] = true;
   for(int v: dag[u]) if(!vis[v]){
      tsr_get(dag, vis, v, tsr);
   }
   tsr.push_back(u);
}

void scc_collect(vector<int> *grev, vector<bool> &vis, int u, vector<int> &scc){
   vis[u] = true;
   scc.push_back(u);
   for(int v: grev[u]) if(!vis[v]){
      scc_collect(grev, vis, v, scc);
   }
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<vector<int>> g(n);
   while(m-- > 0){
      int u, v;
      scanf("%d%d", &u, &v);
      --u; --v;
      g[u].push_back(v);
   }
   int s, t;
   scanf("%d%d", &s, &t);
   --s; --t;
   g[t].clear();
   vector<bool> vis(n);
   vector<int> ts;
   for(int u=0; u<=n-1; ++u) if(!vis[u]){
      tsr_get(g.data(), vis, u, ts);
   }
   vis.flip();
   reverse(ts.begin(), ts.end());
   vector<vector<int>> grev(n);
   for(int u=0; u<=n-1; ++u) for(int v: g[u]){
      grev[v].push_back(u);
   }
   vector<vector<int>> scc;
   vector<int> scc_no(n);
   for(int u: ts) if(!vis[u]){
      scc.push_back({});
      scc_collect(grev.data(), vis, u, scc.back());
      for(int v: scc.back()){
         scc_no[v] = (int)scc.size()-1;
      }
   }
   vector<int> ans(n, INF);
   while(!scc.empty()){
      vector<int> c = move(scc.back()); scc.pop_back();
      if(c[0] == t){
         ans[t] = 0; scc_no[t] = -1;
         continue;
      }
      int id = scc_no[c[0]], ans_min = INF, ans_max = -INF, u_min = -1;
      for(int u: c) for(int v: g[u]) if(scc_no[v] != id){
         if(ans_min > ans[v]){
            ans_min = ans[v];
            u_min = u;
         }
         ans_max = max(ans_max, ans[v]);
      }
      if(u_min==-1 || ans_min==ans_max){
         for(int u: c){
            ans[u] = ans_min;
            scc_no[u] = -1;
         }
         continue;
      }
      ans[u_min] = ans_min+1;
      scc_no[u_min] = -1;
      if(c.size() == 1){
         continue;
      }
      for(int u: c){
         vis[u] = false;
      }
      vis[u_min] = true;
      ts.clear();
      for(int u: c) if(!vis[u]){
         tsr_get(g.data(), vis, u, ts);
      }
      for(int u: ts){
         vis[u] = false;
      }
      reverse(ts.begin(), ts.end());
      for(int u: ts) if(!vis[u]){
         scc.push_back({});
         scc_collect(grev.data(), vis, u, scc.back());
         for(int v: scc.back()){
            scc_no[v] = (int)scc.size()-1;
         }
      }
   }
   printf("%d\n", ans[s]<INF? ans[s]: -1);
}
