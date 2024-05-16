#include<algorithm>
#include<array>
#include<numeric>
#include<random>
#include<tuple>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

using u8 = unsigned char;

struct Gen{
   Gen() = default;
   constexpr void next() noexcept{
      ++subtask, file = 0;
   }
   void gen(tuple<int, int, int, int, vector<pair<int, int>>, vector<pair<int, int>>> const &input){
      char fn[32];
      sprintf(fn, "%d_%02d.in", subtask, ++file);
      FILE *fout = fopen(fn, "wb");
      auto [n, m1, m2, k, uv1, uv2] = input;
      fprintf(fout, "%d %d %d %d\n", n, m1, m2, k);
      for(auto [u, v]: uv1){
         fprintf(fout, "%d %d\n", u, v);
      }
      for(auto [u, v]: uv2){
         fprintf(fout, "%d %d\n", u, v);
      }
      fclose(fout);
   }
   int subtask = 0, file = 0;
};

mt19937_64 Rng;
using Unif = uniform_int_distribution<>;
uniform_real_distribution<> U01{};
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

vector<pair<int, int>> star(int n){
   vector<pair<int, int>> res;
   res.reserve(n);
   for(int u=1; u<=n; ++u){
      res.emplace_back(u, n+1);
   }
   return res;
}

vector<pair<int, int>> randomize(int n, vector<pair<int, int>> const &input){
   auto res = input;
   vector<int> id(input.size()+2);
   iota(id.begin(), id.end(), 0);
   shuffle(id.begin()+n+1, id.end(), Rng);
   shuffle(res.begin(), res.end(), Rng);
   for(auto &[u, v]: res){
      u = id[u]; v = id[v];
      if(rand_intvl(0, 1)){
         swap(u, v);
      }
   }
   return res;
}

vector<pair<int, int>> rand_full_bt(int n){
   vector<int> ha(n);
   iota(ha.begin(), ha.end(), 1);
   int n_vertices = n;
   vector<pair<int, int>> res;
   for(int cnt=n-1; cnt-->0; ){
      auto [i, j] = rand_pair(0, (int)ha.size()-1);
      int u = ha[i], v = ha[j];
      ha.erase(remove_if(ha.begin(), ha.end(), [u, v](int w){return w==u || w==v;}), ha.end());
      ha.push_back(++n_vertices);
      res.emplace_back(u, n_vertices);
      res.emplace_back(v, n_vertices);
   }
   return res;
}

vector<pair<int, int>> rand_full(int n){
   // assert(n >= 3);
   array<double, 3> r;
   for(int i=0; i<=2; ++i){
      r[i] = U01(Rng);
   }
   sort(r.begin(), r.end());
   // assert(r[2] > 0);
   double s = accumulate(r.cbegin(), r.cend(), 0.);
   for(int i=0; i<=2; ++i){
      r[i] /= s;
   }
   array<int, 3> tn;
   for(int i=0; i<=2; ++i){
      tn[i] = (int)(r[i]*(n-3))+1;
   }
   tn[2] = n-tn[0]-tn[1];
   shuffle(tn.begin(), tn.end(), Rng);
   array<vector<pair<int, int>>, 3> t;
   int stn = 0;
   for(int i=0; i<=2; ++i){
      t[i] = rand_full_bt(tn[i]);
      for(auto &[u, v]: t[i]){
         u += u<=tn[i]? stn: n+stn-tn[i]-i;
         v += v<=tn[i]? stn: n+stn-tn[i]-i;
      }
      stn += tn[i];
   }
   vector<pair<int, int>> res;
   for(int i=0; i<=2; ++i){
      res.insert(res.end(), t[i].cbegin(), t[i].cend());
   }
   array<int, 3> rt;
   int st = 0;
   for(int i=0; i<=2; ++i){
      st += tn[i]-1;
      if(tn[i] == 1){
         rt[i] = st+i+1;
      }else{
         rt[i] = n+st;
      }
   }
   for(int i=0; i<=2; ++i){
      res.emplace_back(2*n-2, rt[i]);
   }
   return randomize(n, res);
}

constexpr int V = 300;
constexpr int N_MIN = V/2+1;
constexpr int V3 = 10;
constexpr int N3_MIN = V3/2+1;

int main(){
   Gen g;
   g.next();
   g.gen({4, 2, 2, 0, {{1, 5}, {2, 5}, {3, 6}, {4, 6}, {5, 6}}, {{1, 6}, {2, 6}, {3, 5}, {4, 5}, {5, 6}}});
   g.gen({4, 2, 2, 0, {{1, 5}, {2, 5}, {3, 6}, {4, 6}, {5, 6}}, {{1, 5}, {2, 6}, {3, 5}, {4, 6}, {5, 6}}});
   g.gen({2, 0, 0, 0, {{1, 2}}, {{1, 2}}});
   g.gen({3, 1, 1, 0, {{1, 4}, {4, 3}, {2, 4}}, {{4, 3}, {4, 2}, {4, 1}}});
   auto starvm1 = star(V-1);
   Rng.seed(0);
   auto t1 = randomize(V-1, starvm1), t2 = randomize(V-1, starvm1);
   g.gen({V-1, 1, 1, 0, t1, t2});
   Rng.seed(58);
   t1 = rand_full(N_MIN), t2 = randomize(N_MIN, t1);
   g.gen({N_MIN, N_MIN-2, N_MIN-2, 0, t1, t2});
   g.next();
   g.gen({5, 3, 3, 1, {{1, 7}, {2, 8}, {3, 6}, {4, 6}, {5, 8}, {6, 7}, {7, 8}}, {{1, 6}, {2, 8}, {3, 6}, {4, 7}, {5, 8}, {6, 7}, {7, 8}}});
   g.gen({6, 3, 3, 1, {{1, 7}, {2, 7}, {3, 7}, {4, 8}, {5, 9}, {6, 9}, {7, 8}, {8, 9}}, {{1, 7}, {2, 7}, {3, 9}, {4, 9}, {5, 8}, {6, 8}, {7, 8}, {8, 9}}});
   t1 = star(V-2);
   t2.clear();
   for(int u=2; u<=V-3; ++u){
      t2.emplace_back(u, V-1);
   }
   for(int u: {1, V-2, V-1}){
      t2.emplace_back(u, V);
   }
   g.gen({V-2, 1, 2, 1, t1, t2});
   t1.clear();
   for(int u=1; u<=V-4; ++u){
      t1.emplace_back(u, V-1);
   }
   for(int u=V-3; u<=V-1; ++u){
      t1.emplace_back(u, V);
   }
   g.gen({V-2, 2, 2, 1, t1, t2});
   g.next();
   g.gen({5, 3, 3, 2, {{1, 7}, {2, 8}, {3, 6}, {4, 6}, {5, 8}, {6, 7}, {7, 8}}, {{1, 6}, {2, 8}, {3, 6}, {4, 7}, {5, 8}, {6, 7}, {7, 8}}});
   g.gen({6, 3, 3, 2, {{1, 7}, {2, 7}, {3, 7}, {4, 8}, {5, 9}, {6, 9}, {7, 8}, {8, 9}}, {{1, 7}, {2, 7}, {3, 9}, {4, 9}, {5, 8}, {6, 8}, {7, 8}, {8, 9}}});
   g.gen({6, 1, 4, 2, {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}}, {{1, 7}, {2, 7}, {3, 8}, {4, 8}, {5, 9}, {6, 9}, {7, 10}, {8, 10}, {9, 10}}});
   g.gen({6, 3, 3, 2, {{1, 7}, {2, 7}, {3, 9}, {4, 9}, {5, 8}, {6, 8}, {7, 8}, {8, 9}}, {{1, 7}, {2, 7}, {3, 7}, {4, 8}, {5, 9}, {6, 9}, {7, 8}, {8, 9}}});
   t1 = star(V3-2);
   t2.clear();
   for(int u=2; u<=V3-4; ++u){
      t2.emplace_back(u, V3-1);
   }
   for(int u: {1, V3-3, V3-2, V3-1}){
      t2.emplace_back(u, V3);
   }
   g.gen({V3-2, 1, 2, 2, t1, t2});
   for(int i=5; i-->0; ){
      Rng.seed(114^i);
      t1 = rand_full(N3_MIN);
      t2 = randomize(N3_MIN, t1);
      auto [s, t] = rand_pair(1, N3_MIN);
      for(auto &[u, v]: t2){
         if(u == s){
            u = t;
         }else if(u == t){
            u = s;
         }
         if(v == s){
            v = t;
         }else if(v == t){
            v = s;
         }
      }
      g.gen({N3_MIN, N3_MIN-2, N3_MIN-2, 2, t1, t2});
   }
   g.next();
   t1 = star(V-2);
   t2.clear();
   for(int u=2; u<=V-4; ++u){
      t2.emplace_back(u, V-1);
   }
   for(int u: {1, V-3, V-2, V-1}){
      t2.emplace_back(u, V);
   }
   g.gen({V-2, 1, 2, 2, t1, t2});
   for(int i=5; i-->0; ){
      Rng.seed(514^i);
      t1 = rand_full(N_MIN);
      t2 = randomize(N_MIN, t1);
      auto [s, t] = rand_pair(1, N_MIN);
      for(auto &[u, v]: t2){
         if(u == s){
            u = t;
         }else if(u == t){
            u = s;
         }
         if(v == s){
            v = t;
         }else if(v == t){
            v = s;
         }
      }
      g.gen({N_MIN, N_MIN-2, N_MIN-2, 2, t1, t2});
   }
}
