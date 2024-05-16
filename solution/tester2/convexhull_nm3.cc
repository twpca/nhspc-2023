#include<set>
#include<unordered_set>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

using i64 = long long;

struct Pt{
   Pt() = default;
   constexpr Pt(int a, int b) noexcept: x(a), y(b){}
   constexpr Pt &operator-=(Pt rhs) noexcept{
      x -= rhs.x; y -= rhs.y;
      return *this;
   }
   int x, y;
};
constexpr Pt operator-(Pt a, Pt b) noexcept{
   return a -= b;
}
constexpr bool operator==(Pt a, Pt b) noexcept{
   return a.x==b.x && a.y==b.y;
}
constexpr int operator%(Pt a, Pt b) noexcept{
   return a.x*b.y - a.y*b.x;
}
template<> struct std::hash<Pt>{
   size_t operator()(Pt p) const noexcept{
      i64 x;
      static_assert(sizeof x == sizeof p);
      memcpy(&x, &p, sizeof p);
      return hash<i64>()(x);
   }
};

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<Pt> s1, s2;
   for(int i=0; i<=n-1; ++i){
      int x, y;
      scanf("%d%d", &x, &y);
      s1.emplace_back(x, y);
   }
   for(int i=0; i<=m-1; ++i){
      int x, y;
      scanf("%d%d", &x, &y);
      s2.emplace_back(x, y);
   }
   unordered_set<Pt> us_s1;
   for(Pt p: s1){
      us_s1.insert(p);
   }
   set<int> ans;
   for(int i=0; i<=n-1; ++i) for(int j=0; j<=m-1; ++j){
      Pt v = s2[j]-s1[i];
      for(int k=0; k<=m-1; ++k) if(us_s1.find(s2[k]-v)!=us_s1.cend()){
         for(int l=k+1; l<=m-1; ++l) if(us_s1.find(s2[l]-v)!=us_s1.cend()){
            ans.insert(abs((s2[k]-s2[j])%(s2[l]-s2[j])));
         }
      }
   }
   if(!ans.empty() && *ans.cbegin()==0){
      ans.erase(ans.cbegin());
   }
   printf("%zu\n", ans.size());
   for(int a: ans){
      printf("%d\n", a);
   }
}
