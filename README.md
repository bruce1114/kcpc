# **Source code for "Large-scale k Clique Percolation Community Detection"**
This repository contains a reference implementation of algorithms for KCPC mining in large-scale graphs, including all the algorithms used in experiments (Detect, KCL, QKC, KCL-MCL and KCL-QKC).

## **Environment Setup** ##
All algorithms are implemented with C++11. You may download the repository and enter the main folder manually.
## **Detect** ##
Detect is the baseline method, you can compile and run it as follows:
```
cd kcpc
g++ kcpc.cpp -o detect -std=c++11
./detect ../smalldatasets/linux 4 0 \* program, dataset, k, output label *\
list clique time: 451
kcpc time: 10698 
clique num: 36182
kcpc num: 412    
all time: 11148
```
If you want to output all the KCPCs, you can run Detect as follows:
```
./detect ../smalldatasets/linux 10 1
list clique time: 338
kcpc time: 0
clique num: 15
kcpc num: 1
all time: 339
kcpc-------:
3848 1101 1134 73 3362 3221 875 914 874 876
4982 1101 73 914 3221 875 1134 876 3362 874
4520 1101 914 3362 1134 875 876 3221 73 874
3221 1134 1101 875 876 3362 874 73 914 3288
3221 1134 1101 875 876 3362 874 73 914 4688
3221 1134 1101 875 876 3362 874 73 914 3887
3221 1134 1101 875 876 3362 874 73 914 3921
3221 1134 1101 875 876 3362 874 73 914 4529
3221 1134 1101 875 876 3362 874 73 914 4594
3481 876 3221 1134 874 875 3362 1101 914 4982
3481 876 3221 1134 874 875 3362 1101 914 4520
3481 876 3221 1134 874 875 3362 1101 914 3288
3481 876 3221 1134 874 875 3362 1101 914 4688
3481 876 3221 1134 874 875 3362 1101 914 4529
3481 876 3221 1134 874 875 3362 1101 914 4594
```
In this case, only 1 KCPC can be found.
## **KCL** ##

KCL can be compiled and run as follows:
```
g++ kcpc_kclique.cpp -o kcl -std=c++11
./kcl ../smalldatasets/linux 4 0 \* program, dataset, k, output label *\
big color: 12
all time: 1610
kclique num: 68492
kcpc num: 412
```
## **QKC** ##
QKC can be compiled and run as follows:

```
g++ kcpc_new.cpp -o qkc -std=c++11
./qkc ../smalldatasets/linux 4 0 0 \* program, dataset, k, l, output label *\
degeneracy: 23
list and connect time: 686
final overlap nodes: 4190
group num: 8603
final kcpc time: 4185
clique num: 36182
all time: 4877
kcpc num: 412
```
## **KCL-MCL** ##
KCL-MCL is compiled by kcpc_kclique.cpp with "#define mcliquefirst" at the top of kcpc_kclique.cpp:

```
g++ kcpc_kclique.cpp -o kclmcl -std=c++11
./kclmcl ../smalldatasets/linux 4 0 \* program, dataset, k, output label *\
mclique num: 36182
overlap nodes: 5970 out of 30838
partial degeneracy: 23
big color: 12
kclique time: 1016
all time: 1597
kcpc num: 412
```
## **KCL-QKC** ##
KCL-QKC can be compiled and run as follows:

```
g++ kcpc_combine.cpp -o kclqkc -std=c++11
./kclqkc ../smalldatasets/linux 4 0 0 \* program, dataset, k, l, output label *\
degeneracy: 23
list and connect time: 692
group num: 8729
overlap nodes: 4190 out of 30838
partial degeneracy: 23
big color: 11
kclique time: 680
clique num: 36182
all time: 1440
kcpc num: 412
```