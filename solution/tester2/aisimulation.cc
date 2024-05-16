#include<algorithm>
#include<array>
#include<vector>
#include<cstdio>
using namespace std;

using u8 = unsigned char;

constexpr int K = 10;
constexpr array<int, 1<<K> Bitcnt_build(){
   array<int, 1<<K> res{};
   for(int i=1; i<1<<K; ++i){
      res[i] = res[i/2] + i%2;
   }
   return res;
}
array<int, 1<<K> Bitcnt = Bitcnt_build();

int main(){
   int n, k, t;
   scanf("%d%d%d", &n, &k, &t);
   // assert(k <= K);
   vector<int> b(n);
   for(int i=0; i<=n-1; ++i){
      for(int j=0; j<=k-1; ++j){
         char c;
         scanf(" %c", &c);
         b[i] = 2*b[i]+(c=='1');
      }
   }
   vector<u8> vis(1llu<<k);
   for(int bi: b){
      vis[bi] = true;
   }
   for(int q=0; q<1<<k; ++q) if(Bitcnt[q] > 3){
      vis[q] = true;
   }
   auto check = [n, k, t, b=b.data()](int q){
      vector<int> mask_vec(k);
      fill(mask_vec.end()-t, mask_vec.end(), 1);
      do{
         int mask = 0;
         for(int mi: mask_vec){
            mask = 2*mask + mi;
         }
         auto ok = [q, mask](int bi){
            return (bi&mask) == (q&mask);
         };
         if(none_of(b, b+n, ok)){
            return false;
         }
      }while(next_permutation(mask_vec.begin(), mask_vec.end()));
      return true;
   };
   for(int q=0; q<1<<k; ++q) if(!vis[q]){
      if(check(q)){
         for(int i=k-1; i>=0; --i){
            printf("%d", q>>i&1);
         }
         putchar('\n');
         return 0;
      }
   }
   puts("none");
}
