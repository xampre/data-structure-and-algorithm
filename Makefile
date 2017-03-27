CC = g++
CFLAGS = -std=c++11 #-Wall

tpsort: tpsort_dfs.cc tpsort_Kahn.cc test_tpsort.cc
	$(CC) $(CFLAGS) $^

clean:
	rm -rf *.o *.out
