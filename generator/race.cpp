#include <cstdio>
#include <cstring>
#include <vector>
#include <numeric>
#include "testlib.h"

int get_type(int a, int b, int c)
{
    int r = rnd.next(0, a + b + c - 1);
    if (r < a) return 0;
    if (r < a + b) return 1;
    return 2;
}

void random(int argc, char* argv[]) // n P al ar bl br aleb blea
{
    int n = atoi(argv[0]);
    int P = atoi(argv[1]);
    int al = atoi(argv[2]);
    int ar = atoi(argv[3]);
    int bl = atoi(argv[4]);
    int br = atoi(argv[5]);
    int aleb = atoi(argv[6]);
    int blea = atoi(argv[7]);

    std::vector<int> b(n);

    printf("%d %d\n", n, P);
    for (int i = 0; i < n; i++)
    {
        int a = rnd.next(al, ar);
        b[i] = rnd.next(bl, br);
        int t = get_type(aleb, blea, 100 - aleb - blea);
        if (t == 0 && a > b[i]) std::swap(a, b[i]);
        if (t == 1 && a < b[i]) std::swap(a, b[i]);
        printf("%d%c", a, " \n"[i + 1 == n]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d%c", b[i], " \n"[i + 1 == n]);
    }
}

void distance(int argc, char *argv[]) { // n P al ar bl br aleb blea
    int n = atoi(argv[0]);
    int P = atoi(argv[1]);
    int al = atoi(argv[2]);
    int ar = atoi(argv[3]);
    int dl = atoi(argv[4]);
    int dr = atoi(argv[5]);
    int aleb = atoi(argv[6]);
    int blea = atoi(argv[7]);

    std::vector<int> b(n);
    
    printf("%d %d\n", n, P);
    for (int i = 0; i < n; i++)
    {
        int a = rnd.next(al, ar);
        b[i] = (a + P + rnd.next(dl, dr)) % P;
        int t = get_type(aleb, blea, 100 - aleb - blea);
        if (t == 0 && a > b[i]) std::swap(a, b[i]);
        if (t == 1 && a < b[i]) std::swap(a, b[i]);
        printf("%d%c", a, " \n"[i + 1 == n]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d%c", b[i], " \n"[i + 1 == n]);
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
    register_generator(distance);
    return 0;
}
