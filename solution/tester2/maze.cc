#include<algorithm>
#include<array>
#include<queue>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<bool> wall(n*m);
   array<int, 3> bead{n*m, n*m, n*m};
   int bead_top = 0;
   for(int i=0; i<=n-1; ++i) for(int j=0; j<=m-1; ++j){
      char sij;
      scanf(" %c", &sij);
      wall[i*m+j] = sij=='w';
      if(sij == 'b'){
         bead[bead_top++] = i*m+j;
      }
   }
   array<vector<int>, 4> drop_pos;
#define DROP_POS_GET(IDX, OUTER_FOR, INNER_FOR, I2, J2) do{\
   drop_pos[IDX] = vector<int>(n*m+1, n*m);\
   OUTER_FOR{\
      int x = n*m;\
      INNER_FOR{\
         if(wall[i*m+j]){\
            x = (I2)*m+(J2);\
         }else{\
            drop_pos[IDX][i*m+j] = x;\
         }\
      }\
   }\
}while(0)
   DROP_POS_GET(0, for(int j=0; j<=m-1; ++j), for(int i=n-1; i>=0; --i), i-1, j);
   DROP_POS_GET(1, for(int i=0; i<=n-1; ++i), for(int j=0; j<=m-1; ++j), i, j+1);
   DROP_POS_GET(2, for(int j=0; j<=m-1; ++j), for(int i=0; i<=n-1; ++i), i+1, j);
   DROP_POS_GET(3, for(int i=0; i<=n-1; ++i), for(int j=m-1; j>=0; --j), i, j-1);
#undef DROP_POS_GET
   int n_pos = n*m+1, init = 0;
   for(int p: bead){
      init = n_pos*init + p;
   }
   queue<pair<int, int>> bfs;
   vector<bool> vis(4*n_pos*n_pos*n_pos);
   bfs.emplace(init, 0);
   vis[init] = true;
   array<int, 4> dpos{-m, 1, m, -1};
   while(!bfs.empty()){
      auto [s, a] = bfs.front(); bfs.pop();
      if(s%(n_pos*n_pos*n_pos) == n_pos*n_pos*n_pos-1){
         printf("%d\n", a);
         return 0;
      }
      array<int, 3> b;
      for(int i=2; i>=0; --i){
         b[i] = s%n_pos; s /= n_pos;
      }
#define G_FORCE(D) do{\
      array<int, 3> b2;\
      for(int i=0; i<=2; ++i){\
         b2[i] = drop_pos[D][b[i]];\
      }\
      sort(b2.begin(), b2.end());\
      if(b2[0]==b2[1] && b2[1]!=n_pos-1){\
         if(b2[1] == b2[2]){\
            b2[2] = b2[0] + 2*dpos[D];\
         }\
         b2[1] = b2[0] + dpos[D];\
      }else if(b2[1]==b2[2] && b2[2]!=n_pos-1){\
         b2[2] = b2[1] + dpos[D];\
      }\
      sort(b2.begin(), b2.end());\
      int s2 = (D);\
      for(int p: b2){\
         s2 = n_pos*s2 + p;\
      }\
      if(!vis[s2]){\
         bfs.emplace(s2, a+1);\
         vis[s2] = true;\
      }\
}while(0)
      G_FORCE((s+1)%4);
      G_FORCE((s+3)%4);
#undef G_FORCE
   }
   puts("-1");
}
