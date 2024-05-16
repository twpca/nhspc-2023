#include<algorithm>
#include<numeric>
#include<vector>
#include<cstdio>
using namespace std;

using i64 = long long;

int main(){
   int n, k;
   scanf("%d%d", &n, &k);
   vector<int> c(n);
   for(int i=0; i<=n-1; ++i){
      scanf("%d", c.data()+i);
   }
   vector<int> si(n), ra(n);
   iota(si.begin(), si.end(), 0);
   sort(si.begin(), si.end(), [a=c.data()](int i, int j){
      if(a[i] == a[j]){
         return i < j;
      }
      return a[i] > a[j];
   });
   for(int i=0; i<=n-1; ++i){
      ra[si[i]] = i;
   }
   int cnt = 0;
   i64 ans = 0;
   for(int i=0; i<=n-1; ++i){
      if(ra[i] < k){
         ans += i-cnt;
         ++cnt;
      }
   }
   printf("%lld\n", ans);
}
