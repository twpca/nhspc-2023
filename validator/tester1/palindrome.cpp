#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>

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

constexpr int MIN_T = 1;
constexpr int MAX_T = 10000;
constexpr long long int MIN_N = 1;
constexpr long long int MAX_N[] = {1'000'000'000'000'000, 30, 1'000, 1'000'000, 1'000'000'000'000'000};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int t = inf.readInt(MIN_T, MAX_T, "t");
    inf.readChar('\n');
    std::set<long long int> visit;
    for (int i = 1; i <= t; i++)
    {
        long long int n = inf.readLong(MIN_N, MAX_N[s], "n_" + std::to_string(i));
        visit.insert(n);
        inf.readChar('\n');
    }
    if (s == 1) ensuref(int(visit.size()) == t, "numbers in subtask 1 should be distinct");
    inf.readEof();
    return 0;
}
