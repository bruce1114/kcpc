#ifndef CLIQUETREENODECPP
#define CLIQUETREENODECPP
#include<vector>

using namespace std;

struct cliqueTreeNode{
    vector<int> sons;
    int inNode;
    int leafMark;//-1代表不是，否则就是在clique数组中的编号
};

struct cliqueTree{
    vector<cliqueTreeNode> treeNodePool;
    int root;

    inline int getNewNode(){
        int size=treeNodePool.size();
        cliqueTreeNode newNode;
        newNode.leafMark=-1;
        treeNodePool.emplace_back(cliqueTreeNode());
        return size;
    }
};

#endif