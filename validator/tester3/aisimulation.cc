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

int MAX_N = 100;
const int MAX_K = 10;
const int MAX_T = 10;
const int MIN_N = 1;
const int MIN_K = 2;
const int MIN_T = 2;
int min_one = 0;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int task = subtask(argc, argv);

    if (task == 1 || task == 2) MAX_N = 5;
    if (task == 1 ) min_one = 4;

    int N = inf.readInt(MIN_N, MAX_N, "n");
    inf.readSpace();
    int K = inf.readInt(MIN_K, MAX_K, "k");
    inf.readSpace();
    int T = inf.readInt(MIN_T, MAX_T, "t");
    inf.readChar('\n');
    ensuref(T < K, "T< K");

    for (int i=0;i<N;++i) {
        auto bin = inf.readString();

        ensuref(int(bin.size()) == K, "string size should be K");
        for (char c: bin) ensuref((c=='0')||(c=='1'), "shoule be binary string");

        int one = count(bin.begin(), bin.end(), '1');
        ensuref(one >= min_one, "need more 1 in binary string");
    }
    inf.readEof();
    return 0;
}