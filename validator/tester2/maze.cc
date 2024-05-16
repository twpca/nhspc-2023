#include"testlib.h"
#include<algorithm>
#include<iterator>
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
constexpr int N_MAX = 15;
constexpr int M_MIN = 1;
constexpr int M_MAX = 15;
constexpr char GRIDS[] = "bsw";
constexpr int K_MIN = 1;
constexpr int K_MAX[] = {3, 1, 2, 3};

int main(int argc, char **argv){
   registerValidation(argc, argv);
   int s = subtask(argc, argv);
   int n = inf.readInt(N_MIN, N_MAX, "n");
   inf.readChar(' ');
   int m = inf.readInt(M_MIN, M_MAX, "m");
   inf.readChar('\n');
   char maze[N_MAX][M_MAX];
   int k = 0;
   for(int i=0; i<=n-1; ++i) for(int j=0; j<=m-1; ++j){
      maze[i][j] = inf.readChar();
      ensuref(find(cbegin(GRIDS), cend(GRIDS), maze[i][j])!=cend(GRIDS), "s[%d][%d] = %c, violating the constraint s[i][j] \\in \"%s\".", i+1, j+1, maze[i][j], GRIDS);
      k += maze[i][j] == 'b';
      inf.readChar(" \n"[j==m-1]);
   }
   ensuref(K_MIN<=k && k<=K_MAX[s], "The number of beads is %d, violating the range [%d, %d].", k, K_MIN, K_MAX[s]);
   for(int i=0; i<=n-1; ++i) for(int j=0; j<=m-1; ++j) if(maze[i][j] == 'b'){
      int i2 = i+1;
      while(i2<=n-1 && maze[i2][j]=='b'){
         maze[i2++][j] = 'w';
      }
      ensuref(i2 <= n-1, "s[%d][%d] = 'b', violating the stability.", n, j+1);
      ensuref(maze[i2][j] == 'w', "s[%d][%d] = 'b' and s[%d][%d] = 's', violating the stability.", i2, j+1, i2+1, j+1);
   }
   inf.readEof();
}
