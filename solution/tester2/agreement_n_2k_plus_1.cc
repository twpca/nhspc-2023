#include<algorithm>
#include<functional>
#include<numeric>
#include<queue>
#include<unordered_set>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

bool reduce(vector<int> *g, int u, int p, function<bool(int)> const &ok){
   bool res = ok(u);
   for(int &v: g[u]) if(v != p){
      bool rv = reduce(g, v, u, ok);
      if(!rv){
         v = -1;
      }
      res |= rv;
   }
   g[u].erase(remove(g[u].begin(), g[u].end(), -1), g[u].end());
   return res;
}

void smooth(vector<int> *g, vector<bool> &vis, int u){
   vis[u] = true;
   for(int &v: g[u]) if(!vis[v]){
      int q = u;
      while(g[v].size() == 2){
         if(g[v][0] == q){
            q = v;
            v = g[v][1];
         }else{
            q = v;
            v = g[v][0];
         }
         g[q].clear();
      }
      *find(g[v].begin(), g[v].end(), q) = u;
      smooth(g, vis, v);
   }
}

bool similar(int n, vector<int> const *g1, int m1, vector<int> const *g2, int m2){
   vector<int> phi(n+m1, -1), psi(n+m2, -1);
   iota(phi.begin(), phi.begin()+n, 0);
   iota(psi.begin(), psi.begin()+n, 0);
   vector<int> d1(n+m1), d2(n+m2);
   for(int u=0; u<=n+m1-1; ++u){
      d1[u] = (int)g1[u].size();
   }
   for(int u=0; u<=n+m2-1; ++u){
      d2[u] = (int)g2[u].size();
   }
   queue<int> q;
   for(int u=0; u<=n-1; ++u){
      q.push(u);
   }
   vector<bool> vis1(n+m1), vis2(n+m2);
   while(!q.empty()){
      int u1 = q.front(); q.pop();
      int u2 = phi[u1];
      vis1[u1] = vis2[u2] = true;
      if(d1[u1] == 0){
         if(d2[u2] != 0){
            return false;
         }
         continue;
      }
      if(d2[u2] != 1){
         return false;
      }
      int v1 = *find_if(g1[u1].cbegin(), g1[u1].cend(), [&vis1](int w){return !vis1[w];});
      int v2 = *find_if(g2[u2].cbegin(), g2[u2].cend(), [&vis2](int w){return !vis2[w];});
      if(phi[v1] == -1){
         if(psi[v2] == -1){
            phi[v1] = v2; psi[v2] = v1;
         }else{
            return false;
         }
      }else if(psi[v2] != v1){
         return false;
      }
      --d1[u1]; --d1[v1];
      --d2[u2]; --d2[v2];
      if(d1[v1] == 1){
         q.push(v1);
      }
   }
   return true;
}

bool check(int n, vector<pair<int, int>> const &e1, unordered_set<int> const &f1, int m1, vector<pair<int, int>> const &e2, unordered_set<int> const &f2, int m2){
   vector<vector<int>> g1(n+m1), g2(n+m2);
   for(int i=0; i<=(int)e1.size()-1; ++i) if(f1.find(i) == f1.cend()){
      auto [u, v] = e1[i];
      g1[u].push_back(v);
      g1[v].push_back(u);
   }
   vector<bool> vis1(n+m1);
   for(int u=0; u<=n-1; ++u) if(!vis1[u]){
      reduce(g1.data(), u, u, [n](int v){return v<=n-1;});
      smooth(g1.data(), vis1, u);
   }
   for(int i=0; i<=(int)e2.size()-1; ++i) if(f2.find(i) == f2.cend()){
      auto [u, v] = e2[i];
      g2[u].push_back(v);
      g2[v].push_back(u);
   }
   vector<bool> vis2(n+m2);
   for(int u=0; u<=n-1; ++u) if(!vis2[u]){
      reduce(g2.data(), u, u, [n](int v){return v<=n-1;});
      smooth(g2.data(), vis2, u);
   }
   return similar(n, g1.data(), m1, g2.data(), m2);
}

int main(){
   int n, m1, m2, k;
   scanf("%d%d%d%d", &n, &m1, &m2, &k);
   vector<pair<int, int>> e1;
   e1.reserve(n+m1-1);
   for(int i=0; i<=n+m1-2; ++i){
      int ui, vi;
      scanf("%d%d", &ui, &vi);
      e1.emplace_back(--ui, --vi);
   }
   vector<pair<int, int>> e2;
   e2.reserve(n+m2-1);
   for(int i=0; i<=n+m2-2; ++i){
      int ui, vi;
      scanf("%d%d", &ui, &vi);
      e2.emplace_back(--ui, --vi);
   }
   if(check(n, e1, {}, m1, e2, {}, m2)){
      puts("0");
      return 0;
   }
   if(k == 0){
      puts("-1");
      return 0;
   }
   int s = 0;
   for(int i1=0; i1<=(int)e1.size()-1; ++i1){
      for(int i2=0; i2<=(int)e2.size()-1; ++i2){
         s += check(n, e1, {i1}, m1, e2, {i2}, m2);
      }
   }
   if(s > 0){
      printf("1\n%d\n", s);
      return 0;
   }
   if(k == 1){
      puts("-1");
      return 0;
   }
   for(int i1=0; i1<=(int)e1.size()-1; ++i1) for(int j1=i1+1; j1<=(int)e1.size()-1; ++j1){
      for(int i2=0; i2<=(int)e2.size()-1; ++i2) for(int j2=i2+1; j2<=(int)e2.size()-1; ++j2){
         s += check(n, e1, {i1, j1}, m1, e2, {i2, j2}, m2);
      }
   }
   if(s > 0){
      printf("2\n%d\n", s);
   }else{
      puts("-1");
   }
}
