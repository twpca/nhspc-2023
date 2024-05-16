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

int MAX_N = 100000;
const int MAX_K = 100000;
const int MAX_C = 1'000'000'000;
const int MIN_N = 1;
const int MIN_K = 1;
const int MIN_C = 1;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int task = subtask(argc, argv);

    if (task == 1) MAX_N = 500;

    int N = inf.readInt(MIN_N, MAX_N, "n");
    inf.readSpace();
    int K = inf.readInt(MIN_K, MAX_K, "k");
    inf.readChar('\n');
    ensuref(K <= N, "K<=N");

    std::set<int> st;
    for (int i=0;i<N;++i) {
        int c = inf.readInt(MIN_C, MAX_C, "c");
        st.emplace(c);

        if (i!=N-1) inf.readSpace();
        else inf.readEoln();
    }
    inf.readEof();

    if (task == 1 || task == 2) {
        ensuref(int(st.size()) == N, "subtask 1,2 all c_i should be unique");
    }
    return 0;
}
