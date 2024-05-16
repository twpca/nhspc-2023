#include<algorithm>
#include<random>
#include<unordered_set>
#include<utility>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

using i64 = long long;

struct Pt{
   Pt() = default;
   constexpr Pt(int a, int b) noexcept: x(a), y(b){}
   int x, y;
};
constexpr bool operator==(Pt a, Pt b) noexcept{
   return a.x==b.x && a.y==b.y;
}
template<> struct std::hash<Pt>{
   size_t operator()(Pt p) const noexcept{
      i64 x;
      static_assert(sizeof x == sizeof p);
      memcpy(&x, &p, sizeof p);
      return hash<i64>()(x);
   }
};

struct Gen{
   Gen() = default;
   constexpr void next() noexcept{
      ++subtask, file = 0;
   }
   void gen(pair<vector<Pt>, vector<Pt>> const &s){
      char fn[32];
      sprintf(fn, "%d_%02d.in", subtask, ++file);
      FILE *fout = fopen(fn, "wb");
      auto &[s1, s2] = s;
      fprintf(fout, "%zu %zu\n", s1.size(), s2.size());
      for(auto [x, y]: s1){
         fprintf(fout, "%d %d\n", x, y);
      }
      for(auto [xi, eta]: s2){
         fprintf(fout, "%d %d\n", xi, eta);
      }
      fclose(fout);
   }
   int subtask = 0, file = 0;
};

mt19937_64 Rng;
using Unif = uniform_int_distribution<>;
int rand_intvl(int l, int r){
   return Unif(l, r)(Rng);
}
pair<int, int> rand_pair(int l, int r){
   int x1 = rand_intvl(l, r), x2 = rand_intvl(l, r-1);
   if(x1 == x2){
      ++x2;
   }
   return {x1, x2};
}

constexpr int N = 40;
constexpr int X_MAX = 20;

pair<vector<Pt>, vector<Pt>> rand_subtask1(int n, int m){
   static_assert(X_MAX > 4);
   auto [x1, x2] = rand_pair(0, X_MAX);
   vector<Pt> s1; s1.reserve(2*X_MAX+2);
   for(int i=0; i<=X_MAX; ++i){
      s1.emplace_back(x1, i);
      s1.emplace_back(x2, i);
   }
   shuffle(s1.begin(), s1.end(), Rng);
   // assert(n <= s1.size());
   s1.resize(n);
   vector<Pt> s2; s2.reserve(m);
   int d = abs(x2-x1), x0 = rand_intvl(0, 2*d-1);
   vector<bool> vis(X_MAX+1);
   unordered_set<Pt> us2;
   while(m > 0){
      int x = rand_intvl(0, X_MAX), y = rand_intvl(0, X_MAX);
      if((x+x0)%(2*d)<d && vis[x]){
         continue;
      }
      auto [_, ok] = us2.emplace(x, y);
      if(!ok){
         continue;
      }
      s2.emplace_back(x, y);
      vis[x] = true; --m;
   }
   if(rand_intvl(0, 1)){
      for(auto &[xi, yi]: s1){
         swap(xi, yi);
      }
      for(auto &[xi, yi]: s2){
         swap(xi, yi);
      }
   }
   if(rand_intvl(0, 1)){
      swap(s1, s2);
   }
   return {s1, s2};
}

vector<Pt> rand_set(int n, int x_max=X_MAX){
   unordered_set<Pt> us;
   while(n-- > 0){
      int x, y;
      do{
         x = rand_intvl(0, x_max);
         y = rand_intvl(0, x_max);
      }while(!us.emplace(x, y).second);
   }
   return {us.cbegin(), us.cend()};
}
pair<vector<Pt>, vector<Pt>> rand_case(int n, int m, int s){
   Rng.seed(s);
   auto s1 = rand_set(n), s2 = rand_set(m);
   return {s1, s2};
}
vector<Pt> convex_15gon(int s){
   Rng.seed(s);
   vector<Pt> res{
      {0, 10}, {1, 6}, {2, 3}, {3, 2}, {5, 1},
      {9, 0}, {10, 0}, {15, 3}, {19, 6}, {20, 10},
      {20, 11}, {19, 14}, {18, 16}, {17, 17}, {14, 19}
   };
   shuffle(res.begin(), res.end(), Rng);
   return res;
}
pair<vector<Pt>, vector<Pt>> rand_case3(int n, int s){
   Rng.seed(s);
   auto s1 = rand_set(n), s2 = s1;
   shuffle(s2.begin(), s2.end(), Rng);
   return {s1, s2};
}

int main(){
   Gen g;
   g.next();
   g.gen({{{0, 2}, {1, 1}, {1, 3}, {2, 3}, {3, 2}, {4, 2}}, {{2, 0}, {2, 1}, {2, 2}, {3, 1}, {5, 1}}});
   g.gen({{{0, 0}, {1, 1}, {1, 2}, {2, 0}}, {{2, 0}, {1, 2}, {1, 1}, {0, 0}}});
   g.gen({{{0, 1}, {1, 1}, {1, 2}, {2, 2}}, {{0, 1}, {1, 0}, {1, 1}, {2, 0}}});
   g.gen({{{0, 0}, {0, 1}, {0, 2}}, {{0, 18}, {0, 19}, {0, 20}}});
   g.gen({{{9, 10}, {10, 10}, {11, 10}}, {{5, 10}, {10, 10}, {15, 10}}});
   for(int i=8; i-->0; ){
      Rng.seed(i);
      int n = N-rand_intvl(0, i), m = N-rand_intvl(0, i);
      g.gen(rand_subtask1(n, m));
   }
   g.next();
   g.gen({{{0, 2}, {1, 1}, {1, 3}, {2, 3}, {3, 2}, {4, 2}}, {{2, 0}, {2, 1}, {2, 2}, {3, 1}, {5, 1}}});
   g.gen({{{0, 0}, {1, 1}, {1, 2}, {2, 0}}, {{2, 0}, {1, 2}, {1, 1}, {0, 0}}});
   g.gen({{{0, 1}, {1, 1}, {1, 2}, {2, 2}}, {{0, 1}, {1, 0}, {1, 1}, {2, 0}}});
   g.gen({{{0, 0}, {0, 20}, {20, 0}, {20, 20}}, {{0, 20}, {20, 0}, {0, 0}, {20, 20}}});
   g.gen(rand_case(5, 25, 33));
   g.gen(rand_case(25, 5, 4));
   for(int i=5; i-->0; ){
      g.gen(rand_case(15, 15, 58^i));
   }
   g.gen({convex_15gon(114), convex_15gon(514)});
   g.next();
   g.gen({{{0, 0}, {1, 1}, {1, 2}, {2, 0}}, {{2, 0}, {1, 2}, {1, 1}, {0, 0}}});
   g.gen({{{0, 0}, {0, 20}, {20, 0}, {20, 20}}, {{0, 20}, {20, 0}, {0, 0}, {20, 20}}});
   for(int i=10; i-->0; ){
      g.gen(rand_case3(N, 9527-i));
   }
   g.next();
   for(int i=5; i-->0; ){
      Rng.seed(40010+i);
      auto s1 = rand_set(N, X_MAX-5), s2 = s1;
      shuffle(s2.begin(), s2.end(), Rng);
      int dx = rand_intvl(1, 5), dy = rand_intvl(1, 5);
      for(auto &[x, y]: s2){
         x += dx; y += dy;
      }
      if(rand_intvl(0, 1)){
         swap(s1, s2);
      }
      g.gen({s1, s2});
   }
   for(int i=5; i-->0; ){
      Rng.seed(114514*i);
      auto s1 = rand_set(N), s2 = rand_set(N);
      g.gen({s1, s2});
   }
}
