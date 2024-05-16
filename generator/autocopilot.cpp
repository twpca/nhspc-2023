#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <numeric>
#include <cassert>
#include <queue>
#include "testlib.h"

/*
convert from Prüfer sequence
O(nlogn)
*/
std::vector<std::pair<int, int>> uniform_tree(int size) 
{
    if (size <= 0)
        __testlib_fail("uniform_tree: size must greater then 0");
    if (size == 1)
        return {};
    std::vector<std::pair<int, int>> rt;
    std::vector<std::vector<int>> G(size);
    std::vector<int> seq(size - 2), cnt(size, 0);
    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;
    std::pair<int, int> lst;

    auto add_edge = [&](int u, int v)
    {
        G[u].push_back(v);
        G[v].push_back(u);
    };

    for (int i = 0; i < size - 2; ++i) 
    {
        seq[i] = rnd.next(0, size - 1);
        ++cnt[seq[i]];
    }
    for (int i = 0; i < size; ++i)
        if (!cnt[i])
            leaves.push(i);
    for (int i : seq) 
    {
        add_edge(leaves.top(), i);
        leaves.pop();
        if (!--cnt[i])
            leaves.push(i);
    }
    lst.first = leaves.top();
    leaves.pop();
    lst.second = leaves.top();
    add_edge(lst.first, lst.second);

    auto dfs = [&](auto _dfs, int u, int f) -> void
    {
        if (u != f)
            rt.emplace_back(f, u);
        for (int i : G[u])
            if (i != f)
                _dfs(_dfs, i, u);
    };
    dfs(dfs, 0, 0);

    return rt;
}

/*
shuffle the nodes and connect one from prefix for each node, for each node:
type0: no restriction
type1: connect with rnd.next(std::max(0, i - dis), i - 1)
type2: connect with rnd.next(0, std::min(dis - 1, i - 1))
Note that when type not equal to 1 and 2, it is regraded as 0
O(n)
*/
std::vector<std::pair<int, int>> custom_tree(int size, int type, int dis = 1) 
{
    if (size <= 0)
        __testlib_fail("custom_tree: size must greater then 0");
    if ((type == 1 || type == 2) && dis <= 0)
        __testlib_fail("custom_tree: dis must greater then 0 when type is 1 or 2");
    if (size == 1)
        return {};
    std::vector<std::pair<int, int>> rt;
    for (int i = 1; i < size; ++i)
        if (type == 1)
            rt.push_back(std::make_pair(rnd.next(std::max(0, i - dis), i - 1), i));
        else if (type == 2)
            rt.push_back(std::make_pair(rnd.next(0, std::min(dis - 1, i - 1)), i));
        else
            rt.push_back(std::make_pair(rnd.next(0, i - 1), i));
    return rt;
}

/* Returns random permutation of the given size (values are between `first` and `first`+size-1)*/
template<typename T, typename E>
std::vector<E> perm(T size, E first) {
    if (size < 0)
        __testlib_fail("random_t::perm(T size, E first = 0): size must non-negative");
    else if (size == 0)
        return std::vector<E>();
    std::vector<E> p(size);
    E current = first;
    for (T i = 0; i < size; i++)
        p[i] = current++;
    if (size > 1)
        for (T i = 1; i < size; i++)
            std::swap(p[i], p[rnd.next(i + 1)]);
    return p;
}

/* Returns random permutation of the given size (values are between 0 and size-1)*/
template<typename T>
std::vector<T> perm(T size) {
    return perm(size, T(0));
}

/* Returns `size` unordered (unsorted) distinct numbers between `from` and `to`. */
template<typename T>
std::vector<T> distinct(int size, T from, T to) {
    std::vector<T> result;
    if (size == 0)
        return result;

    if (from > to)
        __testlib_fail("random_t::distinct expected from <= to");

    if (size < 0)
        __testlib_fail("random_t::distinct expected size >= 0");

    uint64_t n = to - from + 1;
    if (uint64_t(size) > n)
        __testlib_fail("random_t::distinct expected size <= to - from + 1");

    double expected = 0.0;
    for (int i = 1; i <= size; i++)
        expected += double(n) / double(n - i + 1);

    if (expected < double(n)) {
        std::set<T> vals;
        while (int(vals.size()) < size) {
            T x = T(rnd.next(from, to));
            if (vals.insert(x).second)
                result.push_back(x);
        }
    } else {
        if (n > 1000000000)
            __testlib_fail("random_t::distinct here expected to - from + 1 <= 1000000000");
        std::vector<T> p(perm(int(n), from));
        result.insert(result.end(), p.begin(), p.begin() + size);
    }

    return result;
}

/* Returns `size` unordered (unsorted) distinct numbers between `0` and `upper`-1. */
template<typename T>
std::vector<T> distinct(int size, T upper) {
    if (size < 0)
        __testlib_fail("random_t::distinct expected size >= 0");
    if (size == 0)
        return std::vector<T>();

    if (upper <= 0)
        __testlib_fail("random_t::distinct expected upper > 0");
    if (size > upper)
        __testlib_fail("random_t::distinct expected size <= upper");

    return distinct(size, T(0), upper - 1);
}

/* Returns random (unsorted) partition which is a representation of sum as a sum of integers not less than min_part. */
template<typename T>
std::vector<T> partition(int size, T sum, T min_part) {
    if (size < 0)
        __testlib_fail("random_t::partition: size < 0");
    if (size == 0 && sum != 0)
        __testlib_fail("random_t::partition: size == 0 && sum != 0");
    if (min_part * size > sum)
        __testlib_fail("random_t::partition: min_part * size > sum");
    if (size == 0 && sum == 0)
        return std::vector<T>();

    T sum_ = sum;
    sum -= min_part * size;

    std::vector<T> septums(size);
    std::vector<T> d = distinct(size - 1, T(1), T(sum + size - 1));
    for (int i = 0; i + 1 < size; i++)
        septums[i + 1] = d[i];
    std::sort(septums.begin(), septums.end());

    std::vector<T> result(size);
    for (int i = 0; i + 1 < size; i++)
        result[i] = septums[i + 1] - septums[i] - 1;
    result[size - 1] = sum + size - 1 - septums.back();
    for (std::size_t i = 0; i < result.size(); i++)
        result[i] += min_part;

    T result_sum = 0;
    for (std::size_t i = 0; i < result.size(); i++)
        result_sum += result[i];
    if (result_sum != sum_)
        __testlib_fail("random_t::partition: partition sum is expected to be the given sum");

    if (*std::min_element(result.begin(), result.end()) < min_part)
        __testlib_fail("random_t::partition: partition min is expected to be no less than the given min_part");

    if (int(result.size()) != size || result.size() != (size_t) size)
        __testlib_fail("random_t::partition: partition size is expected to be equal to the given size");

    return result;
}

void random(int argc, char* argv[]) // n m 
{
    int n = atoi(argv[0]);
    int m = atoi(argv[1]);
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            edges.emplace_back(i, j);
    shuffle(edges.begin(), edges.end());
    while (int(edges.size()) > m)
        edges.pop_back();

    printf("%d %d\n", n, int(edges.size()));
    for (auto [u, v] : edges)
        printf("%d %d\n", u, v);
    printf("%d %d\n", rnd.next(1, n), rnd.next(1, n));
}

void random_dag(int argc, char* argv[]) // n m 
{
    int n = atoi(argv[0]);
    int m = atoi(argv[1]);
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            edges.emplace_back(i, j);
    shuffle(edges.begin(), edges.end());
    while (int(edges.size()) > m)
        edges.pop_back();
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 1);
    shuffle(idx.begin(), idx.end());
    
    printf("%d %d\n", n, int(edges.size()));
    for (auto [u, v] : edges)
        printf("%d %d\n", idx[u], idx[v]);
    printf("%d %d\n", rnd.next(1, n), rnd.next(1, n));
}

void random_tree(int argc, char* argv[]) // n type dis root
{
    int n = atoi(argv[0]);
    int type = atoi(argv[1]);
    int dis = atoi(argv[2]);
    int root = atoi(argv[3]);
    std::vector<std::pair<int, int>> edges;
    if (type == -1) edges = uniform_tree(n);
    else edges = custom_tree(n, type, dis);

    shuffle(edges.begin(), edges.end());

    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 1);
    shuffle(idx.begin(), idx.end());
    
    printf("%d %d\n", n, n - 1);
    for (auto [u, v] : edges)
        printf("%d %d\n", idx[u], idx[v]);
    int s = root ? idx[0] : rnd.next(1, n);
    printf("%d %d\n", s, rnd.next(1, n));
}

/*
p: optimal strategy is spending coin
q: optimal strategy is random walk
mx: max ans
m: number of edges
*/
void construct(int argc, char *argv[]) // p q mx m output pmin_part qsz qmin_part loop
{
    int p = atoi(argv[0]);
    int q = atoi(argv[1]);
    int mx = atoi(argv[2]);
    int m = atoi(argv[3]);
    int output = atoi(argv[4]);
    int pmin_part = atoi(argv[5]);
    int qsz = atoi(argv[6]);
    int qmin_part = atoi(argv[7]);
    int loop = atoi(argv[8]); // 0: all ok,  1: no self loop, 2: dag
    int n = p + q + 2;
    std::vector<std::pair<int, int>> edges, addition;
    int t = -1;
    // s = 0, inf = n - 1
    auto coin = partition(mx, p, pmin_part);
    auto rwalk = partition(qsz, q, qmin_part);
    std::vector<int> rwalk_app(mx + 1);
    for (int i = 0; i < qsz; i++)
        rwalk_app[i] = 1;
    shuffle(rwalk_app.begin(), rwalk_app.end());

    int rpt = 0, pl = 1, ql = p + 1;
    std::vector<int> cur;
    for (int i = 0; i <= mx; i++)
    {
        std::vector<int> nxt;
        int npl = pl, nql = ql;
        if (i > 0) npl += coin[i - 1];
        if (rwalk_app[i]) nql += rwalk[rpt];
       
        if (i > 0)
        {
            for (int j = 0; j < coin[i - 1]; j++)
            {
                int u = pl + j;
                // must have an edge to cur
                int idx = rnd.next(0, int(cur.size()) - 1);
                edges.emplace_back(u, cur[idx]);
                for (int k : cur)
                    if (k != cur[idx])
                        addition.emplace_back(u, k);

                // must have an edge to [npl, p] \cup [nql, n - 1]
                if (loop < 2) 
                {
                    std::vector<std::pair<int, int>> ele;
                    for (int k = npl; k <= p; k++)
                        ele.emplace_back(u, k);
                    for (int k = nql; k < n; k++)
                        ele.emplace_back(u, k);
                    idx = rnd.next(0, int(ele.size()) - 1);
                    edges.push_back(ele[idx]);
                    ele.erase(ele.begin() + idx);
                    addition.insert(addition.end(), ele.begin(), ele.end());
                }
                else 
                {
                    edges.emplace_back(u, n - 1); 
                }
                nxt.push_back(u);
            }
        }
        else
            nxt.push_back(0);

        // addition edges among nxt
        for (int j : nxt)
            for (int k : nxt)
                addition.emplace_back(j, k);

        // random walk
        if (rwalk_app[i])
        {
            for (int j = 0; j < rwalk[rpt]; j++)
            {
                int u = ql + j;
                int idx = rnd.next(0, int(nxt.size()) - 1);
                edges.emplace_back(u, nxt[idx]);
                nxt.push_back(u);
                for (int k : nxt)
                    if (k != nxt[idx])
                    {
                        addition.emplace_back(u, k);
                        if (u != k)
                            addition.emplace_back(k, u);
                    }
            }
            rpt++;
        }

        pl = npl, ql = nql;

        cur.swap(nxt);

        if (output == i)
            t = cur[rnd.next(0, int(cur.size()) - 1)];
    }

    assert(t != -1);

    if (m > int(edges.size()))
    {
        m -= edges.size();
        
        {
            auto tmp = addition;
            addition.clear();
            for (auto [u, v] : tmp)
            {
                int flag = 1;
                if (loop == 1 && u == v) flag = 0;
                if (loop == 2 && u <= v) flag = 0;
                if (flag)
                    addition.emplace_back(u, v);
            }
        }

        shuffle(addition.begin(), addition.end());
        addition.resize(std::min(m, int(addition.size())));
        edges.insert(edges.end(), addition.begin(), addition.end());
    }

    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 1);
    shuffle(idx.begin(), idx.end());
    shuffle(edges.begin(), edges.end());
    printf("%d %d\n", n, int(edges.size()));
    for (auto [u, v] : edges)
        printf("%d %d\n", idx[u], idx[v]);
    printf("%d %d\n", idx[t], idx[0]);
}

#define register_generator(name) if (gname == #name) return name(argc - 2, argv + 2), 0

int main(int argc, char* argv[]) 
{
    if (argc < 2)
    {
        return std::cerr << "Arguments should not be empty.\n", 1;
    }
    registerGen(argc, argv, 1);
    std::string gname(argv[1]);
    register_generator(random);
    register_generator(construct);
    register_generator(random_dag);
    register_generator(random_tree);
    return 0;
}
