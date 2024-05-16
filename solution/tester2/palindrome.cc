#include<cstdio>
using namespace std;

using i64 = long long;
constexpr int MOD = 1'000'000'007;

int main(){
   int T;
   scanf("%d", &T);
   while(T-- > 0){
      i64 n;
      scanf("%lld", &n);
      n /= 2;
      i64 ans = 1, p2 = 2;
      while(n > 0){
         if(n%2 == 1){
            ans = ans*p2%MOD;
         }
         p2 = p2*p2%MOD;
         n /= 2;
      }
      printf("%lld\n", ans);
   }
}
