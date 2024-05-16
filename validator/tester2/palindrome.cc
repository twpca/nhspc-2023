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

using i64 = long long;
constexpr int T = 10'000;
constexpr i64 N[] = {1'000'000'000'000'000, 30, 1'000, 1'000'000, 1'000'000'000'000'000};

int main(int argc, char **argv){
   registerValidation(argc, argv);
   int s = subtask(argc, argv);
   int t = inf.readInt(1, T, "t");
   inf.readChar('\n');
   char var[16];
   if(s == 1){
      unordered_map<int, int> um;
      for(int i=1; i<=t; ++i){
         sprintf(var, "n[%d]", i);
         int ni = inf.readLong(1, N[s], var);
         auto [jt, ok] = um.emplace(ni, i);
         ensuref(ok, "n[%d] = n[%d] = %d.", jt->second, i, ni);
         inf.readChar('\n');
      }
   }else{
      for(int i=1; i<=t; ++i){
         sprintf(var, "n[%d]", i);
         inf.readLong(1, N[s], var);
         inf.readChar('\n');
      }
   }
   inf.readEof();
}
