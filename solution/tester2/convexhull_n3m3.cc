#include<set>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;

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
   auto check = [](Pt p1, Pt p2, Pt q1, Pt q2, Pt r1, Pt r2){
      return p2-p1==q2-q1 && q2-q1==r2-r1;
   };
   set<int> ans;
   for(int i1=0; i1<=n-1; ++i1) for(int j1=i1+1; j1<=n-1; ++j1) for(int k1=j1+1; k1<=n-1; ++k1){
      for(int i2=0; i2<=m-1; ++i2) for(int j2=i2+1; j2<=m-1; ++j2) for(int k2=j2+1; k2<=m-1; ++k2){
         if(check(s1[i1], s2[i2], s1[j1], s2[j2], s1[k1], s2[k2])
            || check(s1[i1], s2[i2], s1[j1], s2[k2], s1[k1], s2[j2])
            || check(s1[i1], s2[j2], s1[j1], s2[i2], s1[k1], s2[k2])
            || check(s1[i1], s2[j2], s1[j1], s2[k2], s1[k1], s2[i2])
            || check(s1[i1], s2[k2], s1[j1], s2[i2], s1[k1], s2[j2])
            || check(s1[i1], s2[k2], s1[j1], s2[j2], s1[k1], s2[i2])){
            ans.insert(abs((s1[j1]-s1[i1])%(s1[k1]-s1[i1])));
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
