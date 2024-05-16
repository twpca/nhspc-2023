#include<algorithm>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

struct Evt{
   int x, type, id;
   Evt() = default;
   constexpr Evt(int a, int t, int i) noexcept: x(a), type(t), id(i){}
};
bool operator<(Evt const &e, Evt const &f) noexcept{
   return make_pair(e.x, e.type) < make_pair(f.x, f.type);
}

struct Node{
   int val = 0, tag = 0;
   Node() = default;
   constexpr Node(int v, int t) noexcept: val(v), tag(t){}
};
void st_add_seg(Node *self, int l, int r, int x, int i, int m_l, int m_r){
   if(r<m_l || m_r<l){
      return;
   }
   if(l<=m_l && m_r<=r){
      self[i].val += x; self[i].tag += x;
      return;
   }
   self[2*i].val += self[i].tag;
   self[2*i].tag += self[i].tag;
   self[2*i+1].val += self[i].tag;
   self[2*i+1].tag += self[i].tag;
   self[i].tag = 0;
   int m_m = m_l+(m_r-m_l)/2;
   st_add_seg(self, l, r, x, 2*i, m_l, m_m);
   st_add_seg(self, l, r, x, 2*i+1, m_m+1, m_r);
   self[i].val = max(self[2*i].val, self[2*i+1].val);
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> a(n), b(n);
   for(int i=0; i<=n-1; ++i){
      scanf("%d", a.data()+i);
   }
   for(int i=0; i<=n-1; ++i){
      scanf("%d", b.data()+i);
   }
   vector<int> risan;
   for(int i=0; i<=n-1; ++i) if(a[i] != m-1){
      if(a[i] >= b[i]-1){
         risan.push_back(a[i]-b[i]+1);
         risan.push_back(m-b[i]);
      }else{
         risan.push_back(0);
         risan.push_back(m-b[i]);
         risan.push_back(a[i]+m+1-b[i]);
         risan.push_back(m);
      }
   }
   if(risan.empty()){
      puts("0");
      return 0;
   }
   sort(risan.begin(), risan.end());
   risan.erase(unique(risan.begin(), risan.end()), risan.end());
   vector<Evt> evt;
   vector<int> left, right, dual;
   vector<Node> st(4*risan.size()-4);
   auto add_seg = [&risan, &evt, &left, &right, &dual, &st](int xl, int xr){
      int l = (int)(lower_bound(risan.cbegin(), risan.cend(), xl)-risan.cbegin());
      int r = (int)(lower_bound(risan.cbegin(), risan.cend(), xr)-risan.cbegin());
      evt.emplace_back(l, 1, (int)left.size());
      evt.emplace_back(r, -1, (int)left.size());
      left.push_back(l);
      right.push_back(r-1);
      dual.push_back(-1);
      st_add_seg(st.data(), l, r-1, 1, 1, 0, (int)risan.size()-2);
   };
   for(int i=0; i<=n-1; ++i) if(a[i] != m-1){
      if(a[i] >= b[i]-1){
         add_seg(max(a[i]-b[i]+1, 0), m-b[i]);
      }else{
         add_seg(0, m-b[i]);
         add_seg(a[i]+m+1-b[i], m);
         int ds = (int)dual.size();
         dual[ds-2] = ds-1;
         dual[ds-1] = ds-2;
      }
   }
   sort(evt.begin(), evt.end());
   int ans = st[1].val, curmax = 0;
   for(auto [x, type, id]: evt){
      curmax += type;
      if(type == 1){
         st_add_seg(st.data(), x, right[id], -1, 1, 0, (int)risan.size()-2);
         if(int id2=dual[id]; id2!=-1){
            st_add_seg(st.data(), left[id2], right[id2], -1, 1, 0, (int)risan.size()-2);
         }
         ans = max(ans, st[1].val+curmax);
      }else{
         st_add_seg(st.data(), x, right[id], 1, 1, 0, (int)risan.size()-2);
         if(int id2=dual[id]; id2!=-1){
            st_add_seg(st.data(), left[id2], right[id2], 1, 1, 0, (int)risan.size()-2);
         }
      }
   }
   printf("%d\n", ans);
}
