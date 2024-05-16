#include<algorithm>
#include<numeric>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;

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

int main(){
   int n, m1, m2, k;
   scanf("%d%d%d%d", &n, &m1, &m2, &k);
   vector<vector<int>> g1(n+m1);
   for(int i=0; i<=n+m1-2; ++i){
      int ui, vi;
      scanf("%d%d", &ui, &vi);
      --ui; --vi;
      g1[ui].push_back(vi);
      g1[vi].push_back(ui);
   }
   vector<vector<int>> g2(n+m2);
   for(int i=0; i<=n+m2-2; ++i){
      int ui, vi;
      scanf("%d%d", &ui, &vi);
      --ui; --vi;
      g2[ui].push_back(vi);
      g2[vi].push_back(ui);
   }
   if(similar(n, g1.data(), m1, g2.data(), m2)){
      puts("0");
   }else{
      puts("-1");
   }
}
