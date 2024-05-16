#include"testlib.h"
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

constexpr int N_MIN = 2;
constexpr int N_MAX = 300;
constexpr int M_MIN = 0;
constexpr int V_MAX[] = {300, 300, 300, 30, 300};
constexpr int K_MIN = 0;
constexpr int K_MAX[] = {2, 0, 1, 2, 2};

int main(int argc, char **argv){
   registerValidation(argc, argv);
   int s = subtask(argc, argv);
   int n = inf.readInt(N_MIN, N_MAX, "n");
   inf.readChar(' ');
   int m1 = inf.readInt(M_MIN, V_MAX[s]-n, "m[1]");
   inf.readChar(' ');
   int m2 = inf.readInt(M_MIN, V_MAX[s]-n, "m[2]");
   inf.readChar(' ');
   inf.readInt(K_MIN, K_MAX[s], "k");
   inf.readChar('\n');
#define CHECK_T(I) do{\
   char var[16];\
   vector<int> deg(n+m##I), djs(n+m##I, -1);\
   auto djs_find = [djs=djs.data()](int i){\
      int r = i;\
      while(djs[r] != -1){\
         r = djs[r];\
      }\
      while(djs[i] != -1){\
         int j = djs[i];\
         djs[i] = r;\
         i = j;\
      }\
      return r;\
   };\
   for(int i=1; i<=n+m##I-1; ++i){\
      sprintf(var, "u[%d]", i);\
      int ui = inf.readInt(1, n+m##I, var);\
      inf.readChar(' ');\
      var[0] = 'v';\
      int vi = inf.readInt(1, n+m##I, var);\
      inf.readChar('\n');\
      --ui; --vi;\
      ++deg[ui]; ++deg[vi];\
      int p = djs_find(ui), q = djs_find(vi);\
      ensuref(p!=q, "During the construction of T[%d], trying to connect %d and %d in the same connected component.", I, ui+1, vi+1);\
      djs[q] = p;\
   }\
   for(int u=0; u<=n-1; ++u){\
      ensuref(deg[u]==1, "deg(%d) = %d in T[%d], while n = %d.", u+1, deg[u], I, n);\
   }\
   for(int u=n; u<=n+m##I-1; ++u){\
      ensuref(deg[u]>=3, "deg(%d) = %d in T[%d], while n = %d.", u+1, deg[u], I, n);\
   }\
}while(0)
   CHECK_T(1);
   CHECK_T(2);
#undef CHECK_TI
   inf.readEof();
}
