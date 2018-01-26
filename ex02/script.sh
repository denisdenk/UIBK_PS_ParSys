#!/bin/bash

g++ mmul_tri.cpp -o mmul -Wall -std=c++11 -DCONTIGUOUS_WITH_INDIRECTION && 

perf stat -o CI_400.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 400 &&

perf stat -o CI_300.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 300 &&

perf stat -o CI_200.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 200 &&

perf stat -o CI_100.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 100 &&

g++ mmul_tri.cpp -o mmul -Wall -std=c++11 -DCONTIGUOUS_WITH_MULTIPLICATION && 

perf stat -o CM_400.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 400 &&

perf stat -o CM_300.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 300 &&

perf stat -o CM_200.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 200 &&

perf stat -o CM_100.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 100 &&

g++ mmul_tri.cpp -o mmul -Wall -std=c++11 -DNESTED_VECTOR &&

perf stat -o ND_400.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 400 &&

perf stat -o ND_300.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 300 &&

perf stat -o ND_200.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 200 &&

perf stat -o ND_100.txt -e task-clock -e cpu-clock -e cycles -e instructions -e branches -e branch-misses -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-prefetch-misses -e L1-dcache-stores -e L1-dcache-store-misses -r 100 ./mmul 100 


