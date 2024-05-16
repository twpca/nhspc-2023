#include<vector>
#include<cstdio>
using namespace std;

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
      if(i>0 && d[p=sc(i-1, j, k)]==-1){
         d[p] = dbf+1; bfs.push_back(p);
      }
      if(i+1<f && d[p=sc(i+1, j, k)]==-1){
         d[p] = dbf+1; bfs.push_back(p);
      }
      if(j>0 && d[p=sc(i, j-1, k)]==-1){
         d[p] = dbf+1; bfs.push_back(p);
      }
      if(j+1<m && d[p=sc(i, j+1, k)]==-1){
         d[p] = dbf+1; bfs.push_back(p);
      }
      if(k>0 && d[p=sc(i, j, k-1)]==-1){
         d[p] = dbf+1; bfs.push_back(p);
      }
      if(k+1<n && d[p=sc(i, j, k+1)]==-1){
         d[p] = dbf+1; bfs.push_back(p);
      }
   }
   int n_query;
   scanf("%d", &n_query);
   if(n_query > 1){
      return 0;
   }
   int a, b, c, x, y, z;
   scanf("%d%d%d%d%d%d", &a, &b, &c, &x, &y, &z);
   --a; --b; --c; --x; --y; --z;
   int s = sc(a, b, c), t = sc(x, y, z);
   if(s == t){
      printf("%d\n", d[s]);
      return 0;
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
   vector<bool> vis(f*m*n);
   for(size_t i0=bfs.size(); i0-->0; ){
      int u = bfs[i0];
      int k = u%n, j = u/n%m, i = u/n/m;
      vis[u] = true;
      int v, p, q;
      if(i>0 && vis[v=sc(i-1, j, k)] && (p=djs_find(u))!=(q=djs_find(v))){
         djs[q] = p;
      }
      if(i+1<f && vis[v=sc(i+1, j, k)] && (p=djs_find(u))!=(q=djs_find(v))){
         djs[q] = p;
      }
      if(j>0 && vis[v=sc(i, j-1, k)] && (p=djs_find(u))!=(q=djs_find(v))){
         djs[q] = p;
      }
      if(j+1<m && vis[v=sc(i, j+1, k)] && (p=djs_find(u))!=(q=djs_find(v))){
         djs[q] = p;
      }
      if(k>0 && vis[v=sc(i, j, k-1)] && (p=djs_find(u))!=(q=djs_find(v))){
         djs[q] = p;
      }
      if(k+1<n && vis[v=sc(i, j, k+1)] && (p=djs_find(u))!=(q=djs_find(v))){
         djs[q] = p;
      }
      if(djs_find(s) == djs_find(t)){
         printf("%d\n", d[u]);
         return 0;
      }
   }
}
