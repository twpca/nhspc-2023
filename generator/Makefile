CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -march=native
GENERATOR_LIST = aisimulation.exe \
	monster \
	museum.exe \
	palindrome.exe \
	race.exe \
	autocopilot.exe \
	convexhull \
	agreement.exe \
	agreement_ex.exe

all: $(GENERATOR_LIST)

clean:
	rm -f $(GENERATOR_LIST)

%.exe: %.cpp
	$(CC) $^ $(CCARGS) -o $@

monster: monster.cc
	$(CC) monster.cc $(CCARGS) -o monster.exe

run_monster: monster
	./monster.exe

palindrome: palindrome.exe
	$(info palindrome.exe)

run_palindrome: palindrome
	./palindrome.exe range 1 30 > 1_01.in
	./palindrome.exe range 1 1000 > 2_01.in
	./palindrome.exe gen 10000 900 1000 > 2_02.in
	./palindrome.exe range 990001 1000000 > 3_01.in 
	./palindrome.exe gen 10000 1 1000000 > 3_02.in
	./palindrome.exe gen 10000 999990 1000000 > 3_03.in
	./palindrome.exe range 999999999990001 1000000000000000 > 4_01.in
	./palindrome.exe gen 10000 1 1000000000000000 a > 4_02.in
	./palindrome.exe gen 10000 1 1000000000000000 b > 4_03.in

museum: museum.exe
	$(info museum.exe)

run_museum: museum
	./museum.exe 1 5   500    2000 1 > 1_01.in
	./museum.exe 2 5   500    2000 1 > 1_02.in
	./museum.exe 3 5   500    2000 1 > 1_03.in
	./museum.exe 4 5   500    2000 1 > 1_04.in
	./museum.exe 1 50  500    2000 1 > 1_05.in
	./museum.exe 1 99  500    3000 1 > 1_06.in
	./museum.exe 1 100 500    3000 1 > 1_07.in
	./museum.exe 1 150 500    3000 1 > 1_08.in
	./museum.exe 1 250 500    3000 1 > 1_09.in
	./museum.exe 1 300 500    3000 1 > 1_10.in
	./museum.exe 1 499 500    3000 1 > 1_11.in
	./museum.exe 3 499 500    3000 1 > 1_12.in
	./museum.exe 4 499 500    3000 1 > 1_13.in
	./museum.exe 1 500   100000  1000000000 1 > 2_01.in
	./museum.exe 2 500   100000  1000000000 1 > 2_02.in
	./museum.exe 3 500   100000  1000000000 1 > 2_03.in
	./museum.exe 4 500   100000  1000000000 1 > 2_04.in
	./museum.exe 1 5000  100000  1000000000 1 > 2_05.in
	./museum.exe 1 5000  100000  1000000000 1 > 2_06.in
	./museum.exe 1 15000 100000  1000000000 1 > 2_07.in
	./museum.exe 1 25000 100000  1000000000 1 > 2_08.in
	./museum.exe 1 50000 100000  1000000000 1 > 2_09.in
	./museum.exe 1 70000 100000  1000000000 1 > 2_10.in
	./museum.exe 1 99999 100000  1000000000 1 > 2_11.in
	./museum.exe 3 99999 100000  1000000000 1 > 2_12.in
	./museum.exe 4 99999 100000  1000000000 1 > 2_13.in
	./museum.exe 1 500   100000  1000000000 0 > 3_01.in
	./museum.exe 2 500   100000  10         0 > 3_02.in
	./museum.exe 3 500   100000  10         0 > 3_03.in
	./museum.exe 4 500   100000  1000000000 0 > 3_04.in
	./museum.exe 1 5000  100000  1000000000 0 > 3_05.in
	./museum.exe 1 5000  100000  1000       0 > 3_06.in
	./museum.exe 1 15000 100000  1000000000 0 > 3_07.in
	./museum.exe 1 25000 100000  100        0 > 3_08.in
	./museum.exe 1 50000 100000  1000000000 0 > 3_09.in
	./museum.exe 1 70000 100000  1000       0 > 3_10.in
	./museum.exe 1 99999 100000  1000000000 0 > 3_11.in
	./museum.exe 3 99999 100000  1000000000 0 > 3_12.in
	./museum.exe 4 99999 100000  1000000000 0 > 3_13.in
	./museum.exe 4 3000   100000  3 0 > 3_15.in
	./museum.exe 3 3300   100000  3 0 > 3_16.in
	./museum.exe 2 3330   100000  3 0 > 3_17.in
	./museum.exe 4 4567   100000  2 0 > 3_18.in
	./museum.exe 3 5678   100000  2 0 > 3_19.in
	./museum.exe 2 2345   100000  2 0 > 3_20.in

cover: cover.exe
	$(info cover.exe)

aisimulation: aisimulation.exe
	$(info aisimulation.exe)

run_aisimulation: aisimulation
	./aisimulation.exe 1 5 10 3 > 1_01.in
	./aisimulation.exe 3 5 10 3 > 1_02.in
	./aisimulation.exe 1 5 10 9 > 1_03.in
	./aisimulation.exe 1 5 5  2 > 1_04.in
	./aisimulation.exe 1 5 5  2 > 1_05.in
	./aisimulation.exe 1 5 10 2 > 1_06.in
	./aisimulation.exe 1 5 10 2 abc > 1_07.in
	./aisimulation.exe 1 5 10 2 def > 1_08.in
	./aisimulation.exe 1 5 10 2 ghi > 1_09.in
	./aisimulation.exe 1 5 10 2 jdi > 1_10.in

	./aisimulation.exe 2 5 10 5 > 2_01.in
	./aisimulation.exe 3 5 10 3 > 2_02.in
	./aisimulation.exe 4 5 10 4 > 2_03.in
	./aisimulation.exe 2 5 3  2 > 2_04.in
	./aisimulation.exe 5 5 10 2 > 2_05.in
	./aisimulation.exe 5 5 10 2  abc > 2_06.in
	./aisimulation.exe 5 5 10 2  def > 2_07.in
	./aisimulation.exe 5 1 10 3  asd > 2_08.in
	./aisimulation.exe 8 5 10 2  asd > 2_09.in
	./aisimulation.exe 8 5 10 3  asd > 2_10.in
	./aisimulation.exe 1 5 10 2  dsd > 2_11.in
	./aisimulation.exe 1 5 10 2  fws > 2_12.in

	./aisimulation.exe 2 100 10 5 > 3_01.in
	./aisimulation.exe 3 100 10 9 > 3_02.in
	./aisimulation.exe 4 100 10 5 > 3_03.in
	./aisimulation.exe 5 100 10 2 > 3_04.in
	./aisimulation.exe 5 100 10 3 > 3_05.in
	./aisimulation.exe 5 100 10 9 > 3_06.in
	./aisimulation.exe 5 100 10 7 > 3_07.in
	./aisimulation.exe 6 100 10 6 > 3_08.in
	./aisimulation.exe 7 100 10 3 > 3_09.in
	./aisimulation.exe 8 100 10 3 > 3_10.in
	./aisimulation.exe 7 100 10 2 > 3_11.in
	./aisimulation.exe 7 100 10 2 > 3_12.in

race: race.exe
	$(info race.exe)

run_race: race
	./race.exe random 1 100 0 99 0 99 0 0 > 1_01.in
	./race.exe random 100 1 0 0 0 0 0 0 > 1_02.in
	./race.exe random 100 100 0 99 0 99 0 0 > 1_03.in
	./race.exe distance 100 100 0 99 -1 1 0 0 > 1_04.in
	./race.exe distance 100 100 90 99 -3 3 0 0 > 1_05.in
	./race.exe distance 100 100 90 99 -5 5 0 0 > 1_06.in
	./race.exe random 100 100 0 10 0 99 0 0 > 1_07.in
	./race.exe random 100 100 89 99 0 99 0 0 > 1_08.in
	./race.exe random 100 87 0 86 0 86 0 0 > 1_09.in
	./race.exe distance 100 100 97 98 2 3 0 0 tbmcvhkosn > 1_10.in
	./race.exe random 100 97 92 95 6 16 36 6 xmvdmhxatz > 1_11.in
	./race.exe random 100 10000 0 9999 0 9999 0 0 > 2_01.in
	./race.exe distance 100 10000 0 9999 -10 10 0 0 > 2_02.in
	./race.exe distance 100 10000 9900 9999 -10 10 0 0 > 2_03.in
	./race.exe distance 100 10000 9900 9999 -100 100 0 0 > 2_04.in
	./race.exe random 100 10000 0 50 0 9999 0 0 > 2_05.in
	./race.exe random 100 10000 9949 9999 0 9999 0 0 > 2_06.in
	./race.exe random 100 9876 0 9875 0 9875 0 0 > 2_07.in
	./race.exe random 94 7777 0 7776 888 1999 0 0 > 2_08.in
	./race.exe distance 100 9996 9968 9994 22 36 24 36 rsdxjbafny > 2_09.in
	./race.exe random 100 9992 9959 9985 1428 5873 67 13 daypbdfoof > 2_10.in
	./race.exe random 5000 1000000000 0 999999999 0 999999999 0 0 > 3_01.in
	./race.exe distance 5000 1000000000 0 999999999 -100 100 0 0 > 3_02.in
	./race.exe distance 5000 1000000000 999999000 999999999 -100 100 0 0 > 3_03.in
	./race.exe distance 5000 1000000000 999999000 999999999 -1000 1000 0 0 > 3_04.in
	./race.exe distance 5000 1000000000 999999000 999999999 -10000 10000 0 0 > 3_05.in
	./race.exe distance 5000 1000000000 999999000 999999999 -100000 100000 0 0 > 3_06.in
	./race.exe random 5000 1000000000 999990000 999999999 800000000 999999999 0 0 > 3_07.in
	./race.exe random 5000 1000000000 0 1515 0 999999999 0 0 > 3_08.in
	./race.exe random 5000 1000000000 999994848 999999999 0 999999999 0 0 > 3_09.in
	./race.exe random 5000 1000000000 878787878 999999999 0 999999999 0 0 > 3_10.in
	./race.exe random 5000 998244353 0 998244352 0 998244352 0 0 > 3_11.in
	./race.exe random 4747 123456789 0 100000000 23456788 123456788 0 0 > 3_12.in
	./race.exe random 5000 999999993 992849564 999969997 84478230 733507920 37 19 wjsyiuihkg > 3_13.in
	./race.exe random 5000 999999990 999131654 999551407 22173501 135588796 11 7 widxyfeqrk > 3_14.in
	./race.exe random 5000 999999996 998985458 999576226 13329370 768259846 50 48 ueewbnpvcj > 3_15.in
	./race.exe random 100000 1000000000 0 999999999 0 999999999 0 100 > 4_01.in
	./race.exe random 200000 1000000000 0 999999999 0 999999999 0 100 a > 4_02.in
	./race.exe random 200000 1000000000 0 999999999 0 999999999 0 100 b > 4_03.in
	./race.exe distance 200000 1000000000 0 999999999 -100 0 0 100 > 4_04.in
	./race.exe distance 200000 1000000000 999999000 999999999 -1000 0 0 100 > 4_05.in
	./race.exe distance 200000 1000000000 5000 999999999 -1000 0 0 100 > 4_06.in
	./race.exe random 200000 1000000000 500000000 999999999 0 500000000 0 100 > 4_07.in
	./race.exe random 200000 1000000000 999999000 999999999 0 999999000 0 100 > 4_08.in
	./race.exe random 1 1000000000 0 999999999 0 999999999 0 100 > 4_09.in
	./race.exe random 200000 1 0 0 0 0 0 0 > 4_10.in
	./race.exe random 100000 1000000000 0 999999999 0 999999999 0 0 > 5_01.in
	./race.exe random 200000 1000000000 0 999999999 0 999999999 0 a > 5_02.in
	./race.exe random 200000 1000000000 0 999999999 0 999999999 0 b > 5_03.in
	./race.exe distance 200000 1000000000 0 999999999 -10000 10000 0 0 > 5_04.in
	./race.exe distance 200000 1000000000 999990000 999999999 -10000 10000 0 0 > 5_05.in
	./race.exe distance 200000 1000000000 999980000 999999999 -100000 100000 0 0 > 5_06.in
	./race.exe random 200000 1000000000 0 6666 0 999999999 0 0 > 5_07.in
	./race.exe random 200000 1000000000 999988877 999999999 0 999999999 0 0 > 5_08.in
	./race.exe random 200000 1000000000 999123456 999999999 0 999999999 0 0 > 5_09.in
	./race.exe random 200000 998244853 0 998244852 0 998244852 0 0 > 5_10.in
	./race.exe random 200000 1000000000 996703466 999769807 322671729 616172564 8 28 szbgdwvxcu > 5_11.in
	./race.exe random 200000 999999995 996621891 999120753 82900427 433946093 32 15 uvuddeuunc > 5_12.in
	./race.exe random 200000 999999996 996144286 999761039 229270269 471862638 5 47 panufajrjg > 5_13.in

convexhull: convexhull.cc
	$(CC) convexhull.cc $(CCARGS) -o convexhull.exe

run_convexhull: convexhull
	./convexhull.exe

autocopilot: autocopilot.exe
	$(info autocopilot.exe)

run_autocopilot: autocopilot
	./autocopilot.exe random_tree 2 -1 0 0 c > 1_01.in
	./autocopilot.exe random_tree 2999 -1 0 1 > 1_02.in
	./autocopilot.exe random_tree 3000 -1 0 0 > 1_03.in
	./autocopilot.exe random_tree 3000 -1 0 1 > 1_04.in
	./autocopilot.exe random_tree 3000 0 0 1 > 1_05.in
	./autocopilot.exe random_tree 3000 1 1 1 > 1_06.in
	./autocopilot.exe random_tree 3000 1 2 1 > 1_07.in
	./autocopilot.exe random_tree 3000 2 1 1 > 1_08.in
	./autocopilot.exe random_tree 3000 2 2 1 > 1_09.in
	./autocopilot.exe random_tree 3000 2 10 1 > 1_10.in
	./autocopilot.exe construct 1500 1498 150 30000 138 2 20 1 2 > 2_04.in
	./autocopilot.exe construct 2998 0 2998 30000 2998 1 0 0 2 > 2_05.in
	./autocopilot.exe construct 2998 0 1500 30000 1369 1 0 0 2 > 2_06.in
	./autocopilot.exe construct 486 1498 486 30000 410 1 100 1 2 > 2_07.in
	./autocopilot.exe construct 333 2665 200 30000 0 1 135 2 2 > 2_08.in
	./autocopilot.exe construct 87 2911 42 30000 23 1 42 3 2 > 2_09.in
	./autocopilot.exe construct 36 62 20 1000 20 1 6 1 0 > 3_05.in
	./autocopilot.exe construct 98 0 98 1000 98 1 0 0 0 > 3_06.in
	./autocopilot.exe construct 49 49 32 1000 2 1 20 1 0 > 3_07.in
	./autocopilot.exe construct 20 78 13 1000 8 1 10 1 0 > 3_08.in
	./autocopilot.exe construct 70 28 16 1000 16 2 3 1 1 > 3_09.in
	./autocopilot.exe construct 23 75 4 1000 3 1 4 1 1 > 3_10.in
	./autocopilot.exe construct 19 79 19 1000 6 1 11 1 1 ampbxyxufy > 3_11.in
	./autocopilot.exe construct 63 35 59 1000 50 1 19 1 1 afglmzlvep > 3_12.in
	./autocopilot.exe construct 19 79 13 1000 13 1 9 1 1 sindpthuly > 3_13.in
	./autocopilot.exe construct 1436 1552 220 30000 215 2 200 1 0 > 4_05.in
	./autocopilot.exe construct 2998 0 2998 30000 2997 1 0 0 0 > 4_06.in
	./autocopilot.exe construct 2998 0 1234 30000 1114 1 0 0 1 > 4_07.in
	./autocopilot.exe construct 800 2198 100 30000 99 3 100 2 1 > 4_08.in
	./autocopilot.exe construct 3 2995 3 30000 3 1 3 1 1 > 4_09.in
	./autocopilot.exe construct 2665 333 2188 30000 2187 1 1 1 0 > 4_10.in
	./autocopilot.exe construct 2534 464 2533 30000 2531 1 10 1 0 > 4_11.in
	./autocopilot.exe construct 4 2994 3 30000 0 1 3 1 1 > 4_12.in
	./autocopilot.exe construct 5 2993 3 30000 2 1 3 1 1 > 4_13.in
	./autocopilot.exe construct 459 2539 361 30000 25 1 303 1 1 polksvlfjf > 4_14.in
	./autocopilot.exe construct 2343 655 1975 30000 1441 1 307 1 1 gillxjynwl > 4_15.in
	./autocopilot.exe construct 750 2248 119 30000 112 1 65 1 1 ycwslafoeg > 4_16.in

agreement_ex: agreement_ex.exe
	$(info agreement_ex.exe)

agreement: agreement.cc
	$(CC) agreement.cc $(CCARGS) -o agreement.exe

run_agreement: agreement agreement_ex
	./agreement.exe
	./agreement_ex.exe random 1 199 3 5 1 1 70 1 > 2_20.in
	./agreement_ex.exe random 1 4 2 4 98 14 0 1 sozvmtwtta > 2_21.in
	./agreement_ex.exe random 1 13 1 3 61 83 0 1 fejcjjwwpj > 2_22.in
	./agreement_ex.exe random 1 17 1 3 72 61 0 1 pgeezmkekm > 2_23.in
	./agreement_ex.exe random 2 12 3 4 1 1 50 2 > 3_20.in
	./agreement_ex.exe random 2 16 3 4 1 1 70 2 > 3_21.in
	./agreement_ex.exe random 2 17 3 4 1 1 70 2 > 3_22.in
	./agreement_ex.exe random 2 18 3 4 1 1 80 2 > 3_23.in
	./agreement_ex.exe random 2 18 3 4 1 1 90 2 > 3_24.in
	./agreement_ex.exe random 2 19 3 4 1 1 80 2 > 3_25.in
	./agreement_ex.exe random 2 18 3 5 1 1 50 1 > 3_26.in
	./agreement_ex.exe random 2 18 3 5 1 1 50 0 > 3_27.in
	./agreement_ex.exe random 2 19 3 5 1 1 50 3 > 3_28.in
	./agreement_ex.exe random 2 19 3 5 1 1 60 3 > 3_29.in
	./agreement_ex.exe random 2 190 3 4 1 1 80 2 > 4_20.in
	./agreement_ex.exe random 2 190 3 4 1 1 60 2 > 4_21.in
	./agreement_ex.exe random 2 189 3 4 1 1 60 2 > 4_22.in
	./agreement_ex.exe random 2 189 3 4 1 2 70 2 > 4_23.in
	./agreement_ex.exe random 2 180 3 4 1 2 80 2 > 4_24.in
	./agreement_ex.exe random 2 165 3 4 10 3 30 2 > 4_25.in
	./agreement_ex.exe random 2 165 3 4 1 10 50 1 > 4_26.in
	./agreement_ex.exe random 2 165 3 4 10 1 0 0 > 4_27.in
	./agreement_ex.exe random 2 186 3 5 1 1 50 2 > 4_28.in
	./agreement_ex.exe random 2 184 3 5 1 1 50 3 > 4_29.in
	./agreement_ex.exe random 2 199 3 5 1 1 70 3 > 4_30.in
