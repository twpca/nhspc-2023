#include"testlib.h"
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<vector>
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
constexpr bool operator==(Pt a, Pt b) noexcept{
   return a.x==b.x && a.y==b.y;
}
constexpr int operator%(Pt a, Pt b) noexcept{
   return a.x*b.y - a.y*b.x;
}
template<> struct std::hash<Pt>{
   size_t operator()(Pt p) const noexcept{
      u64 x;
      static_assert(sizeof x == sizeof p);
      memcpy(&x, &p, sizeof p);
      return hash<u64>()(x);
   }
};

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
int k_all(Pt *s1, int n, Pt *s2, int m){
   vector<int> x(n+m), y(n+m);
   for(int i=0; i<=n-1; ++i){
      x[i] = s1[i].x;
      y[i] = s1[i].y;
   }
   for(int i=0; i<=m-1; ++i){
      x[n+i] = s2[i].x;
      y[n+i] = s2[i].y;
   }
   auto [p_xmin, p_xmax] = minmax_element(x.cbegin(), x.cend());
   auto [p_ymin, p_ymax] = minmax_element(y.cbegin(), y.cend());
   int x_min = *p_xmin, x_max = *p_xmax;
   int y_min = *p_ymin, y_max = *p_ymax;
   if(x_min==x_max || y_min==y_max){
      return 0;
   }
   for(int i=0; i<=n-1; ++i){
      s1[i] -= {x_min, y_min};
   }
   for(int i=0; i<=m-1; ++i){
      s2[i] -= {x_min, y_min};
   }
   x_max -= x_min; y_max -= y_min;
   vector<u8> in_s1((x_max+1)*(y_max+1));
   for(int i=0; i<=n-1; ++i){
      in_s1[s1[i].x*(y_max+1)+s1[i].y] = true;
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
   sort(seg.begin(), seg.end(), [p=s2](pair<int, int> s, pair<int, int> t){
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
   vector<vector<u64>> ok(m, vector<u64>(vec_len));
   vector<u64> res(vec_len);
   for(int i1=0; i1<=n-1; ++i1) for(int i2=0; i2<=m-1; ++i2){
      Pt v = s2[i2]-s1[i1];
      for(int i=0; i<=m-1; ++i) for(u64 &sij: ok[i]){
         sij = 0;
      }
      bs_set(ok[i2], 2*area_max);
      for(auto [i, j]: seg) if(check_s1(s2[j]-v)){
         int d2a = s2[i]%s2[j];
         bs_or_eq(ok[j], bs_l_shift(ok[i], d2a));
      }
      bs_or_eq(res, ok[i2]);
   }
   int cnt = 0;
   for(int i=1; i<=2*area_max; ++i){
      cnt += bs_test(res, 2*area_max+i);
   }
   return cnt;
}

int k_subtask1(Pt const *s1, int n, Pt const *s2, int m){
   unordered_set<Pt> us_s1;
   for(int i=0; i<=n-1; ++i){
      us_s1.insert(s1[i]);
   }
   set<int> res;
   for(int i=0; i<=n-1; ++i) for(int j=0; j<=m-1; ++j){
      Pt v = s2[j]-s1[i];
      for(int k=0; k<=m-1; ++k) if(us_s1.find(s2[k]-v)!=us_s1.cend()){
         for(int l=k+1; l<=m-1; ++l) if(us_s1.find(s2[l]-v)!=us_s1.cend()){
            res.insert(abs((s2[k]-s2[j])%(s2[l]-s2[j])));
         }
      }
   }
   if(!res.empty() && *res.cbegin()==0){
      res.erase(res.cbegin());
   }
   return (int)res.size();
}

constexpr int N_MIN = 3;
constexpr int N_MAX = 40;
constexpr int X_MIN = 0;
constexpr int X_MAX = 20;
constexpr int NPLUSM = 30;

int main(int argc, char **argv){
   registerValidation(argc, argv);
   int s = subtask(argc, argv);
   int n = inf.readInt(N_MIN, N_MAX, "n");
   inf.readChar(' ');
   int m = inf.readInt(N_MIN, N_MAX, "m");
   inf.readChar('\n');
   if(s == 2){
      ensuref(n+m <= NPLUSM, "(n, m) = (%d, %d), violating the constraint n+m <= %d.", n, m, NPLUSM);
   }
   vector<Pt> s1, s2;
   unordered_map<Pt, int> um1, um2;
   for(int i=1; i<=n; ++i){
      char var[16];
      sprintf(var, "x[%d]", i);
      int xi = inf.readInt(X_MIN, X_MAX, var);
      inf.readChar(' ');
      var[0] = 'y';
      int yi = inf.readInt(X_MIN, X_MAX, var);
      inf.readChar('\n');
      s1.emplace_back(xi, yi);
      auto [jt, ok] = um1.emplace(s1.back(), i);
      ensuref(ok, "(x[%d], y[%d]) = (x[%d], y[%d]) = (%d, %d).", jt->second, jt->second, i, i, xi, yi);
   }
   for(int i=1; i<=m; ++i){
      char var[16];
      sprintf(var, "xi[%d]", i);
      int xi = inf.readInt(X_MIN, X_MAX, var);
      inf.readChar(' ');
      sprintf(var, "eta[%d]", i);
      int yi = inf.readInt(X_MIN, X_MAX, var);
      inf.readChar('\n');
      s2.emplace_back(xi, yi);
      auto [jt, ok] = um2.emplace(s2.back(), i);
      ensuref(ok, "(xi[%d], eta[%d]) = (xi[%d], eta[%d]) = (%d, %d).", jt->second, jt->second, i, i, xi, yi);
   }
   if(s == 1){
      int k1 = k_subtask1(s1.data(), n, s2.data(), m);
      int kall = k_all(s1.data(), n, s2.data(), m);
      ensuref(k1 == kall, "There are good convex hulls with 4 or more corners whose areas can't be achieved with good triangles.");
   }
   if(s == 3){
      unordered_set<Pt> us1, us2;
      for(auto [p, _]: um1){
         us1.insert(p);
      }
      for(auto [q, _]: um2){
         us2.insert(q);
      }
      ensuref(us1 == us2, "S1 != S2.");
   }
   inf.readEof();
}
