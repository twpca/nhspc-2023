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

vector<u64> &bs_set(vector<u64> &self, int pos){
   self[pos>>6] |= 1ull<<(pos&63);
   return self;
}
vector<u64> bs_l_shift(vector<u64> const &bs, int n){
   if(n == 0){
      return bs;
   }
   if(n > 0){
      int q = n>>6, r = n&63;
      vector<u64> res(bs.size());
      if(q >= bs.size()){
         return res;
      }
      copy(bs.cbegin(), bs.cend()-q, res.begin()+q);
      if(r == 0){
         return res;
      }
      u64 mask = (1ull<<(64-r))-1;
      res.back() &= mask;
      for(int i=(int)res.size(); i-->q; ){
         u64 carry = 0;
         if(i-1 >= q){
            carry = res[i-1]>>(64-r);
            res[i-1] &= mask;
         }
         res[i] = res[i]<<r | carry;
      }
      return res;
   }
   // assert(n != INT_MIN);
   n = -n;
   int q = n>>6, r = n&63;
   vector<u64> res(bs.size());
   if(q >= bs.size()){
      return res;
   }
   copy(bs.cbegin()+q, bs.cend(), res.begin());
   if(r == 0){
      return res;
   }
   u64 mask = (1ull<<r)-1;
   for(int i=0; i<=(int)res.size()-q-1; ++i){
      u64 carry = 0;
      if(i+1 <= (int)res.size()-q-1){
         carry = res[i+1] & mask;
      }
      res[i] = res[i]>>r | carry<<(64-r);
   }
   return res;
}
vector<u64> &bs_or_eq(vector<u64> &self, vector<u64> const &rhs){
   // assert(self.size() == rhs.size());
   for(size_t i=0; i<self.size(); ++i){
      self[i] |= rhs[i];
   }
   return self;
}
bool bs_test(vector<u64> const &self, int pos){
   return self[pos>>6]>>(pos&63)&1;
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
   int area_max = x_max*y_max, vec_len = area_max/16+1;
   vector<u64> ans(vec_len);
   for(int i1=0; i1<=n-1; ++i1) for(int i2=0; i2<=m-1; ++i2){
      vector<vector<u64>> ok(m, vector<u64>(vec_len));
      bs_set(ok[i2], 2*area_max);
      Pt v = s2[i2]-s1[i1];
      for(auto [i, j]: seg) if(check_s1(s2[j]-v)){
         int d2a = s2[i]%s2[j];
         bs_or_eq(ok[j], bs_l_shift(ok[i], d2a));
      }
      bs_or_eq(ans, ok[i2]);
   }
   vector<int> a;
   for(int i=1; i<=2*area_max; ++i) if(bs_test(ans, 2*area_max+i)){
      a.push_back(i);
   }
   printf("%zu\n", a.size());
   for(int ai: a){
      printf("%d\n", ai);
   }
}
