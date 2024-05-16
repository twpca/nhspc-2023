#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

constexpr int INF = 1'000'000'000;

int dfs(vector<int> const *g, vector<bool> &vis, int t, int u, int *dp){
   if(vis[u]){
      return dp[u];
   }
   vis[u] = true;
   int x_min = INF, x_max = -INF;
   for(int v: g[u]){
      int xv = dfs(g, vis, t, v, dp);
      x_min = min(x_min, xv);
      x_max = max(x_max, xv);
   }
   return dp[u] = x_min==x_max? x_min: x_min+1;
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
   vector<bool> vis(n);
   vector<int> dp(n, INF);
   vis[t] = true; dp[t] = 0;
   int ans = dfs(g.data(), vis, t, s, dp.data());
   printf("%d\n", ans<INF? ans: -1);
}
