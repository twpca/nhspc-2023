---
layout: default
---

# 2023 全國資訊學科能力競賽 解說（NHSPC2023 Editorial）

---

# A. Agreement

----

## Subtask 1 : $k=0$

----

$k=0$ 也就是要檢查兩棵樹是否相似，這裡有兩種做法，分別是
- Tree Hash 等樹同構判斷演算法
- 直接構造一對一函數

兩種做法都可以達到線性的時間複雜度。當然也可以嘗試用最糟 $\omega(n)$ 等較慢的時間複雜度來通過本子任務，但對解決未來的子任務會有障礙，這裡就略過不提。

----

### 做法一：Tree Hash

一般的[樹同構](https://zh.wikipedia.org/zh-tw/%E6%A0%91%E5%90%8C%E6%9E%84)測試其實存在[決定性](https://en.wikipedia.org/wiki/Deterministic_algorithm)的 [AHU 演算法](https://oi-wiki.org/graph/tree-ahu/)，但它的實作較為複雜，而本題又和樹同構有微妙的差別（因為葉子的映射被固定住了），這裡就簡單介紹另一個筆者比較喜歡的樹同構判斷方法，也就是 Tree Hash。

----

Tree Hash 與一般 Hash 的概念相同，目的是把一個複雜的物件壓縮成一個簡單的數字。
- 我們用一個 Hash Function 來將一棵樹壓縮成一個數字，且若兩棵樹同構則壓縮成的數字相同。在實作恰當的情況下，當兩棵樹不同構時，很難被壓縮成同一個數字，可以用壓縮成的數字是否相同，簡單判斷兩棵樹是否同構。
- 但是，Hash 的缺點是實際上存在兩棵不同構的樹被打到同一個數字，只是我們相信發生「碰撞」的機率非常低。
- 因此，簡易的 Hash 實作其實是一個非決定性的做法。

----

給定一個固定的根，以下 `dfs` 遞迴函式可以給出有根樹的 Tree Hash，讓同構的有根樹都打到同一個數字。

```cpp=
unsigned long long seed; // 初始成一個隨機的數字
unsigned long long shift(unsigned long long x) { // 擾動函數，必須相當地沒有規則才可以確保低碰撞機率
  x ^= x << 13; 
  x ^= x >> 7;
  x ^= x << 17;
  return x;
}
unsigned long long dfs(int u, int f) {
  unsigned long long sum = seed; // 一個點的初始 hash 是 seed
  for (int i : G[u])
    if (i != f)
      sum += shift(dfs(i, u)); // 直接加上每個子樹擾動後的 hash 值當作該子樹的 hash 值
  return sum;
}
```

----

前述的 Tree Hash 方式可以證明，若 `shift` 這個擾動函式是純隨機的，那 $n$ 棵樹發生碰撞的次數期望值只有 $O(\frac{n^2}{2^w})$，其中 $w$ 是 hash 值的位元數，也因此我們選用 `unsigned long long` 就能讓碰撞次數降至非常小。
- 不過，並不存在真正純隨機的函式，也因此網路上流傳著各式各樣的擾動函式，前述的函式是筆者慣用的。
- 當然，隨意取例如 $\text{shift}(x)$ 是一個多項式的話是非常容易碰撞的，因為它太有規則了。

----

介紹完一般的樹同構之後要怎麼應用到本題呢？
- 首先，一般判斷無根樹同構需要找重心當根，但本題不用，我們可以指定一個葉節點並直接拿它當作根，這是因為葉子的映射是固定的。
- 既然葉子的映射是固定的，我們可以直接幫每個葉子先行賦予一個固定的隨機 hash 值來取代原本的 `seed`。
- 最後，為了幫未來的子任務鋪陳，對於那些 degree 2 的內節點（儘管 Subtask 1 沒有），我們可以直接檢查它的小孩數量來判斷它需不需要被移除，若需要，則直接當作沒有這個點，把子樹的 Tree Hash 值原封不動地回傳上去就好。

----

### 做法二：構造一對一函數

----

由於本題幫我們把葉子的映射都確定了，可以考慮直接構造這個一對一函數。
- 要先記得移除 degree 不到 3 的內節點，或是在實作過程中處理掉。

----

目標：不斷地拔掉 degree 不超過 1 的點，並在拔掉點時嘗試幫它的父節點賦予或檢查映射值
- 維護一條 queue，裡面裝著所有 degree 不超過 1 的點，一開始裝著 $1, 2, \ldots, n$。
- 每次拔點時，好好維護所有點的映射值：
    - 若有父節點且兩棵樹皆無映射值，則好好賦予。
    - 否則若有父節點，檢查兩邊的映射值是否相同，若不相同則可直接判斷兩棵樹不類似，即使是只有一邊被賦予值也代表不類似。

若整個過程都沒有產生問題，就能判斷兩棵樹類似。

----

以下我們假定讀者已經有辦法將 Subtask 1 當作一個線性時間內判斷兩棵樹相似的黑盒子。
- 本題的 Subtask 1 非常重要。

----

## Subtask 2 : $k\in\{0, 1\}$
## Subtask 3 : $k\leq 2$、$n+m_1 \leq 30$ 且 $n+m_2 \leq 30$

----

這兩個子問題的做法其實可以相同：考慮 $O(n^k)$ 枚舉 $T_1$ 要切斷哪 $k$ 條邊、$O(n^k)$ 枚舉 $T_2$ 要切斷哪 $k$ 條邊，再 $O(n)$ 判斷剩下的演化森林是否相同即可。
- 總共的時間複雜度會是 $O(n^{2k+1})$。

----

## Subtask 4 : $k\leq 2$、$n+m_1 \leq 300$ 且 $n+m_2 \leq 300$

----

兩邊都花 $O(n^k)$ 枚舉的代價非常之痛，因此我們考慮只枚舉一邊，另一邊嘗試直接檢查並計算方法數來算出答案。

----

枚舉完 $F_1$ 之後，我們其實可以先看看 $T_2$ 上有哪些點是一定要在同一塊的。
- 這裡，我們假定切割完後的 $k+1$ 棵樹會被染成相異的 $k+1$ 種顏色。

----

一開始，將 $T_2$ 內的葉節點先染成對應的顏色。
- 對於每一種顏色，讓這些顏色的葉節點按照其在 $T_2$ 內的預處理 DFS 序排序。
    - 若只有一個點，則不需再做任何動作。
    - 否則，最小 DFS 序點和最大 DFS 序的最低共同祖先會被染成同一個顏色，這個最低共同祖先同時也會是所有該顏色點的最低共同祖先。
- 找到這個最低共同祖先後，每個點可以暴力往上染色，並在遇到已經染色過的點時停下來
    - 這裡其實可以做到線性，因為每個點至多被染一次，若有一個點被染上兩種顏色，那麼該次窮舉的 $F_1$ 便不合法。

----

如此一來便檢查完合法性了，接下來計算方法數有兩種做法：
- 直接判斷法
- 樹 DP

----

### 做法一：直接判斷法

----

其實可以觀察到，染完色之後若還有沒被著色的節點，則 $F_2$ 就有 $3$ 種；否則為 $1$ 種。
- 這個情況僅限於 $k\leq 2$，讀者可以自行反過來進行將至多 $3$ 棵樹的演化森林構造回一整棵樹看看，再觀察有幾種切割回來的方法。

----

### 做法二：樹 DP

----

若 $k$ 沒有限制，則存在 $O(nk)$（或根據實作有可能是 $O(nk^2)$）的樹 DP 方法數計算方法。
- 但本題因為已有 $O(n^k)$ 的瓶頸在，我們認為出到 $k=3$ 時已無太大意義。

----

首先我們先將問題對應成較簡單的形式：
- 將染成同一顏色的點縮成一個點，並改統一標為黑色。
- 將未染色的點留成白色的點。

問題變成給定一個樹，問有幾種切 $k$ 條邊的方法使得所有黑色點都在不同的連通塊。

----

考慮以下樹 DP 狀態：
- $\text{dp1}_{u, i}$：$u$ 的子樹切了 $i$ 條邊都合法的情況下，且連接著 $u$ 的連通塊**還有**黑色點。
- $\text{dp2}_{u, i}$：$u$ 的子樹切了 $i$ 條邊都合法的情況下，且連接著 $u$ 的連通塊**沒有**黑色點。

這裡將轉移式留給讀者自行練習。

----

因此，整題可以在 $O(n^{k+1})$ 的時間內通過，若採用樹 DP 的話可能是 $O(kn^{k+1})$ 或 $O(k^2n^{k+1})$，但都無傷大雅。

----

一份可以通過整題的解答，使用：
- Tree Hash 實作兩棵樹相似的檢查。
- 併查集較為偷懶地進行染色。
- 樹 DP 統計 $F_2$ 的種類數。
```cpp=
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include <random>
using namespace std;

const int MAXN = 305;

struct DSU 
{
    int boss[MAXN];
    void init(int n)
    {
        iota(boss + 1, boss + n + 1, 1);
    }
    int get_boss(int x)
    {
        if (boss[x] == x) return x;
        return boss[x] = get_boss(boss[x]);
    }
    bool Union(int x, int y)
    {
        x = get_boss(x), y = get_boss(y);
        if (x == y) return false;
        boss[x] = y;
        return true;
    }
} dsu1, dsu2;

unsigned long long seed;
unsigned long long shift(unsigned long long x) 
{
    x ^= x << 13; 
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

unsigned long long base[MAXN];
int vis[MAXN];

unsigned long long dfs(int u, int f, const vector<int> *G, const int &n, const int &boss) 
{
    vis[u] = 1;
    if (u <= n && u != f) 
    {
        if (boss) dsu1.Union(u, boss); 
        return base[u];
    }
    if (G[u].size() == 1 && u != f) return 0; 
    unsigned long long sum = 0;
    vector<unsigned long long> child;
    for (int i : G[u])
        if (i != f)
        {
            unsigned long long res = dfs(i, u, G, n, boss);
            if (res != 0)
                child.push_back(res);
        }
    if (int(child.size()) > 1) sum += seed;
    for (auto v : child)
    {
        if (int(child.size()) > 1)
            v = shift(v);
        sum += v;
    }       
    return sum;
}

vector<pair<int, int>> T1_edges;
vector<int> T2[MAXN], F1[MAXN], F2[MAXN], SG[MAXN];
int pa2[MAXN], in2[MAXN], out2[MAXN], dft2, stk[MAXN], stktp;
pair<int, int> dp[MAXN][5];

void cal(int u, int f, const int &k)
{
    for (int i = 0; i <= k; i++)
        dp[u][i] = make_pair(0, 0);
    if (vis[u]) dp[u][0].second = 1;
    else dp[u][0].first = 1;
    for (int i : SG[u])
        if (i != f) 
        {
            cal(i, u, k);
            for (int a = 0; a <= k + 1; a++)
                dp[0][a] = make_pair(0, 0);
            for (int a = 0; a <= k; a++)
                for (int b = 0; a + b <= k; b++)
                {
                    dp[0][a + b].first += dp[u][a].first * dp[i][b].first;
                    dp[0][a + b + 1].first += dp[u][a].first * (dp[i][b].first + dp[i][b].second);
                    dp[0][a + b].second += dp[u][a].first * dp[i][b].second;
                    dp[0][a + b].second += dp[u][a].second * dp[i][b].first;
                    dp[0][a + b + 1].second += dp[u][a].second * (dp[i][b].first + dp[i][b].second);
                }
            for (int a = 0; a <= k; a++)
                dp[u][a] = dp[0][a];
        }
}

void pre(int u, int f, const int &n)
{
    in2[u] = ++dft2, pa2[u] = f;
    if (u <= n)
        stk[++stktp] = u;
    for (int i : T2[u])
        if (i != f)
            pre(i, u, n);
    out2[u] = dft2;
}

bool ancestor2(int u, int v)
{
    return in2[u] <= in2[v] && out2[u] >= out2[v];
}

bool handle(vector<int> group)
{
    int lca = group[0];
    while (!ancestor2(lca, group.back()))
        lca = pa2[lca];
    if (vis[lca]) return false;
    vis[lca] = 1;
    for (int i : group)
        for (; i != lca; i = dsu2.get_boss(i))
        {
            if (vis[i]) return false;
            vis[i] = 1;
            F2[i].push_back(pa2[i]);
            F2[pa2[i]].push_back(i);
            dsu2.Union(i, pa2[i]);
        }
    return true;
}

unsigned long long val[MAXN];
vector<int> group[MAXN];

int solve(int n, int m1, int m2, int k)
{
    vector<int> mask(n + m1 - 1);
    for (int i = 1; i <= k; i++)
        mask[n + m1 - 1 - i] = 1;
    int ans = 0;

    auto check = [&]()
    {
        for (int i = 1; i <= n + m1; i++)
            F1[i].clear(), vis[i] = 0;
        for (int i = 1; i <= n; i++)
            group[i].clear();

        dsu1.init(n);
        for (int i = 0; i < n + m1 - 1; i++)
            if (!mask[i])
            {
                auto [u, v] = T1_edges[i];
                F1[u].push_back(v);
                F1[v].push_back(u);
            }
        for (int i = 1; i <= n; i++)
        {
            if (vis[i]) continue;
            val[i] = dfs(i, i, F1, n, i);
        }
        for (int i = 1; i <= n; i++)
        {
            group[dsu1.get_boss(stk[i])].push_back(stk[i]);
        }
        dsu2.init(n + m2);
        for (int i = 1; i <= n + m2; i++)
            vis[i] = 0, F2[i].clear();
        for (int i = 1; i <= n; i++)
        {
            if (dsu1.get_boss(i) == i)
            {
                if (!handle(group[i])) return 0;
                unsigned long long res = dfs(i, i, F2, n, 0);
                if (res != val[i]) return 0;
            }
        }
        for (int i = 1; i <= n + m2; i++)
            SG[i].clear(), group[i].clear(), vis[i] = 0;
        for (int i = 1; i <= n + m2; i++) 
            group[dsu2.get_boss(i)].push_back(i);
        for (int i = 1; i <= n + m2; i++)
        {
            if (dsu2.get_boss(i) != i) continue;
            vis[i] = 1;
            for (int j : group[i])
                for (int p : T2[j])
                    if (!vis[dsu2.get_boss(p)])
                    {
                        SG[i].push_back(dsu2.get_boss(p));
                        vis[dsu2.get_boss(p)] = 1;
                    }
            vis[i] = 0;
            for (int j : group[i])
                for (int p : T2[j])
                    vis[dsu2.get_boss(p)] = 0;
        }
        for (int i = 1; i <= n; i++)
            vis[dsu2.get_boss(i)] = 1;
        cal(dsu2.get_boss(1), dsu2.get_boss(1), k);
        return dp[dsu2.get_boss(1)][k].second;
    };

    do 
    {
        ans += check();
    } while (next_permutation(mask.begin(), mask.end()));
    return ans;
}

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m1, m2, k;
    cin >> n >> m1 >> m2 >> k;
    mt19937_64 rnd(20231208);
    seed = rnd();
    for (int i = 1; i <= n; i++)
        base[i] = rnd();
    for (int i = 1; i < n + m1; i++)
    {
        int u, v;
        cin >> u >> v;
        T1_edges.emplace_back(u, v);
    }
    for (int i = 1; i < n + m2; i++)
    {
        int u, v;
        cin >> u >> v;
        T2[u].push_back(v);
        T2[v].push_back(u);
    }
    pre(1, 1, n);
    for (int i = 0; i <= k; i++)
    {
        int res = solve(n, m1, m2, i);
        if (res > 0)
        {
            cout << i << "\n";
            if (i) cout << res << "\n";
            return 0;
        }
    }
    cout << "-1\n";
}
```

----

前一頁解答的整體時間複雜度是 $O(n^{k+1}(k^2+\alpha(n)))$，但依然能穩定的在一秒內跑完（本題時限為五秒）。
- 本題用來產生答案的程式碼則是全程使用決定性做法。

---

# B. AI Simulation

----

枚舉所有可能的 $\mathbf{q}$，接著對於任意下標序列 $\mathbf{j}$，檢查 $\mathbf{q}$ 是否與 $\mathbf{b_1}, \mathbf{b_2}, \ldots, \mathbf{b_n}$ 的其中一個在 $\mathbf{j}$ 上相同。統計一下能發現

* 有 $\left(\binom{k}{0}+\binom{k}{1}+\binom{k}{2}+\binom{k}{3} = O(k^3)\right)$ 種可能的 $\mathbf{q}$。
* 有 $\left(\binom{k}{t} \le \binom{k}{\lfloor k/2\rfloor} = O(\frac{2^k}{\sqrt{k}})\right)$ 種可能的 $\mathbf{j}$。
* 總共有 $\left(n = O(n)\right)$ 個 $\mathbf{b_i}$ 要檢查。

由於本題的 $k$ 相較於 word size ($64$) 很小，檢查 $\mathbf{q}$ 與某個 $\mathbf{b_i}$ 在 $\mathbf{j}$ 上是否相同，可以用位元壓縮做到 $O(1)$ 時間，故總時間複雜度為 $O(nk^{\frac52}2^k)$。

----

官解

```!=
#include <bitset>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int N, K, T;
vector<uint32_t> users;
set<uint32_t> users_set;

bool check(uint32_t q) {
    if (users_set.find(q) != users_set.end())
        return false;

    string mask = string(K - T, '0') + string(T, '1');
    do {
        uint32_t bmask = bitset<32>(mask).to_ulong();
        bool ok = false;
        for (auto &u: users)
            if ( (q&bmask) == (u&bmask) ) {
                ok = true;
                break;
            }
        if (!ok) return false;
    } while (next_permutation(mask.begin(), mask.end()));
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> K >> T;

    for (int i = 0; i < N; ++i) {
        bitset<16> b;
        cin >> b;

        users.emplace_back(b.to_ulong());
        users_set.emplace(b.to_ulong());
    }

    // O(K^3 * C(K,T) * n)
    uint32_t q = 0;
    do {
        // 0 bits
        if (check(q = 0))
            goto end_of_search;
        // 1 bits
        for (int i = 0; i < K; ++i)
            if (check(q = (1 << i)))
                goto end_of_search;
        // 2 bits
        for (int i = 0; i < K; ++i)
            for (int j = i + 1; j < K; ++j)
                if (check(q = (1 << i) | (1 << j)))
                    goto end_of_search;
        // 3 bits
        for (int i = 0; i < K; ++i)
            for (int j = i + 1; j < K; ++j)
                for (int k = j + 1; k < K; ++k)
                    if (check(q = (1 << i) | (1 << j) | (1 << k)))
                        goto end_of_search;
        // fail
        q = -1;
    end_of_search:
        break;
    } while (false);

    if (q == -1)
        cout << "none\n";
    else {
        for (int i = K-1; i >= 0; --i) {
            cout << ((q >> i) & 1);
        }
        cout << '\n';
    }
}
```

---

# C. Autocopilot

----

## Subtask 1 : 輸入是一棵有向樹

----

可以觀察到，汽車從 $s$ 開始出發、走到 $t$ 的過程中一定都要待在 $t$ 的祖先上。
- 因此，只需要將 $s$ 到 $t$ 的路徑抓出來，數有幾個會產生「分支」的點就是所需要花費的硬幣數。

----

## Subtask 2 : 輸入是有向無環圖

----

講到有向無環圖，自然就會想到能不能拓撲排序後動態規劃看看？
- 令 $\text{dp}_u$ 為從節點 $u$ 出發時，至少要備妥幾個硬幣才能確保汽車會走到節點 $t$。
- base case: $\text{dp}_t = 0$、$\text{dp}_x = \infty$ 對於所有走不到 $t$ 的點 $x$。

----

$\text{dp}_u$ 的答案為何？
- 若選擇花一枚硬幣，對於 $u$ 指向的那些點，選擇 dp 值最小的點走肯定最好。
    - 因此，$\min_{(u, v)\in E}\{\text{dp}_v + 1\}$ 可以用來更新 $\text{dp}_u$。
- 若選擇讓 AI 隨機走，對於 $u$ 指向的那些點，那最差的情況下 AI 會不小心走到 dp 值最大的點。
    - 因此，$\max_{(u, v)\in E}\{\text{dp}_v\}$ 可以用來更新 $\text{dp}_u$。

----

結論，$\text{dp}_u = \min\{\max_{(u, v)\in E}\{\text{dp}_v\}, \min_{(u, v)\in E}\{\text{dp}_v + 1\}\}$
- 可拓撲排序後做到 $O(n + m)$。

----

## Subtask 3 : $n \leq 100, m \leq 1000$

----

圖上有了環之後就不能 DP 了？
- 試著想想看 Dijkstra 在做些什麼？

----

最短路的 DP：$\text{dp}_u = \min_{(u, v)\in E}\{\text{dp}_v + w(u, v)\}$
- 當 $w(u, v) \geq 0$，也就是邊權都非負時，dijkstra 就可以找到一個好的計算順序。
- 只要依序計算出來的 dp 值非嚴格遞增，就可以確保轉移順序！

----

因此，套用 Dijkstra 的想法，我們沿用 Subtask 2 時寫出的 DP 式，每次找出當前 DP 值最小的那個點，就可以確定他的 DP 值。
- 這是因為這個點的值已經不可能更小了！

----

不過這題好像又有點不一樣？
- 考慮這張圖
![image](https://hackmd.io/_uploads/r1VBHTE86.png)
- 1, 2 的 DP 值在計算出來之前，我們無從用 Subtask 2 的 DP 式得出他是 0！
- 這似乎是因為他們互相轉移了。

----

問題回到原點了嗎？
- 考慮一下已經計算出所有答案的理想狀態，可以發現有些點的最佳策略是花錢、有些點的最佳策略是讓 AI 隨機。
- 那麼其實有這樣的 DP 計算順序：
    - DP 值為 0（終點）$\leftarrow$ DP 值為 0（隨機遊走）$\leftarrow$ DP 值為 1（花錢）$\leftarrow$ DP 值為 1（隨機遊走）$\leftarrow$ DP 值為 2（花錢）$\leftarrow$ DP 值為 2（隨機遊走）......

----

如果 DP 值為 $x$（隨機遊走）以前的 DP 值都已經計算完畢，那麼要如何計算出 DP 值為 $x+1$（花錢）的點？
- 肯定會有一些未知值的點分別各自指向一個 DP 值為 $x$ 的隨機遊走點，這些點肯定最佳只能是 $x+1$。

----

如果 DP 值為 $x$（花錢 or 終點）以前的 DP 值都已經計算完畢，那麼要如何計算出 dp 值為 $x$（隨機遊走）的點？
- 這時候就有趣了，因為隨機遊走的點其實會互相走到，這時候正確的做法其實是「直接對每個點模擬一遍看看」。
- 模擬什麼？模擬這個點隨機遊走的情況下，會不會走到無法走到終點 $t$ 的點。
- 如果不會，那為什麼不就讓他隨機走就好？**反正當前的 dp 值最大也就 $x$**，因此這個點的最佳策略勢必為隨機遊走，且 dp 值為 $x$。

----

基於以上兩種 case，根據數學歸納法，我們可以證明其正確性。

----

如何實作？
- 按照先前提到的計算順序計算。
- 對於花錢成 DP 值 $x$ 的 case，很簡單，更新所有沒有值的、有指到 $x+1$ 的點就好。
- 對於隨機遊走得到 DP 值 $x$ 的 case，對每個點花 $O(n+m)$ 模擬 DFS 一遍，總共花費 $O(n(n+m))$。
- 總共有至多 $O(n)$ 種種類需要計算（注意到答案最多也就 $n-2$），因此總共的時間複雜度為 $O(n^2(n+m))$。

----

## Subtask 4 : $n\leq 300, m\leq 30000$

----

如何進一步優化？
- 對於隨機遊走得到 DP 值 $x$ 的 case，對每個點花 $O(n+m)$ 模擬 DFS 一遍，這步好像就是瓶頸，不能全部的點都一起算嗎？
- 可以！

----

在反圖上對所有「無法走到終點 $t$ 的點」往回做 DFS。
- 碰到已經計算出 DP 值的點就停下來。
- 如此一來，剩下被 DFS 到的點就是那些隨機遊走還有可能走不到 $t$ 的點！
- 我們進一步將時間優化到了 $O(n(n + m))$，已經足以通過本題。

----

官解

```!=
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

const int MAXN = 3005;

vector<int> G[MAXN], RG[MAXN];
int reachable[MAXN], ans[MAXN];
int done[MAXN], vis[MAXN];

void dfs(int u, int *tag) 
{
    tag[u] = 1;
    for (int i : RG[u])
        if (!tag[i])
            dfs(i, tag);
}

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, s, t;
    cin >> n >> m;
    while (m--) 
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        RG[v].push_back(u);
    }
    cin >> s >> t;

    int remain = n;

    fill_n(ans + 1, n, n + 1);
    dfs(t, reachable);
    for (int i = 1; i <= n; i++)
        if (!reachable[i])
            done[i] = 1, --remain;

    auto relax = [&](int u, int d) 
    {
        if (ans[u] > d) 
        {
            ans[u] = d;
        }
    };

    auto random_walk = [&](int current) 
    {
        fill_n(vis + 1, n, 0);
        for (int i = 1; i <= n; i++)
            if (reachable[i] && done[i])
                vis[i] = 1;
        for (int i = 1; i <= n; i++)
            if (!reachable[i] && !vis[i])
                dfs(i, vis);
        for (int i = 1; i <= n; i++)
            if (!done[i] && !vis[i])
                relax(i, current);
    };

    relax(t, 0);
    while (remain > 0) 
    {
        int best = -1, best_val = n + 2;
        for (int i = 1; i <= n; i++)
            if (!done[i]) 
            {
                if (best_val > ans[i])
                    best = i, best_val = ans[i];
            }
        done[best] = 1, --remain;
        for (int i : RG[best])
            relax(i, ans[best] + 1);
        random_walk(ans[best]);
    }

    if (ans[s] == n + 1) cout << "-1\n";
    else cout << ans[s] << "\n";
}
```

----

# 方法二

----

## Subtask 2 : 輸入是有向無環圖

----

設 $\text{dp}_u$ 為節點 $u$ 至終點 $t$ 至少需要花的代幣數。初始一樣設
$$\text{dp}_u = \begin{cases}0,&\text{if }u = t,\\\infty,&\text{otherwise.}\end{cases}$$

----

考慮一個節點 $u$，並設 $u$ 連到 $v_1, v_2, \ldots, v_k$，並不失一般性地假定 $\text{dp}_{v_1} \le \text{dp}_{v_2} \le \ldots \le \text{dp}_{v_k}$，則
1. 若 $\text{dp}_{v_1} = \text{dp}_{v_k} = w$，則因為 $u$ 不管下一步走到哪裡都得花 $w$ 枚代幣，可知 $\text{dp}_u = \text{dp}_{v_1}$。
2. 若 $\text{dp}_{v_1} < \text{dp}_{v_k}$，可知 $\text{dp}_u = \text{dp}_{v_1}+1$。

整體時間複雜度為 $O(n+m)$。

----

## Subtask 4 : $n\leq 300, m\leq 30000$

----

Subtask 2 的轉移式會成立，靠的是輸入的圖沒有環這件事。如果輸入有環，我們先用強連通元件 ([strongly connected component](https://en.wikipedia.org/wiki/Strongly_connected_component), SCC) 分解，把環縮掉不就好了？！

假定我們已經做好了 SCC 分解，並考慮其中一個強連通塊 $C$，試著計算 $C$ 內部所有節點的 $\text{dp}$ 值。

----

設 $C$ 連到外部的節點有 $v_1, v_2, \ldots, v_k$，並不失一般性地假定 $\text{dp}_{v_1} \le \text{dp}_{v_2} \le \ldots \le \text{dp}_{v_k}$。
1. 若 $\text{dp}_{v_1} = \text{dp}_{v_k} = w$，則因為「在不花代幣的情況下，從 $C$ 中的任意節點 $u$ 出發，離開 $C$ 後都得花上 $w$ 枚代幣」，可知 $\text{dp}_u = \text{dp}_{v_1}$。
2. 如果 $\text{dp}_{v_1} < \text{dp}_{v_k}$ 呢？假定連到 $v_1$ 的是 $C$ 中的 $u_1$，則因為「在不花代幣的情況下，從 $u_1$ 隨便走，運氣不好的話離開 $C$ 的第一個點可能是 $v_k$」，可知 $\text{dp}_{u_1} = \text{dp}_{v_1}+1$。

----

上述的情況 2 只算出了 $C$ 的其中一個點 $u_1$ 的 $\text{dp}$ 值。當 $C$ 包含三個以上的點時，$C-u_1$ 可能不再是強連通了，只能重新計算 $C-u_1$ 的 SCC 分解。

![image](https://hackmd.io/_uploads/SktHORF86.png)

----

每算出一個 $\text{dp}$ 值時，可能就需要重做一次 SCC 分解，總時間複雜度與前一個方法同為
$$O(n)\times O(n+m) = O(n(n+m)).$$

----

方法二的解答

```cpp=
#include<algorithm>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

constexpr int INF = 1'000'000'000;

void tsr_get(vector<int> *dag, vector<bool> &vis, int u, vector<int> &tsr){
   vis[u] = true;
   for(int v: dag[u]) if(!vis[v]){
      tsr_get(dag, vis, v, tsr);
   }
   tsr.push_back(u);
}

void scc_collect(vector<int> *grev, vector<bool> &vis, int u, vector<int> &scc){
   vis[u] = true;
   scc.push_back(u);
   for(int v: grev[u]) if(!vis[v]){
      scc_collect(grev, vis, v, scc);
   }
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<vector<int>> g(n);
   while(m-- > 0){
      int u, v;
      scanf("%d%d", &u, &v);
      --u; --v;
      g[u].push_back(v);
   }
   int s, t;
   scanf("%d%d", &s, &t);
   --s; --t;
   g[t].clear();
   vector<bool> vis(n);
   vector<int> ts;
   for(int u=0; u<=n-1; ++u) if(!vis[u]){
      tsr_get(g.data(), vis, u, ts);
   }
   vis.flip();
   reverse(ts.begin(), ts.end());
   vector<vector<int>> grev(n);
   for(int u=0; u<=n-1; ++u) for(int v: g[u]){
      grev[v].push_back(u);
   }
   vector<vector<int>> scc;
   vector<int> scc_no(n);
   for(int u: ts) if(!vis[u]){
      scc.push_back({});
      scc_collect(grev.data(), vis, u, scc.back());
      for(int v: scc.back()){
         scc_no[v] = (int)scc.size()-1;
      }
   }
   vector<int> ans(n, INF);
   while(!scc.empty()){
      vector<int> c = move(scc.back()); scc.pop_back();
      if(c[0] == t){
         ans[t] = 0; scc_no[t] = -1;
         continue;
      }
      int id = scc_no[c[0]], ans_min = INF, ans_max = -INF, u_min = -1;
      for(int u: c) for(int v: g[u]) if(scc_no[v] != id){
         if(ans_min > ans[v]){
            ans_min = ans[v];
            u_min = u;
         }
         ans_max = max(ans_max, ans[v]);
      }
      if(u_min==-1 || ans_min==ans_max){
         for(int u: c){
            ans[u] = ans_min;
            scc_no[u] = -1;
         }
         continue;
      }
      ans[u_min] = ans_min+1;
      scc_no[u_min] = -1;
      if(c.size() == 1){
         continue;
      }
      for(int u: c){
         vis[u] = false;
      }
      vis[u_min] = true;
      ts.clear();
      for(int u: c) if(!vis[u]){
         tsr_get(g.data(), vis, u, ts);
      }
      for(int u: ts){
         vis[u] = false;
      }
      reverse(ts.begin(), ts.end());
      for(int u: ts) if(!vis[u]){
         scc.push_back({});
         scc_collect(grev.data(), vis, u, scc.back());
         for(int v: scc.back()){
            scc_no[v] = (int)scc.size()-1;
         }
      }
   }
   printf("%d\n", ans[s]<INF? ans[s]: -1);
}

```

----

## Bonus？

----

本題有沒有足夠簡單的做法能夠進一步優化時間複雜度，也是我們很在意的點。
- 若仔細觀察，會發現所有複雜度優化的瓶頸在於以下動態資料結構問題：
    - 動態刪點 or 動態刪邊
    - 快速偵測到那些無法被固定源點 $u$ 走到的點
- 這個問題是圖論上著名的 dynamic reachability 的特殊情況，經過簡單的搜尋後，我們還沒有找到足夠快速又適合競賽程式的演算法。

---

# D. Convex Hull

----

* 本節假定讀者熟悉計算平面上簡單多邊形面積的 [shoelace formula](https://en.wikipedia.org/wiki/Shoelace_formula)。
* 由於可能的非 $0$ 面積的兩倍只能是 $800$ 以內的正整數，以下都用陣列（而不是相對慢很多的 `std::unordered_set` 或 `std::set`）記錄所有可能的面積。

----

## Subtask 1 : 只要看平移後重合的三角形就能獲得正確答案

----

直接 $O(n^3m^3)$ 枚舉會超時，必須找出其他解法。
* 設 $S_1 = \{P_i\}_{i=1}^n$ 與 $S_2 = \{Q_j\}_{j=1}^m$。枚舉 $1 \le i \le n$ 與 $1 \le j \le m$，並透過平移使 $P_i$ 與 $Q_j$ 重合。
* 在 $S_2$ 剩下的點中，枚舉平移後重合的 $Q_k$ 與 $Q_l$，並計算 $\Delta Q_jQ_kQ_l$ 的面積。
* 時間複雜度是 $O(nm^3)$。

----

## Subtask 2 : $n+m \le 30$

----

* 枚舉 $S_1$ 的非空子集合 $T_1$，檢查 $T_1$ 是否為 $\operatorname{Conv}(T_1)$ 的頂點。
* 若 $T_1$ 為 $\operatorname{Conv}(T_1)$ 的頂點，取任意 $P_i \in T_1$，接著枚舉 $Q_j \in S_2$，檢查 $P_i$ 平移至 $Q_j$ 時，$T_1$ 是否被 $S_2$ 包含。
* 只要事先對 $S_1$ 中的點依照 $(x, y)$ 座標排序，就能在 $O(|T_1|)$ 時間內以 [Andrew's 演算法](https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain)求出 $\operatorname{Conv}(T_1)$，總時間複雜度為 $O(nm2^n)$。

----

## Subtask 3 : $S_1 = S_2$

----

這個子任務相當於：給定點集合 $S$，求出「子凸包 $\operatorname{Conv}(T)$ 的面積」所形成的集合。

----

我們不妨想一想：一個子凸包邊界是怎麼形成的呢？
![image](https://hackmd.io/_uploads/HyoTxgBLT.png)

----

設 $S = \{P_1, P_2, \ldots, P_n\}$，並設 $C$ 為 $S$ 的一個恰包含 $c$ 條邊（其中 $c\ge2$）的子凸包邊界。將 $C$ 上的每條邊以逆時針定向後，可以得到一堆有向線段，滿足
1. 首尾相連：若 $\mathbf{P_i}\mathbf{P_j}$ 在 $C$ 上，則必存在某個的 $k$，滿足 $\mathbf{P_j}\mathbf{P_k}$ 也在 $C$ 上。
2. 取 $C$ 上 $y$ 座標最大的點 $P_0^*$ 當起點（當有多個點具有相同的最大 $y$ 座標時，取 $x$ 座標最小的那個點當作 $P_0^*$），並遞迴定義 $P_{i+1}^*$ 為「$\mathbf{P_i^*}\mathbf{P_{i+1}^*}$ 為 $C$ 上尚未被挑走，且[主輻角](https://en.wikipedia.org/wiki/Argument_(complex_analysis)#Principal_value)（取 $(-\pi, \pi]$ 區間）最小的有向線段」（注意我們有 $P_c^* = P_0^*$）。則
   - 主輻角 $\operatorname{Arg}(\mathbf{P_i^*}\mathbf{P_{i+1}^*})$ 隨著 $i$ 遞增。
   - $\operatorname{Arg}(\mathbf{P_{c-1}^*}\mathbf{P_c^*}) - \operatorname{Arg}(\mathbf{P_0^*}\mathbf{P_1^*}) < 2\pi.$


----

反過來說，如果我們找到了一堆首尾相連的有向線段 $\mathbf{P_{i_0}}\mathbf{P_{i_1}}, \mathbf{P_{i_1}}\mathbf{P_{i_2}}, \ldots, \mathbf{P_{i_{c-1}}}\mathbf{P_{i_c}}=\mathbf{P_{i_{c-1}}}\mathbf{P_{i_0}}$，滿足
1. $\operatorname{Arg}(\mathbf{P_{i_k}}\mathbf{P_{i_{k+1}}})$ 隨著 $k$ 遞增，
2. $\operatorname{Arg}(\mathbf{P_{i_{c-1}}}\mathbf{P_{i_0}}) - \operatorname{Arg}(\mathbf{P_{i_0}}\mathbf{P_{i_1}}) < 2\pi$，

那這些有向線段也會構成子凸包邊界嗎？

答案是肯定的，以下簡單說明原因。

----

假定我們選出了有向線段 $\mathbf{P_{i_k}}\mathbf{P_{i_{k+1}}}$，並畫成圖：
![image](https://hackmd.io/_uploads/SyQiulHI6.png)

----

對於 $l > k$，只要
$$\operatorname{Arg}(\mathbf{P_{i_l}}\mathbf{P_{i_{l+1}}})-\operatorname{Arg}(\mathbf{P_{i_k}}\mathbf{P_{i_{k+1}}}) < \pi,$$ $P_{i_{l+1}}$ 就只能落在射線 $\overrightarrow{P_{i_k}P_{i_{k+1}}}$（不含 $\overline{P_{i_k}P_{i_{k+1}}}$ 本身）上，或 $\overrightarrow{P_{i_k}P_{i_{k+1}}}$ 切出的左半平面（即上圖中的灰色區域）內。

----

因此一旦找到了某個 $l > k$ 滿足 $P_{i_l} = P_{i_k}$，則有 $\operatorname{Arg}(\mathbf{P_{i_{l-1}}P_{i_l}}) - \operatorname{Arg}(\mathbf{P_{i_k}}\mathbf{P_{i_{k+1}}}) \ge \pi.$
![image](https://hackmd.io/_uploads/BkCdbbH8p.png)

----

此時由於
$$\begin{split}
2\pi &> \operatorname{Arg}(\mathbf{P_{i_0}}\mathbf{P_{i_{c-1}}})-\operatorname{Arg}(\mathbf{P_{i_1}}\mathbf{P_{i_0}})\\
&\geq \operatorname{Arg}(\mathbf{P_{i_0}}\mathbf{P_{i_{c-1}}}) - \operatorname{Arg}(\mathbf{P_{i_{k+1}}}\mathbf{P_{i_k}})\\
&= \left(\operatorname{Arg}(\mathbf{P_{i_0}}\mathbf{P_{i_{c-1}}})-\operatorname{Arg}(\mathbf{P_{i_l}}\mathbf{P_{i_{l-1}}})\right)\\
&\ \ \ \ +\left(\operatorname{Arg}(\mathbf{P_{i_l}}\mathbf{P_{i_{l-1}}})-\operatorname{Arg}(\mathbf{P_{i_{k+1}}}\mathbf{P_{i_k}})\right)\\
&\geq \left(\operatorname{Arg}(\mathbf{P_{i_0}}\mathbf{P_{i_{c-1}}})-\operatorname{Arg}(\mathbf{P_{i_l}}\mathbf{P_{i_{l-1}}})\right) + \pi
,\end{split}$$

可知 $\operatorname{Arg}(\mathbf{P_{i_0}}\mathbf{P_{i_{c-1}}})-\operatorname{Arg}(\mathbf{P_{i_l}}\mathbf{P_{i_{l-1}}}) < \pi$。

----

根據先前的討論，$P_{i_0}$ 只能落在射線 $\overrightarrow{P_{i_{l-1}}P_{i_l}}$（不含 $\overline{P_{i_{l-1}}P_{i_l}}$ 本身）上，或 $\overrightarrow{P_{i_{l-1}}P_{i_l}}$ 切出的左半平面（即上圖中的灰色區域）內，故有
1. $k = 0$ 或 $P_{i_0}, P_{i_1}, \ldots, P_{i_{k+1}}$ 共線。
2. $l = c$ 或 $P_{i_{l-1}}, P_{i_l}, \ldots, P_{i_c}=P_{i_0}$ 共線。

----

* 當 $k > 0$ 或 $l < c$ 時，這堆有向線段構成的其實是退化成一條線段的平凡凸包。
* 當 $k = 0$ 與 $l = c$ 時，這堆有向線段才有可能構成一般的凸多邊形（儘管仍有可能出現三點共線，甚至是退化的狀況）。

但無論如何，我們都會得到一個面積 $\ge0$ 的子凸包。

----

接下來可以介紹演算法了。
* $O(n)$ 枚舉 $S$ 的每一點 $P_{i_0}$，嘗試作為子凸包的起點（即 $y$ 座標最大，且 $y$ 座標相同時 $x$ 座標最小的點）。
* 以主輻角遞增的方式，逐步加入有向線段 $\mathbf{P_i}\mathbf{P_j}$，並試著算出每個首尾相連的序列 $P_{i_0}, P_{i_1}, \ldots, P_{i_c}$ 中，所有可能的 $\sum_{k=0}^{c-1}(x_{i_k}y_{i_{k+1}}-x_{i_{k+1}}y_{i_k})$ 值。

----

* 設 $D_{j, a}$ 為「只使用『已加入的有向邊們』的情況下，是否存在下標序列 $i_0, i_1, \ldots, i_c=j$，滿足
  1. $\operatorname{Arg}(\mathbf{P_{i_k}}\mathbf{P_{i_{k+1}}})$ 隨著 $k$ 遞增，且
  2. $\sum_{k=0}^{c-1}(x_{i_k}y_{i_{k+1}}-x_{i_{k+1}}y_{i_k}) = a$
  
  這兩件事」的 `true`／`false` 值。初始設 $D_{i_0, 0}$ 為 `true`，其他皆為 `false`。
* 加入一條有向邊 $\mathbf{P_{j_1}}\mathbf{P_{j_2}}$ 時，利用 $D_{j_1, \cdot}$ 來更新 $D_{j_2, \cdot}$；每條有向邊都加入後，$D_{i_0}$ 就是以 $P_{i_0}$ 作為子凸包起點時，所有可能的面積。
* 枚舉 $i_0 = 1, 2, \ldots, n$，再對每次算出的 $D_{i_0}$ 取聯集，就能獲得答案。

----

只要先將 $O(n^2)$ 個 $\mathbf{P_i}\mathbf{P_j}$ 們根據主輻角排好，總時間複雜度即為 $O(n^3A)$，其中 $A$ 代表可能的 $\sum_{k=0}^{c-1}(x_{i_k}y_{i_{k+1}}-x_{i_{k+1}}y_{i_k})$ 值數，以本題而言為 $2\times800+1=1601$。

----

## Subtask 4 : 無額外限制

----

多枚舉一個維度以考慮所有可能的平移，時間複雜度變成 $O(nm^3A)$。

----

官解

```!=
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

```

----

## 以下反省

* 這題的時限卡得很緊，但為了卡掉 subtask 1 的 naïve $O(n^3m^3)$ 枚舉（經實測跑超快，即使 $n$ 與 $m$ 都設為 $40$，也只花了 $0.5$ 秒），只能這麼做了。
* 作為卡 subtask 1 naïve 演算法的副作用，如果 subtask 4 的解沒用位元壓縮，運氣不好可能會在 subtask 1, 3, 4 超時。

----

最後簡單說明我們是怎麼生 subtask 1 的。只要選兩條平行線 (say, $x = 0$ 與 $x = c$)，在上面亂選 $40$ 個點當作 $S_1$，接著這樣造 $S_2$：
1. 如果 $x \operatorname{mod} 2c < c$，任意選。
2. 如果 $x \operatorname{mod} 2c \ge c$，最多只能選一個點。

注意 $S_1$ 的子凸包只能是三角形或四邊形，而如果是四邊形的話，必有兩個點在 $x=0$ 上，另外兩個點在 $x=c$ 上。另一方面，若 $P(x_1, y_1), Q(x_2, y_2) \in S_2$ 且 $|x_1-x_2| = c$，則 $P$ 與 $Q$ 之中，必有一個點的上下沒有任何其他點，故共同子凸包只能是三角形。

---

# E. Maze

----

這題的做法是 BFS，但實作難度會根據狀態怎麼設計產生雲泥之別。

本節提供筆者的做法供讀者參考。

----

## 狀態

----

如果實際把旋轉操作模擬出來，程式碼的行數會暴增。筆者把迷宮的旋轉方向，改為重力的方向。

* 一次左旋轉會將往下/左/上/右的重力，分別改為往左/上/右/下的重力。
* 一次右旋轉會將往下/右/上/左的重力，分別改為往右/上/左/下的重力。

----

迷宮的狀態可以用小鋼珠們的位置表示。筆者假定每座迷宮都恰有 $3$ 顆小鋼珠，並將不足的部分視為已掉出迷宮。

一顆小鋼珠 $B$ 的位置可以用 $0$ 到 $nm$ 的非負整數 $p$ 表示，其中
1. 若 $p = nm$，代表 $B$ 已掉出迷宮。
2. 若 $0 \le p \le nm-1$，寫 $p = qm+r$，其中
   1. $q, r$ 皆為整數，
   2. $0 \le r \le m-1$，
   
   代表 $B$ 在迷宮中的位置 $(q+1, r+1)$。

----

設三顆小鋼珠的位置分別在 $b_1, b_2, b_3$。由於 $b_1, b_2, b_3$ 的順序並不影響狀態的異同，筆者加上 $b_1 \le b_2 \le b_3$ 這個限制。

迷宮（重力）的方向也應被考慮。筆者加入方向 $D$，其中
1. 若 $D = 0$，迷宮的重力往下。
1. 若 $D = 1$，迷宮的重力往左。
1. 若 $D = 2$，迷宮的重力往上。
1. 若 $D = 3$，迷宮的重力往右。

因此一個狀態可以用 $4$-tuple $(D, b_1, b_2, b_3)$ 表示，目標找出從初始狀態走到 $(D, nm, nm, nm)$ 至少要花幾步。

----

## 轉移

----

考慮一狀態 $S := (D, \ldots)$，則
1. 一次左旋轉後，$S$ 變成 $((D+1)\operatorname{mod}4, \ldots)$。
2. 一次右旋轉後，$S$ 變成 $((D+3)\operatorname{mod}4, \ldots)$。

所有小鋼珠在旋轉後皆會沿著重力的方向掉落，必須算出它們的新位置才能推得旋轉後的狀態。

計算掉落後的新位置，儘管存在 naïve(?) $O(nm)$ 時間的方法，筆者在這裡提供 $O(1)$ 時間的方法供讀者參考。

----

事先算出在沒有其他小鋼珠的情況下，若小鋼珠 $B$ 原本在位置 $(i, j)$，則在沿著重力方向 $D$ 掉落後，$B$ 最後抵達的位置 $P'_{D, (i, j)}$。

儘管也能使用模擬，$P'$ 可以在線性時間內計算完成，且 code 也比模擬短。

----

設 $D'$ 為旋轉後的重力方向。對於 $i = 1, 2, 3$，想把三個新位置寫成 $P'_{D', b_i}$，但這在其中兩個相同時是錯的。

設將 $P'_{D', b_i}$ 由小到大重排後得到 $b_1', b_2', b_3'$。
* 若 $b_1' = b_2'$，則
  * 若 $b_2' = b_3'$，則 $b_3'$ 往 $D'$ 的反方向加 $2$。
  * $b_2'$ 往 $D'$ 的反方向加 $1$。

* 否則，若 $b_2' = b_3'$，則 $b_3'$ 往 $D'$ 的反方向加 $1$。

最後再將 $b_1', b_2', b_3'$ 排序，就能得到新的狀態了，故總時間複雜度為 $O(n^3m^3)$。

----

官解

```cpp=
#include<algorithm>
#include<array>
#include<queue>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<bool> wall(n*m);
   array<int, 3> bead{n*m, n*m, n*m};
   int bead_top = 0;
   for(int i=0; i<=n-1; ++i) for(int j=0; j<=m-1; ++j){
      char sij;
      scanf(" %c", &sij);
      wall[i*m+j] = sij=='w';
      if(sij == 'b'){
         bead[bead_top++] = i*m+j;
      }
   }
   array<vector<int>, 4> drop_pos;
#define DROP_POS_GET(IDX, OUTER_FOR, INNER_FOR, I2, J2) do{\
   drop_pos[IDX] = vector<int>(n*m+1, n*m);\
   OUTER_FOR{\
      int x = n*m;\
      INNER_FOR{\
         if(wall[i*m+j]){\
            x = (I2)*m+(J2);\
         }else{\
            drop_pos[IDX][i*m+j] = x;\
         }\
      }\
   }\
}while(0)
   DROP_POS_GET(0, for(int j=0; j<=m-1; ++j), for(int i=n-1; i>=0; --i), i-1, j);
   DROP_POS_GET(1, for(int i=0; i<=n-1; ++i), for(int j=0; j<=m-1; ++j), i, j+1);
   DROP_POS_GET(2, for(int j=0; j<=m-1; ++j), for(int i=0; i<=n-1; ++i), i+1, j);
   DROP_POS_GET(3, for(int i=0; i<=n-1; ++i), for(int j=m-1; j>=0; --j), i, j-1);
#undef DROP_POS_GET
   int n_pos = n*m+1, init = 0;
   for(int p: bead){
      init = n_pos*init + p;
   }
   queue<pair<int, int>> bfs;
   vector<bool> vis(4*n_pos*n_pos*n_pos);
   bfs.emplace(init, 0);
   vis[init] = true;
   array<int, 4> dpos{-m, 1, m, -1};
   while(!bfs.empty()){
      auto [s, a] = bfs.front(); bfs.pop();
      if(s%(n_pos*n_pos*n_pos) == n_pos*n_pos*n_pos-1){
         printf("%d\n", a);
         return 0;
      }
      array<int, 3> b;
      for(int i=2; i>=0; --i){
         b[i] = s%n_pos; s /= n_pos;
      }
#define G_FORCE(D) do{\
      array<int, 3> b2;\
      for(int i=0; i<=2; ++i){\
         b2[i] = drop_pos[D][b[i]];\
      }\
      sort(b2.begin(), b2.end());\
      if(b2[0]==b2[1] && b2[1]!=n_pos-1){\
         if(b2[1] == b2[2]){\
            b2[2] = b2[0] + 2*dpos[D];\
         }\
         b2[1] = b2[0] + dpos[D];\
      }else if(b2[1]==b2[2] && b2[2]!=n_pos-1){\
         b2[2] = b2[1] + dpos[D];\
      }\
      sort(b2.begin(), b2.end());\
      int s2 = (D);\
      for(int p: b2){\
         s2 = n_pos*s2 + p;\
      }\
      if(!vis[s2]){\
         bfs.emplace(s2, a+1);\
         vis[s2] = true;\
      }\
}while(0)
      G_FORCE((s+1)%4);
      G_FORCE((s+3)%4);
#undef G_FORCE
   }
   puts("-1");
}

```

----

題目的最早版本並沒有限制鋼珠的數量。原出題者預期的做法是用 BFS，並搭配 bit string 做狀態壓縮。當時尚未決定最大的 subtask 3 的範圍，不過就連 subtask 2 的 $n, m \le 10$，筆者也手動造出了至少需要旋轉 $124$ 次才能拿出所有小鋼珠的迷宮：
```
w w w w w w w w w w
w b b b b b b b b w
w b b b b b b b b w
w b b b b b b b b w
w b b b b b b b b w
w b b b b b b b b w
w b b b b b b b b w
w w b b b b b b b w
w s b b b b b b b w
w s w w w w w w w w
```

最後決定限制小鋼珠的數量不超過 $3$，並提高 $n, m$ 的上限至 $15$。

----

儘管一度有卡掉 naïve 轉移的打算，實測後發現要讓 expand 出的狀態數跑滿很困難。筆者手動造出的 $15\times15$ 迷宮中，最多也只 expand 了不到 $40000$ 個狀態，故只好讓 $O(nm)$ 時間的轉移 (i.e. 總時間複雜度 $O(n^4m^4)$) 也能通過。

本題測資全部都是手動生成的（因為想不到該怎麼 random 生出有解且夠複雜的迷宮 QQ），希望能卡掉各種不小心寫出的 bug。

---

# F. Monster

----

## Subtask 2 : 查詢任意房間的黑色恐怖距離

----

1. 開一條陣列 $d_{x, y, z}$ 記錄房間 $(x, y, z)$ 的黑色恐怖距離，初始皆設為 $\infty$。
2. 將每間餐廳的位置 $(p_i, q_i, r_i)$ 的 $d$ 值更新為 $0$，並放入佇列 $Q$ 中。
3. 拿 $Q$ 做 BFS，就能得到所有房間的答案。

時間複雜度為 $O(FMN)$。

----

## Subtask 3 : $FMN \le 3000$

----

將每個房間視為節點，其中節點 $u, v$ 相鄰若且唯若兩個房間相鄰（即在隔壁、樓下或樓上）。
1. 賦予每個節點 $u$ 權重 $d_u$，並將節點們依照權重由大到小排序。
2. 仿照 [Kruskal's 演算法](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)，從空集合開始逐步加入每個節點。加入節點 $u$ 時，如果 $u$ 有已被加入的鄰居 $v$，則嘗試連接 $u$ 與 $v$。

最後會得到一棵生成樹 $T$，且 $u, v$ 間最小的黑色恐怖距離的最大值，即為 $u, v$ 在 $T$ 中的路徑上，點權重的最小值。

----

* 建立 $T$ 需要對 $d_u$ 排序；但事實上我們做 BFS 時，將訪問的順序反過來，就得到了點權重 $d_u$ 遞減的節點序列。因此只需要 $O(FMN\alpha(FMN))$ 時間，就能建好 $T$。
* 將 $T$ 上的每個節點當成搜尋起點，就能算出每個點對 $(u, v)$ 的答案。

時間複雜度為 $O(F^2M^2N^2)$。

----

## Subtask 4 : $Q = 1$

----

建立 $T$ 的過程中，持續檢查 $s_1 := (a_1, b_1, c_1)$ 與 $t_1 := (x_1, y_1, z_1)$ 的連通狀況。一旦加入了某個節點 $u$ 後 $s_1$ 與 $t_1$ 連通了，就知道答案是 $d_u$。

時間複雜度為 $O(FMN\alpha(FMN))$。

----

## Subtask 5 : 無額外限制

----

注意第 $i$ 筆詢問的答案 $d_i^*$ 為 $T$ 上 $s_i := (a_i, b_i, c_i)$ 與 $t_i := (x_i, y_i, z_i)$ 之間的點權重最小值。

任選 $T$ 中的某個點 $r$ 當根後，只要找出 $s_i$ 與 $t_i$ 的最近共同祖先 ([lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor), LCA) $a_i$，$d_i^*$ 就是「$s_i$ 與 $a_i$ 之間的最小點權重」與「$t_i$ 與 $a_i$ 之間的最小點權重」之間的最小值。

----

![image](https://hackmd.io/_uploads/BkujBePLT.png)

----

定義
1. $P_{0, u}$ 為 $u$ 的父節點；特別地，$P_{0, r} := r$。
2. $M_{0, u} = \min\{d_u, d_{P_{0, u}}\}.$

接著對於所有的 $i\ge1$，遞迴定義
1. $P_{i, u} = P_{i-1, P_{i-1, u}},$
2. $M_{i, u} = \min\{M_{i-1, u}, M_{i-1, P_{i-1, u}}\}.$

注意 $P_{i, u}$ 為 $u$ 的上 $2^i$ 層祖先，而 $M_{i, u}$ 為 $u$ 至 $P_{i, u}$ 之間點權重的最小值。這種「利用兩個長度為 $2^{i-1}$ 的區間資訊，算出長度為 $2^i$ 的區間資訊」的手法又稱為倍增 (binary lifting)，也可見於 [sparse table](https://cp-algorithms.com/data_structures/sparse-table.html) 與 [suffix array](https://en.wikipedia.org/wiki/Suffix_array) 的建立。

----

有了 $P$ 與 $M$，就能將一般的任兩個節點間的 LCA 查詢，修改成任兩個節點間的最小值查詢了。

總時間複雜度為
* 建立 $O(FMN\log(FMN))$。
* 每筆查詢 $O(\log(FMN))$。

由於這種基於倍增的 LCA 查詢在網路上的資源非常多，限於篇幅這裡就不詳細介紹了，對此技巧不熟的讀者也能從學著做這題開始。

----

官解

```cpp=
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

void dfs(vector<int> const *g, int u, int p, int d, int *p_rec, int *d_rec){
   p_rec[u] = p;
   d_rec[u] = d;
   for(int v: g[u]) if(v != p){
      dfs(g, v, u, d+1, p_rec, d_rec);
   }
}

int main(){
   int f, m, n, r;
   scanf("%d%d%d%d", &f, &m, &n, &r);
   auto sc = [m, n](int i, int j, int k){
      return (i*m+j)*n+k;
   };
   vector<int> d(f*m*n, -1), bfs;
   while(r-- > 0){
      int i, j, k;
      scanf("%d%d%d", &i, &j, &k);
      --i; --j; --k;
      d[sc(i, j, k)] = 0;
      bfs.push_back(sc(i, j, k));
   }
   for(size_t i0=0; i0<bfs.size(); ++i0){
      int bf = bfs[i0], dbf = d[bf];
      int k = bf%n, j = bf/n%m, i = bf/n/m;
      int p;
#define PUSH(COND, I2, J2, K2) do{\
      if((COND) && d[p = sc((I2), (J2), (K2))]==-1){\
         d[p] = dbf+1; bfs.push_back(p);\
      }\
}while(0)
      PUSH(i>0, i-1, j, k);
      PUSH(i+1<f, i+1, j, k);
      PUSH(j>0, i, j-1, k);
      PUSH(j+1<m, i, j+1, k);
      PUSH(k>0, i, j, k-1);
      PUSH(k+1<n, i, j, k+1);
#undef PUSH
   }
   vector<int> djs(f*m*n, -1);
   auto djs_find = [djs=djs.data()](int i){
      int r = i;
      while(djs[r] != -1){
         r = djs[r];
      }
      while(djs[i] != -1){
         int j = djs[i];
         djs[i] = r;
         i = j;
      }
      return r;
   };
   vector<vector<int>> g(f*m*n);
   vector<bool> vis(f*m*n);
   for(size_t i0=bfs.size(); i0-->0; ){
      int u = bfs[i0];
      int k = u%n, j = u/n%m, i = u/n/m;
      vis[u] = true;
      int v, p, q;
#define ADD_EDGE(COND, I2, J2, K2) do{\
      if((COND) && vis[v = sc((I2), (J2), (K2))] && (p=djs_find(u))!=(q=djs_find(v))){\
         g[u].push_back(v);\
         g[v].push_back(u);\
         djs[q] = p;\
      }\
}while(0)
      ADD_EDGE(i>0, i-1, j, k);
      ADD_EDGE(i+1<f, i+1, j, k);
      ADD_EDGE(j>0, i, j-1, k);
      ADD_EDGE(j+1<m, i, j+1, k);
      ADD_EDGE(k>0, i, j, k-1);
      ADD_EDGE(k+1<n, i, j, k+1);
#undef ADD_EDGE
   }
   vector<vector<int>> p{vector<int>(f*m*n)};
   vector<int> dep(f*m*n);
   dfs(g.data(), 0, 0, 0, p[0].data(), dep.data());
   vector<vector<int>> dp{vector<int>(f*m*n)};
   for(int u=0; u<=f*m*n-1; ++u){
      dp[0][u] = min(d[u], d[p[0][u]]);
   }
   for(int i=0; any_of(p[i].cbegin(), p[i].cend(), [](int x){return x;}); ++i){
      p.push_back(vector<int>(f*m*n));
      dp.push_back(vector<int>(f*m*n));
      for(int u=0; u<=f*m*n-1; ++u){
         p[i+1][u] = p[i][p[i][u]];
         dp[i+1][u] = min(dp[i][u], dp[i][p[i][u]]);
      }
   }
   int q;
   scanf("%d", &q);
   while(q-- > 0){
      int s1, s2, s3, t1, t2, t3;
      scanf("%d%d%d%d%d%d", &s1, &s2, &s3, &t1, &t2, &t3);
      --s1; --s2; --s3; --t1; --t2; --t3;
      int s = sc(s1, s2, s3), t = sc(t1, t2, t3);
      if(dep[s] < dep[t]){
         swap(s, t);
      }
      int ans = min(d[s], d[t]);
      for(size_t i=p.size(); i-->0; ){
         if(dep[p[i][s]] >= dep[t]){
            ans = min(ans, dp[i][s]);
            s = p[i][s];
         }
      }
      if(s != t){
         for(size_t i=p.size(); i-->0; ){
            if(p[i][s] != p[i][t]){
               ans = min({ans, dp[i][s], dp[i][t]});
               s = p[i][s]; t = p[i][t];
            }
         }
         ans = min(ans, d[p[0][s]]);
      }
      printf("%d\n", ans);
   }
}

```

----

* 題目的最早版本只有一筆詢問（即 $Q = 1$）。由於這場比賽實作困難題目的還不少，而這題即使改成多筆詢問，對熟悉的選手而言負擔也不會增加得太大，就改成了現行版本。
  * 然後發現大部分的 AC code 都在讀入所有詢問後一起處理 QAQ
* 曾經想過提高 $F, M, N$ 以推廣 [Voronoi diagram](https://en.wikipedia.org/wiki/Voronoi_diagram)，但發現在三維空間中，$n$ 個點的 Voronoi diagram 最糟會退化成 $\Theta(n^2)$ 個節點（可參考 [[1]](https://en.wikipedia.org/wiki/Voronoi_diagram#Generalizations_and_variations) 與 [[2]](https://www.cse.ust.hk/~golin/pubs/3D_Voronoi_I.pdf)），只好放棄。

---

# G. Museum

----

標出價值前 $k$ 高的作品，接著用減法算出它們個別要被移動幾次，時間複雜度與排序同為 $O(n\log n)$。

----

官解

```!=
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    // weight, index, flag
    vector<tuple<int, int, int>> c;

    for (int i = 0; i < N; ++i) {
        int weight;
        cin >> weight;
        c.emplace_back(weight, i, 0);
    }

#define flag(idx) get<2>(c[(idx)])
    stable_sort(c.begin(), c.end(), [](auto a, auto b) {
        if (get<0>(a) != get<0>(b))
            return get<0>(a) > get<0>(b);
        return get<1>(a) < get<1>(b);
    });
    for (int i = 0; i < K; ++i)
        flag(i) = 1;

    sort(c.begin(), c.end(), [](auto a, auto b) {
        // sort by index
        return get<1>(a) < get<1>(b);
    });

    // move distance max to (10^6)^2
    long long ans = 0;
    int j = 0;
    for (int i = 0; i < K; ++i) {
        if (flag(i) == 0) {
            j = max(j, i + 1);
            while (flag(j) == 0)
                j++;
            swap(c[i], c[j]);
            ans += j - i;
        }
    }

    cout << ans << '\n';
}
```

----

* **Subtask 1**: 以防有人不會 call library 也不會手爆 $O(n\log n)$ 時間的排序。
* **Subtask 2**: 以防有人在只拿 $c_i$ 當 key 的情況下，call 了 [unstable](https://en.wikipedia.org/wiki/Sorting_algorithm#Stability) 版本的排序 (e.g. `std::sort`)。

---

# H. Palindrome

----

## Subtask 1 : $n_i \le 30$

----

可能可以拿來練習暴搜 (?

----

## Subtask 2 : $n_i \le 10^3$

----

設答案為 $D_n$。若 $n$ 是奇數，我們有

$$D_n = 1 + (D_{n-2} + D_{n-4} + \ldots + D_1).$$

若 $n$ 是偶數，我們有

$$D_n = 2 + (D_{n-2} + D_{n-4} + \ldots + D_2).$$

給定初始條件 $D_1 = 1, D_2 = 2$，可以花 $O(n^2)$ 時間得到 $1 \ldots n$ 的答案。

----

## Subtask 3 : $n_i \le 10^6$

----

無論 $n$ 是奇數還是偶數，只要 $n \ge 3$，直接將遞迴式相減可得

$$D_n - D_{n-2} = D_{n-2}.$$

也就是對任意 $n \ge 3$，均有 $D_n = 2D_{n-2}$。

----

## Subtask 4 : $n_i \le 10^{15}$

----

由於 $D_n = 2^{\lfloor\frac n2\rfloor}$，可以直接使用[快速冪](https://en.wikipedia.org/wiki/Exponentiation_by_squaring)。

----

官解

```!=
#include <iostream>
using namespace std;

const int mod = 1e9 + 7;

int mod_pow(int a, long long int n) 
{
    if (n == 0) return 1;
    int half = mod_pow(a, n / 2);
    half = (long long int)half * half % mod;
    if (n % 2 == 1) half = (long long int)half * a % mod;
    return half;
}

void solve()
{
    long long int n;
    cin >> n;
    cout << mod_pow(2, n / 2) << "\n";
}

int main() 
{
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++)
    {
        solve();
    }
    return 0;
}

```

----

其實 $D_n = 2D_{n-2}$ 有個直觀的解釋方式。以範例中的 $n = 6$ 來說，將所有的分解法拆成兩類：

| 首尾皆為 $1$ | 首尾皆不為 $1$ |
|:---:|:---:|
| $1+4+1$ | $6$ |
| $1+2+2+1$ | $3+3$ |
| $1+1+2+1+1$ | $2+2+2$ |
| $1+1+1+1+1+1$ | $2+1+1+2$ |

可以看出首尾皆為 $1$，與首尾皆不為 $1$ 的分解法之間，存在一個雙射 ([bijection](https://en.wikipedia.org/wiki/Bijection)) 關係。由於首尾皆為 $1$ 的分解方法數為 $D_{n-2}$，自然有 $D_n = 2D_{n-2}$。

---

# I. Race

----

## Subtask 1 : $n \leq 100, P \leq 100$

----

這個子問題只需要花費 $O(P^2)$ 窮舉所有可能的選值，再 $O(n)$ 檢查即可。

----

## Subtask 2 : $n \leq 100, P \leq 10000$

----

觀察
- 所有可能的選值，必可從 $a_i + 1 - b_i$ 中挑出。
    - 這裡取[同餘](https://zh.wikipedia.org/zh-tw/%E5%90%8C%E9%A4%98) $P$ 的最小非負整數。
- 這是因為我們可以把第 $i$ 場比賽能夠勝利的選值想像成 $0\sim P-1$ 這個環狀序列的一個區間 $[a_i + 1 - b_i, P - 1 - b_i]$。
- 若其中一個取值不為 $a_i + 1 - b_i$，嘗試將其減去一，並不會讓任何一個原本靠該值勝利的比賽「離開」勝利區間。

----

由於所有可能的選值必可從 $a_i + 1 - b_i$ 中挑出，可將 $O(nP^2)$ 的窮舉降低為 $O(n^3)$ 以通過本子題。

----

## Subtask 3 : $n \leq 5000$

----

先窮舉第一選值，接著對於那些無法靠該值勝利的比賽，進一步考慮讓它們主動去標記哪些第二選值可以讓它們勝利。
- 接著從所有可能的第二選值中，挑出被標記最多次的就會是當前的最佳解。

----

若胡亂窮舉第一選值，很有可能每場比賽會不斷地在勝利和尚未勝利之間來回切換。一場比賽切換一次的代價是 $O(n)$ 的標記時間，因此若 $n$ 場比賽都需要 $O(n)$ 次切換，時間複雜度就會再次回到 $O(n^3)$。

----

但如果照著 $a_i + 1 - b_i$ 的遞增順序窮舉呢？
- Subtask 2 有提到每場比賽勝利的選值是一個區間，因此實際上這個區間只會被進入一次、離開一次，切換的次數就可以降低到 $O(1)$！
- 時間複雜度 $O(n^2)$，足以通過本子題。

----

## Subtask 4 : $b_i \leq a_i$

----

當 $b_i \leq a_i$ 時，第 $i$ 場比賽能夠勝利的選值 $[a_i + 1 - b_i, P - 1 - b_i]$ 其實就是一個 $0\sim P-1$ 不會跨過頭尾的正常區間。
- 回想到 Subtask 3 時，切換比賽的勝利狀態我們要做的事情──對所有可以勝利的第二選值加上 $1$ 或減去 $1$。
- 這不就是區間加值、區間減值嗎？
- 而查詢被標記最多次的選值，其實就是問全部的最大值。

----

使用能夠區間加減值、維護最大值的資料結構（e.g. [線段樹](https://zh.wikipedia.org/zh-tw/%E7%BA%BF%E6%AE%B5%E6%A0%91_(%E5%8C%BA%E9%97%B4%E6%9F%A5%E8%AF%A2))），便可以把切換的代價降至 $O(\log n)$。
- 但還有一個問題，該如何快速找到需要切換狀態的比賽？

----

只要好好對每場比賽的勝利取值區間排序，即可在窮舉到對應值時進行切換。
- 整體複雜度降為 $O(n\log n)$。

----

## Subtask 5 : $n\leq 2\times 10^5$

----

$b_i > a_i$ 開始可能發生，難道區間變成環狀意義上的區間就不能區間加減值了嗎？
- 一個最簡單的做法其實就是把跨頭尾的區間拆成兩個，變成 $[0, P - 1 - b_i]$ 和 $[a_i + 1 - b_i, P - 1]$。
- $O(1)$ 個區間修改一樣是 $O(\log n)$。
- 總時間複雜度 $O(n\log n)$，已足以通過本題。

----

官解
- 官解實際上利用了「跨頭尾區間等價全部除去一個非跨頭尾區間」這個性質來簡化實作，讀者可以自行研究。

```cpp=
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

const int MAX_N = 200005;

class Segtree 
{
private:
    struct node 
    {
        int mx, lazy;
    } seg[MAX_N << 3];
    int n;
    void up(int rt) 
    {
        seg[rt].mx = max(seg[rt << 1].mx, seg[rt << 1 | 1].mx);
    }
    void give_tag(int rt, int v)
    {
        seg[rt].mx += v;
        seg[rt].lazy += v;
    }
    void down(int rt)
    {
        give_tag(rt << 1, seg[rt].lazy);
        give_tag(rt << 1 | 1, seg[rt].lazy);
        seg[rt].lazy = 0;
    }
    void build(int l, int r, int rt) 
    {
        seg[rt].mx = seg[rt].lazy = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
    }
    void modify(int L, int R, int l, int r, int rt, int v)
    {
        if (L <= l && R >= r) return give_tag(rt, v);
        down(rt);
        int mid = (l + r) >> 1;
        if (L <= mid) modify(L, R, l, mid, rt << 1, v);
        if (R > mid) modify(L, R, mid + 1, r, rt << 1 | 1, v);
        up(rt);
    }
public:
    void init(int _n)
    {
        n = _n;
        build(1, n, 1);
    }
    void modify(int l, int r, int v)
    {
        if (l <= r)
            modify(l, r, 1, n, 1, v);
    }
    int get_max()
    {
        return seg[1].mx;
    }
} segtree;

int arr[MAX_N], brr[MAX_N], type[MAX_N];
pair<int, int> itv[MAX_N]; // [l, r)
vector<int> addition[MAX_N * 2], deletion[MAX_N * 2];

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, P;
    cin >> n >> P;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> brr[i];
    }

    int type2_cnt = 0;
    vector<int> vals;
    vals.push_back(0), vals.push_back(P);
    for (int i = 1; i <= n; i++)
    {
        if (brr[i] > arr[i]) 
        {
            itv[i] = make_pair(P - brr[i], P + arr[i] - brr[i] + 1);
            type[i] = 2;
            type2_cnt += 1;
        }
        else
        {
            itv[i] = make_pair(arr[i] - brr[i] + 1, P - brr[i]);
            type[i] = 1;
        }
        vals.push_back(itv[i].first);
        vals.push_back(itv[i].second);
    }
    sort(vals.begin(), vals.end()), vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    segtree.init(vals.size());
    for (int i = 1; i <= n; i++)
    {
        itv[i].first = upper_bound(vals.begin(), vals.end(), itv[i].first) - vals.begin();
        itv[i].second = upper_bound(vals.begin(), vals.end(), itv[i].second) - vals.begin();
        addition[itv[i].first].push_back(i);
        deletion[itv[i].second].push_back(i);
        if (type[i] == 1)
            segtree.modify(itv[i].first, itv[i].second - 1, 1);
    }

    int ans = 0, cnt = 0;
    for (int i = 1; i < int(vals.size()); i++)
    {
        for (int j : addition[i])
        {
            if (type[j] == 1)
                cnt += 1;
            segtree.modify(itv[j].first, itv[j].second - 1, -1);
        }
        for (int j : deletion[i])
        {
            if (type[j] == 1)
                cnt -= 1;
            segtree.modify(itv[j].first, itv[j].second - 1, 1);
        }
        ans = max(ans, cnt + segtree.get_max() + type2_cnt); 
    }

    cout << ans << "\n";
}
```
