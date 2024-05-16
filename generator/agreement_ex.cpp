#include <cstdio>
#include <cstring>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "testlib.h"

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

/* 
a: conn by vertex
b: conn by edge
p: conn by new vertex
*/
void random(int argc, char* argv[]) // k n min_part deg a b p realk
{
    int k = atoi(argv[0]);
    int n = atoi(argv[1]);
    int min_part = atoi(argv[2]);
    int deg = atoi(argv[3]);
    int a = atoi(argv[4]);
    int b = atoi(argv[5]);
    int p = atoi(argv[6]);
    int realk = atoi(argv[7]);
    auto leafs = partition(realk + 1, n, min_part);
    std::vector<std::vector<std::pair<int, int>>> trees;
    std::vector<std::pair<int, int>> T1, T2;

    int internal = n + 1, base = 1;

    auto construct = [&](int sz)
    {
        std::vector<std::pair<int, int>> res;
        std::vector<int> que(sz);
        std::iota(que.begin(), que.end(), base);
        while (int(que.size()) > 1)
        {
            if (int(que.size()) == 2)
            {
                res.emplace_back(que[0], que[1]);
                que.clear();
            }
            else
            {
                shuffle(que.begin(), que.end());
                int num = rnd.next(2, std::min((int)que.size(), deg));
                int r = internal++;
                while (num--)
                {
                    res.emplace_back(que.back(), r);
                    que.pop_back();
                }
                que.push_back(r);
            }
        }
        return res;
    };

    for (int lv : leafs)
    {
        trees.push_back(construct(lv));
        base += lv;
    }

    auto connect_node = [&](auto &tree, auto &cur) 
    {
        std::vector<int> ele;
        for (auto &[u, v] : tree)
        {
            if (u > n)
                ele.push_back(u);
            if (v > n)
                ele.push_back(v);
        }
        std::sort(ele.begin(), ele.end()), ele.resize(std::unique(ele.begin(), ele.end()) - ele.begin());
        if (ele.empty() || rnd.next(1, a + b) > a)
        {
            int nxt = rnd.next(0, int(tree.size()) - 1);
            auto [u, v] = tree[nxt];
            tree.erase(tree.begin() + nxt);
            int r = cur++;
            tree.emplace_back(u, r);
            tree.emplace_back(v, r);
            return r;
        }
        else 
        {
            return ele[rnd.next(0, int(ele.size()) - 1)];
        }
    };

    auto construct_tree = [&]()
    {
        auto cur_trees = trees;
        int cur = internal;
        while (int(cur_trees.size()) > 2 && rnd.next(1, 100) <= p)
        {
            int r = cur++;
            auto tree1 = cur_trees.back();
            cur_trees.pop_back();
            auto tree2 = cur_trees.back();
            cur_trees.pop_back();
            auto tree3 = cur_trees.back();
            cur_trees.pop_back();
            int u = connect_node(tree1, cur);
            int v = connect_node(tree2, cur);
            int w = connect_node(tree3, cur);
            tree1.insert(tree1.end(), tree2.begin(), tree2.end());
            tree1.insert(tree1.end(), tree3.begin(), tree3.end());
            tree1.emplace_back(r, u);
            tree1.emplace_back(r, v);
            tree1.emplace_back(r, w);
            cur_trees.push_back(tree1);
        }
        while (int(cur_trees.size()) > 1)
        {
            auto tree1 = cur_trees.back();
            cur_trees.pop_back();
            auto tree2 = cur_trees.back();
            cur_trees.pop_back();
            int u = connect_node(tree1, cur);
            int v = connect_node(tree2, cur);
            tree1.insert(tree1.end(), tree2.begin(), tree2.end());
            tree1.emplace_back(u, v);
            cur_trees.push_back(tree1);
        }
        return cur_trees[0];
    };


    T1 = construct_tree();
    T2 = construct_tree();
  
    shuffle(T1.begin(), T1.end());
    shuffle(T2.begin(), T2.end());
    
    printf("%d %d %d %d\n", n, int(T1.size()) + 1 - n, int(T2.size()) + 1 - n, k);
    for (auto &T : {T1, T2})
    {
        int m = int(T.size()) + 1 - n;
        std::vector<int> idx(m);
        std::iota(idx.begin(), idx.end(), n + 1);
        shuffle(idx.begin(), idx.end());
        for (auto [u, v] : T)
        {
            if (u >= n + 1) u = idx[u - (n + 1)];
            if (v >= n + 1) v = idx[v - (n + 1)];
            if (rnd.next(0, 1))
                std::swap(u, v);
            printf("%d %d\n", u, v);
        }
    }
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
    return 0;
}
