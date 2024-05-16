#include <cstdio>
#include <cstring>
#include <vector>
#include <numeric>
#include "testlib.h"

#define register_generator(name) if (gname == #name) return name(argc - 2, argv + 2), 0

void gen(int argc, char* argv[]) // t nl nr
{
    int t = atoi(argv[0]);
    long long int nl = atoll(argv[1]);
    long long int nr = atoll(argv[2]);
    printf("%d\n", t);
    for (int tc = 1; tc <= t; tc++)
    {
        printf("%lld\n", rnd.next(nl, nr));
    }
}

void range(int argc, char* argv[]) // nl nr
{
    registerGen(argc, argv, 1);
    long long int nl = atoll(argv[0]);
    long long int nr = atoll(argv[1]);
    std::vector<long long int> numbers(nr - nl + 1);
    std::iota(numbers.begin(), numbers.end(), nl); 
    shuffle(numbers.begin(), numbers.end());
    printf("%lld\n", nr - nl + 1);
    for (long long int n : numbers)
    {
        printf("%lld\n", n);
    }
}

int main(int argc, char* argv[]) 
{
    if (argc < 2)
    {
        return std::cerr << "Arguments should not be empty.\n", 1;
    }
    registerGen(argc, argv, 1);
    std::string gname(argv[1]);
    register_generator(gen);
    register_generator(range);
    return 0;
}
