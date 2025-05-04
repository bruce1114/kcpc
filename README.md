# **Source code for "Scaling Up k-Clique Percolation Community Detection"**
This repository contains a reference implementation of algorithms for KCPC mining in large-scale graphs, including algorithms used in experiments (QKC, KCL-MCL, KCL-QKC, Add-edge, Del-edge, Add-vertex, Del-vertex).

## **Environment Setup** ##
All algorithms are implemented with C++11. You may download the repository and enter the main folder manually.

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

## **Add-edge** ##
Add-edge can be compiled and run as follows:

```
g++ kcpc_inc.cpp -o kcpc_inc -std=c++11
./kcpc_inc ../smalldatasets/linux 3 10 100 0 \* program, dataset, k, l, number of edges to be added, output label *\
degeneracy: 23
list and connect time: 1291
group num: 5136
overlap nodes: 4526 out of 30825
partial degeneracy: 22
big color: 12
kclique time: 833
clique num: 111071
all time: 2217
kcpc num: 514
clique num: 111115 fake clique num: 8 kcpc num: 514
ave time: 0.39
```

The second-to-last line outputs the number of maximal cliques after all edges have been added, the number of invalidated maximal cliques, and the number of KCPCs. The last line reports the average time (in milliseconds) taken to add each edge.

Del-edge, Add-vertex, Del-vertex can be compiled and run in similar way.