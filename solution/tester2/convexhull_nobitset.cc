#include<algorithm>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

using u8 = unsigned char;
using u64 = unsigned long long;

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
constexpr int operator%(Pt a, Pt b) noexcept{
   return a.x*b.y - a.y*b.x;
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> x0(n+m), y0(n+m);
   for(int i=0; i<=n+m-1; ++i){
      scanf("%d%d", x0.data()+i, y0.data()+i);
   }
   auto [p_xmin, p_xmax] = minmax_element(x0.cbegin(), x0.cend());
   auto [p_ymin, p_ymax] = minmax_element(y0.cbegin(), y0.cend());
   int x_min = *p_xmin, x_max = *p_xmax;
   int y_min = *p_ymin, y_max = *p_ymax;
   if(x_min==x_max || y_min==y_max){
      puts("0");
      return 0;
   }
   vector<Pt> s1(n), s2(m);
   for(int i=0; i<=n-1; ++i){
      s1[i].x = x0[i]-x_min, s1[i].y = y0[i]-y_min;
   }
   for(int i=0; i<=m-1; ++i){
      s2[i].x = x0[n+i]-x_min, s2[i].y = y0[n+i]-y_min;
   }
   x_max -= x_min; y_max -= y_min;
   vector<u8> in_s1((x_max+1)*(y_max+1));
   for(auto [x, y]: s1){
      in_s1[x*(y_max+1)+y] = true;
   }
   auto check_s1 = [x_max, y_max, ok=in_s1.data()](Pt p){
      auto [x, y] = p;
      if(x<0 || x>x_max || y<0 || y>y_max){
         return false;
      }
      return (bool)ok[x*(y_max+1)+y];
   };
   vector<pair<int, int>> seg;
   for(int i=0; i<=m-1; ++i) for(int j=0; j<=m-1; ++j) if(i != j){
      seg.emplace_back(i, j);
   }
   sort(seg.begin(), seg.end(), [p=s2.data()](pair<int, int> s, pair<int, int> t){
      auto [i1, j1] = s; auto [i2, j2] = t;
      auto u = p[j1]-p[i1], v = p[j2]-p[i2];
      if(u.y>0 || u.y==0 && u.x<0){
         if(v.y>0 || v.y==0 && v.x<0){
            return u%v > 0;
         }
         return false;
      }
      if(v.y>0 || v.y==0 && v.x<0){
         return true;
      }
      return u%v > 0;
   });
   int area_max = x_max*y_max;
   vector<u8> ans(4*area_max+1);
   for(int i1=0; i1<=n-1; ++i1) for(int i2=0; i2<=m-1; ++i2){
      vector<vector<u8>> ok(m, vector<u8>(4*area_max+1));
      ok[i2][2*area_max] = true;
      Pt v = s2[i2]-s1[i1];
      for(auto [i, j]: seg) if(check_s1(s2[j]-v)){
         int d2a = s2[i]%s2[j];
         if(d2a > 0){
            for(int k=d2a; k<=4*area_max; ++k){
               ok[j][k] |= ok[i][k-d2a];
            }
         }else{
            d2a = -d2a;
            for(int k=0; k+d2a<=4*area_max; ++k){
               ok[j][k] |= ok[i][k+d2a];
            }
         }
      }
      for(int i=0; i<=4*area_max; ++i){
         ans[i] |= ok[i2][i];
      }
   }
   printf("%td\n", count(ans.cbegin()+2*area_max+1, ans.cend(), 1));
   for(int i=1; i<=2*area_max; ++i) if(ans[2*area_max+i]){
      printf("%d\n", i);
   }
}
