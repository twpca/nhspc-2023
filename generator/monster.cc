#include<algorithm>
#include<array>
#include<numeric>
#include<random>
#include<utility>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;

using Pt3 = array<int, 3>;

struct Gen{
   Gen() = default;
   constexpr void next() noexcept{
      ++subtask, file = 0;
   }
   void gen(Pt3 fmn, vector<Pt3> const &pqr, vector<pair<Pt3, Pt3>> const &st){
      char fn[32];
      sprintf(fn, "%d_%02d.in", subtask, ++file);
      FILE *fout = fopen(fn, "wb");
      auto [f, m, n] = fmn;
      fprintf(fout, "%d %d %d\n%zu\n", f, m, n, pqr.size());
      for(auto [p, q, r]: pqr){
         fprintf(fout, "%d %d %d\n", p, q, r);
      }
      fprintf(fout, "%zu\n", st.size());
      for(auto [s, t]: st){
         auto [a, b, c] = s;
         auto [x, y, z] = t;
         fprintf(fout, "%d %d %d %d %d %d\n", a, b, c, x, y, z);
      }
      fclose(fout);
   }
private:
   int subtask = 0, file = 0;
};

mt19937_64 Rng;
using Unif = uniform_int_distribution<>;
int rand_intvl(int l, int r){
   return Unif(l, r)(Rng);
}
Pt3 rand_pt3(Pt3 fmn){
   Pt3 res;
   for(int i=0; i<=2; ++i){
      res[i] = rand_intvl(1, fmn[i]);
   }
   return res;
}
vector<Pt3> rand_pqr(Pt3 fmn, int size){
   vector<int> id(fmn[0]*fmn[1]*fmn[2]);
   iota(id.begin(), id.end(), 0);
   for(int i=0; i<=size-1; ++i){
      swap(id[i], id[rand_intvl(i, (int)id.size()-1)]);
   }
   vector<Pt3> res(size);
   for(int i=0; i<=size-1; ++i){
      res[i][2] = id[i]%fmn[2]+1;
      res[i][1] = id[i]/fmn[2]%fmn[1]+1;
      res[i][0] = id[i]/fmn[2]/fmn[1]+1;
   }
   return res;
}
vector<pair<Pt3, Pt3>> rand_st(Pt3 fmn, int size){
   vector<pair<Pt3, Pt3>> res(size);
   for(auto &[s, t]: res){
      s = rand_pt3(fmn);
      t = rand_pt3(fmn);
   }
   return res;
}

constexpr int FMN[] = {0, 100, 200'000, 3'000, 200'000, 200'000};
constexpr int Q[] = {0, 100, 200'000, 200'000, 1, 200'000};

int main(){
   Gen g;
   g.next();
   g.gen({1, 1, 3}, {{1, 1, 2}}, {{{1, 1, 1}, {1, 1, 3}}});
   g.gen({1, 1, 1}, {{1, 1, 1}}, {{{1, 1, 1}, {1, 1, 1}}});
   for(int i=10; i-->0; ){
      Rng.seed(i);
      int m = rand_intvl(1, i+1), n = (FMN[1]-i)/m;
      if(rand_intvl(0, 1)){
         swap(m, n);
      }
      Pt3 fmn = {1, m, n}, rest = rand_pt3(fmn);
      g.gen(fmn, {rest}, rand_st(fmn, Q[1]-rand_intvl(0, i*Q[1]/10)));
   }
   g.next();
   for(int i=10; i-->0; ){
      Rng.seed(87-i);
      int f = 50+rand_intvl(0, 2*i);
      int m = 50+rand_intvl(0, 2*i);
      int n = (FMN[2]-10*i)/f/m;
      Pt3 fmn = {f, m, n};
      shuffle(fmn.begin(), fmn.end(), Rng);
      auto pqr = rand_pqr(fmn, f*m*n-f*m*n*i/10);
      vector<pair<Pt3, Pt3>> mv(Q[2]-rand_intvl(0, i*Q[2]/10));
      for(auto &[s, t]: mv){
         s = t = rand_pt3(fmn);
      }
      g.gen(fmn, pqr, move(mv));
   }
   g.next();
   g.gen({3, 3, 3}, {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}}, {{{1, 3, 3}, {3, 1, 1}}, {{1, 2, 2}, {3, 2, 2}}, {{1, 2, 3}, {1, 2, 3}}, {{1, 1, 1}, {3, 3, 3}}});
   for(int i=10; i-->0; ){
      Rng.seed(58^i);
      int f = 10+rand_intvl(0, i);
      int m = 20+rand_intvl(0, i);
      int n = (FMN[3]-10*i)/f/m;
      Pt3 fmn = {f, m, n};
      shuffle(fmn.begin(), fmn.end(), Rng);
      auto pqr = rand_pqr(fmn, f*m*n-f*m*n*i/10);
      g.gen(fmn, pqr, rand_st(fmn, Q[3]-rand_intvl(0, i*Q[3]/10)));
   }
   g.next();
   g.gen({1, 1, 3}, {{1, 1, 2}}, {{{1, 1, 1}, {1, 1, 3}}});
   g.gen({1, 1, 1}, {{1, 1, 1}}, {{{1, 1, 1}, {1, 1, 1}}});
   for(int i=10; i-->0; ){
      Rng.seed(4649+i);
      int f = 50+rand_intvl(0, 2*i);
      int m = 50+rand_intvl(0, 2*i);
      int n = (FMN[4]-10*i)/f/m;
      Pt3 fmn = {f, m, n};
      shuffle(fmn.begin(), fmn.end(), Rng);
      auto pqr = rand_pqr(fmn, f*m*n-f*m*n*i/10);
      g.gen(fmn, pqr, rand_st(fmn, 1));
   }
   g.gen({50, 50, 80}, {{11, 45, 14}}, {{{9, 5, 27}, {9, 5, 27}}});
   g.next();
   for(int i=10; i-->0; ){
      Rng.seed(114514*i);
      int f = 50+rand_intvl(0, 2*i);
      int m = 50+rand_intvl(0, 2*i);
      int n = (FMN[5]-10*i)/f/m;
      Pt3 fmn = {f, m, n};
      shuffle(fmn.begin(), fmn.end(), Rng);
      auto pqr = rand_pqr(fmn, f*m*n-f*m*n*i/10);
      g.gen(fmn, pqr, rand_st(fmn, Q[5]-rand_intvl(0, i*Q[5]/10)));
   }
}
