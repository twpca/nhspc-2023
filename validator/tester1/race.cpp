#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>

int subtask(int argc, char **argv)
{
   for (int i = 0; i + 1 < argc; i++) 
   {
      if (!strcmp(argv[i], "--testcase"))
      {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

constexpr int MIN_N = 1;
constexpr int MAX_N[] = {200'000, 100, 100, 5000, 200'000, 200'000};
constexpr int MIN_P = 1;
constexpr int MAX_P[] = {1'000'000'000, 100, 10'000, 1'000'000'000, 1'000'000'000, 1'000'000'000};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readChar(' ');
    int P = inf.readInt(MIN_P, MAX_P[s], "P");
    inf.readChar('\n');
    std::vector<int> a(n);
    for (int i = 1; i <= n; i++)
    {
        a[i - 1] = inf.readInt(0, P - 1, "a_" + std::to_string(i));
        if (i == n) inf.readChar('\n');
        else inf.readChar(' ');
    }
    for (int i = 1; i <= n; i++)
    {
        int b = inf.readInt(0, P - 1, "a_" + std::to_string(i));
        if (i == n) inf.readChar('\n');
        else inf.readChar(' ');
        if (s == 4) ensuref(b <= a[i - 1], "b_%d > a_%d in subtask 4", i, i);
    }
    inf.readEof();
    return 0;
}
