CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -D CMS -D TESTSYS
CHECKER_LIST = diff aisimulation 

all: $(CHECKER_LIST)

clean:
	rm -f $(CHECKER_LIST)

diff: diff.cpp
	$(CC) diff.cpp $(CCARGS) -o diff

aisimulation: aisimulation.cpp
	$(CC) aisimulation.cpp $(CCARGS) -o aisimulation
