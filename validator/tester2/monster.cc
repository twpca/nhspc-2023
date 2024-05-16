#include"testlib.h"
#include<unordered_map>
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

constexpr int F_MIN = 1;
constexpr int F_MAX[] = {200'000, 1, 200'000, 200'000, 200'000, 200'000};
constexpr int M_MIN = 1;
constexpr int M_MAX = 200'000;
constexpr int N_MIN = 1;
constexpr int N_MAX = 200'000;
constexpr int FMN_MAX[] = {200'000, 100, 200'000, 3'000, 200'000, 200'000};
constexpr int R_MIN = 1;
constexpr int Q_MIN = 1;
constexpr int Q_MAX[] = {200'000, 100, 200'000, 200'000, 1, 200'000};

using i64 = long long;

int main(int argc, char **argv){
   registerValidation(argc, argv);
   int s = subtask(argc, argv);
   int f = inf.readInt(F_MIN, F_MAX[s], "F");
   inf.readChar(' ');
   int m = inf.readInt(M_MIN, M_MAX, "M");
   inf.readChar(' ');
   int n = inf.readInt(N_MIN, N_MAX, "N");
   inf.readChar('\n');
   ensuref((i64)f*m*n <= FMN_MAX[s], "FMN = %lld, violating the constraint FMN <= %d.", (i64)f*m*n, FMN_MAX[s]);
   int fmn = f*m*n;
   int r = inf.readInt(R_MIN, fmn, "R");
   inf.readChar('\n');
   unordered_map<int, int> pqr;
   for(int i=1; i<=r; ++i){
      char var[16];
      sprintf(var, "p[%d]", i);
      int pi = inf.readInt(1, f, var);
      inf.readChar(' ');
      var[0] = 'q';
      int qi = inf.readInt(1, m, var);
      inf.readChar(' ');
      var[0] = 'r';
      int ri = inf.readInt(1, n, var);
      inf.readChar('\n');
      auto [jt, ok] = pqr.emplace((pi*m+qi)*n+ri, i);
      int j = jt->second;
      ensuref(ok, "(p[%d], q[%d], r[%d]) = (p[%d], q[%d], r[%d]) = (%d, %d, %d), violating the constraint (p[i], q[i], r[i]) != (p[j], q[j], r[j]) if i != j.", i, i, i, j, j, j, pi, qi, ri);
   }
   int q = inf.readInt(Q_MIN, Q_MAX[s], "Q");
   inf.readChar('\n');
   for(int i=1; i<=q; ++i){
      char var[16];
      sprintf(var, "a[%d]", i);
      int ai = inf.readInt(1, f, var);
      inf.readChar(' ');
      var[0] = 'b';
      int bi = inf.readInt(1, m, var);
      inf.readChar(' ');
      var[0] = 'c';
      int ci = inf.readInt(1, n, var);
      inf.readChar(' ');
      var[0] = 'x';
      int xi = inf.readInt(1, f, var);
      inf.readChar(' ');
      var[0] = 'y';
      int yi = inf.readInt(1, m, var);
      inf.readChar(' ');
      var[0] = 'z';
      int zi = inf.readInt(1, n, var);
      inf.readChar('\n');
      if(s == 2){
         ensuref(ai==xi && bi==yi && ci==zi, "In subtask 2, (a[%d], b[%d], c[%d]) = (%d, %d, %d), (x[%d], y[%d], z[%d]) = (%d, %d, %d), violating the constraint (a[i], b[i], c[i]) = (x[i], y[i], z[i]) for i in {1, 2, ..., Q}.", i, i, i, ai, bi, ci, i, i, i, xi, yi, zi);
      }
   }
   inf.readEof();
}
