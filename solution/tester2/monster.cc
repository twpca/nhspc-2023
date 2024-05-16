#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

void dfs(vector<int> const *g, int u, int p, int d, int *p_rec, int *d_rec){
   p_rec[u] = p;
   d_rec[u] = d;
   for(int v: g[u]) if(v != p){
      dfs(g, v, u, d+1, p_rec, d_rec);
   }
}

int main(){
   int f, m, n, r;
   scanf("%d%d%d%d", &f, &m, &n, &r);
   auto sc = [m, n](int i, int j, int k){
      return (i*m+j)*n+k;
   };
   vector<int> d(f*m*n, -1), bfs;
   while(r-- > 0){
      int i, j, k;
      scanf("%d%d%d", &i, &j, &k);
      --i; --j; --k;
      d[sc(i, j, k)] = 0;
      bfs.push_back(sc(i, j, k));
   }
   for(size_t i0=0; i0<bfs.size(); ++i0){
      int bf = bfs[i0], dbf = d[bf];
      int k = bf%n, j = bf/n%m, i = bf/n/m;
      int p;
#define PUSH(COND, I2, J2, K2) do{\
      if((COND) && d[p = sc((I2), (J2), (K2))]==-1){\
         d[p] = dbf+1; bfs.push_back(p);\
      }\
}while(0)
      PUSH(i>0, i-1, j, k);
      PUSH(i+1<f, i+1, j, k);
      PUSH(j>0, i, j-1, k);
      PUSH(j+1<m, i, j+1, k);
      PUSH(k>0, i, j, k-1);
      PUSH(k+1<n, i, j, k+1);
#undef PUSH
   }
   vector<int> djs(f*m*n, -1);
   auto djs_find = [djs=djs.data()](int i){
      int r = i;
      while(djs[r] != -1){
         r = djs[r];
      }
      while(djs[i] != -1){
         int j = djs[i];
         djs[i] = r;
         i = j;
      }
      return r;
   };
   vector<vector<int>> g(f*m*n);
   vector<bool> vis(f*m*n);
   for(size_t i0=bfs.size(); i0-->0; ){
      int u = bfs[i0];
      int k = u%n, j = u/n%m, i = u/n/m;
      vis[u] = true;
      int v, p, q;
#define ADD_EDGE(COND, I2, J2, K2) do{\
      if((COND) && vis[v = sc((I2), (J2), (K2))] && (p=djs_find(u))!=(q=djs_find(v))){\
         g[u].push_back(v);\
         g[v].push_back(u);\
         djs[q] = p;\
      }\
}while(0)
      ADD_EDGE(i>0, i-1, j, k);
      ADD_EDGE(i+1<f, i+1, j, k);
      ADD_EDGE(j>0, i, j-1, k);
      ADD_EDGE(j+1<m, i, j+1, k);
      ADD_EDGE(k>0, i, j, k-1);
      ADD_EDGE(k+1<n, i, j, k+1);
#undef ADD_EDGE
   }
   vector<vector<int>> p{vector<int>(f*m*n)};
   vector<int> dep(f*m*n);
   dfs(g.data(), 0, 0, 0, p[0].data(), dep.data());
   vector<vector<int>> dp{vector<int>(f*m*n)};
   for(int u=0; u<=f*m*n-1; ++u){
      dp[0][u] = min(d[u], d[p[0][u]]);
   }
   for(int i=0; any_of(p[i].cbegin(), p[i].cend(), [](int x){return x;}); ++i){
      p.push_back(vector<int>(f*m*n));
      dp.push_back(vector<int>(f*m*n));
      for(int u=0; u<=f*m*n-1; ++u){
         p[i+1][u] = p[i][p[i][u]];
         dp[i+1][u] = min(dp[i][u], dp[i][p[i][u]]);
      }
   }
   int q;
   scanf("%d", &q);
   while(q-- > 0){
      int s1, s2, s3, t1, t2, t3;
      scanf("%d%d%d%d%d%d", &s1, &s2, &s3, &t1, &t2, &t3);
      --s1; --s2; --s3; --t1; --t2; --t3;
      int s = sc(s1, s2, s3), t = sc(t1, t2, t3);
      if(dep[s] < dep[t]){
         swap(s, t);
      }
      int ans = min(d[s], d[t]);
      for(size_t i=p.size(); i-->0; ){
         if(dep[p[i][s]] >= dep[t]){
            ans = min(ans, dp[i][s]);
            s = p[i][s];
         }
      }
      if(s != t){
         for(size_t i=p.size(); i-->0; ){
            if(p[i][s] != p[i][t]){
               ans = min({ans, dp[i][s], dp[i][t]});
               s = p[i][s]; t = p[i][t];
            }
         }
         ans = min(ans, d[p[0][s]]);
      }
      printf("%d\n", ans);
   }
}
