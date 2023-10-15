#ifndef GRAPHCPP
#define GRAPHCPP

#include<string>
#include<iostream>
#include<vector>
#include"utils.cpp"
#include<unordered_map>
#include<unordered_set>
#include"cliqueTreeNode.cpp"
#include"unionfind.cpp"
#include<algorithm>
#include<sys/time.h>
using namespace std;

// #define nopivot
// #define bkbar
// #define keeporder

class Graph{
public:
    vector<vector<int>> adjList;
    vector<int> fullNodeslist;
    vector<bool> visGroup;
    vector<int> visGroups;

    //for connect maximal clique
    int maximumClique;

    void readGraph(string filename);
    void reduceGraph(int percent);
    void readGraphE(string filename,int percent);

    void listMaximalCliques(vector<vector<int>>& cliques,int kval);
    void listMaximalCliquesRegular(vector<vector<int>>& cliques);
    void listMaximalCliquesRegularDegeneracy(vector<vector<int>>& cliques);

    void listMaximalCliqueNoPivot(vector<vector<int> >& cliques);
    void bkNoPivot(vector<int>& PX,vector<int>& IPX,int xbegin,int pbegin,int pend,vector<int>& R,vector<vector<int> >& cliques);
    int getDegeneracyOrder(vector<int>& order,vector<vector<int> >& later);
    int getDegeneracyOrder(vector<int>& order,vector<int>& coreNumber);
    int getDegeneracyOrder(vector<int>& order,vector<int>& coreNumber,vector<vector<int> >& later);
    int getDegeneracyOrder(vector<int>& nodeslist,vector<int>& order,vector<vector<int> >& later,vector<int>& IPX,int pr);
    void bkPivot(int kval,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,int xl,int pl,int pr,vector<int>& R,vector<vector<int>>& cliques);
    // void bkPivot(vector<int>& P,vector<int>& IP,vector<int>& X,vector<int>& IX,int candIndex,int xIndex,vector<int>& R,vector<vector<int>>& cliques);
    void bkPivotRegular(unordered_set<int> cand,vector<int> curclique,unordered_set<int> X,vector<vector<int>>& holdcliques);
    // void exchange(vector<int>& arr,int aIndex,int bIndex,vector<int>& arrIndex,int de);

    void buildCliqueGraph(vector<vector<int>>& clique2node,vector<vector<int>>& node2clique);
    void reportByte();
    bool isTrees();
    bool dfs(int from,int u,vector<bool>& vis);

    void buildGraphViaEdges(vector<pair<int,int> >& edges);

    void listConnectMaximalCliques(int kval,int nopivotRatio,int nopivotPSize,bool savePivot,vector<vector<int>>& cliques,unf& fans);
    int bkConnect(bool needPivot,int nopivotPSize,bool savePivot,bool connectDirect,bool subClique,cliqueTree& tree,unf& f,unf& fans,int kval,vector<int>& orderIndex,vector<int>& firstLayerSons,vector<int>& xTreeNodesStack,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,vector<vector<int> >& later,int xl,int pl,int pr,vector<int>& R,vector<vector<int>>& cliques);
    void connectCliques(cliqueTree& tree,unf& f,unf& fans,vector<int>& orderIndex,vector<int>& firstLayerSons,vector<int>& xTreeNodesStack,vector<int>& PX,vector<int>& IPX,int xl,int pl,int pr,vector<vector<int> >& later,vector<vector<int> >& tempAdjList,vector<int>& R);
    inline int getAnyCliqueId(cliqueTree& tree, unordered_set<int>& theParts,unordered_set<int>& RParts, int startTreeNode);
    void testGroupOverlap(int kval,vector<vector<int> >& cliques,unf& fans);
    bool checkCommonGroup(vector<int>& Pmcliques,int pmr,unf& fans);

    void listConnectMcliquesOverlap(int kval,int nopivotPSize,unf& fans,vector<vector<int> >& cliques);
    void bkConnectOverlap(bool needPivot,int nopivotPSize,bool subClique,unf& fans,int kval,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,int xl,int pl,int pr,vector<int>& Pmclique,vector<int>& IPmclique,int pmr,vector<vector<int> >& node2mclique,vector<int>& R);

    void listConnectCliques(int kval,vector<vector<int> >& cliques,unf& fans);
    void kcliqueConnect(unf& fans,int kval,vector<vector<vector<int> > >& former,vector<vector<int> >& PPos,vector<int>& PX,vector<int>& IPX,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,int pxr,vector<int>& R,vector<vector<int>>& cliques,unordered_map<clique,int,hashClique>& mapclique);
    int kcliquelist(int kval,vector<vector<int> >& cliques);
    void listkclique(int kval,int& cliqueNum,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,vector<int>& R,vector<vector<int>>& cliques);


    void kcpc_combine_temp(int kval,int nopivotPSize,int degeneracySplit,char splitType,int minvade,vector<vector<int> >& cliques,unf& fans);
    void kcpc_combine_temp_nox(int kval,int nopivotPSize,int degeneracyPercent,vector<vector<int> >& cliques,unf& fans);
    void listConnectMcliquesPartial(int kval,int nopivotPSize,vector<int>& nodeslist,vector<int>& PX,vector<int>& IPX,int pr,vector<vector<int>>& cliques,unf& fans);
    void listConnectKcliquesPartial(int kval,vector<int>& nodeslist,vector<int>& PX,vector<int>& IPX,int pr,vector<vector<int> >& cliques,vector<vector<int> >& node2clique,unf& fans);
    void listConnectKcliquesPartialNox(int kval,vector<int>& nodeslist,vector<int>& PX,vector<int>& IPX,int pr,vector<vector<int> >& cliques,vector<vector<int> >& node2clique,unf& fans);
    void kcliqueConnectWithMclique(unf& fans,int kval,vector<vector<vector<int> > >& former,vector<vector<int> >& PPos,vector<int>& PX,vector<int>& IPX,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,int pxr,vector<int>& Pmcliques,vector<int>& IPmcliques,int pmr,vector<int>& R,vector<vector<int>>& cliques,vector<vector<int> >& node2clique,unordered_map<clique,int,hashClique>& mapclique);
    void kcliqueConnectWithMcliqueNox(unf& fans,int kval,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,vector<int>& Pmcliques,vector<int>& IPmcliques,int pmr,vector<int>& R,vector<vector<int> >& node2clique);
    // void kcliqueConnectWithMcliqueGroupNox(unf& fans,int kval,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,vector<int>& Pmcliques,vector<int>& IPmcliques,int pmr,vector<int>& R,vector<vector<int> >& node2clique);
    void finalMclique(vector<int>& nodeslist,vector<vector<int> >& cliques,int mcliquer,int kval,unf& fans);
    
    void kcpc_combine(int kval,int nopivotPSize,int degeneracySplit,vector<vector<int> >& cliques,unf& fans);
    int kcliquelist_combine(int kval,vector<int>& order,vector<int>& coreNumber,int degeneracy,int split,int degeneracySplit,vector<vector<int> >& cliques,vector<vector<int> >& later,vector<vector<int> >& tempColorAdjList);

    //just for test
    void listMcliquesPrintTree();
    void bkPivotPrintTree(int kval,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,int xl,int pl,int pr,vector<int>& R,vector<vector<int>>& cliques,int& treeId);

    #ifdef couttree
    int overallTreeid;
    #endif

    #ifdef counttree
    long long treenodecnt;
    #endif

};

void Graph::readGraphE(string filename,int percent){
    vector<vector<int> > holdLines;
    bool res=readFile(filename,holdLines);
    if(!res) exit(0);

    int neededges=holdLines.size()*percent/100;
    for(int i=0;i<neededges;++i){
        int randpos=rand()%(holdLines.size()-i)+i;
        // int temp=allnodes[i];
        vector<int> temp=holdLines[i];
        holdLines[i]=holdLines[randpos];
        holdLines[randpos]=temp;
    }

    holdLines.resize(neededges);

    int bigval=0;
    for(int i=0;i<holdLines.size();++i){
        for(int j=0;j<holdLines[i].size();++j){
            if(bigval<holdLines[i][j]) bigval=holdLines[i][j];
        }
    }

    adjList.resize(bigval+1);

    unordered_map<int,unordered_set<int>> tmpAdjMatrix;
    for(int i=0;i<holdLines.size();++i){
        int a=holdLines[i][0];
        int b=holdLines[i][1];

        if(tmpAdjMatrix.find(a)==tmpAdjMatrix.end()||tmpAdjMatrix[a].find(b)==tmpAdjMatrix[a].end()){
            tmpAdjMatrix[a].insert(b);tmpAdjMatrix[b].insert(a);
            adjList[a].push_back(b);
            adjList[b].push_back(a);
        }
    }

    for(int i=0;i<adjList.size();++i) adjList[i].shrink_to_fit();
}

void Graph::reduceGraph(int percent){
    vector<int> allnodes;
    allnodes.resize(adjList.size());
    for(int i=0;i<adjList.size();++i){
        allnodes[i]=i;
    }

    int leftnodes=adjList.size()*percent/100;
    for(int i=0;i<leftnodes;++i){
        int randpos=rand()%(adjList.size()-i)+i;
        int temp=allnodes[i];
        allnodes[i]=allnodes[randpos];
        allnodes[randpos]=temp;
    }

    vector<int> nodesinchose;
    nodesinchose.resize(adjList.size(),0);
    for(int i=0;i<leftnodes;++i){
        nodesinchose[allnodes[i]]=1;
    }

    for(int i=0;i<adjList.size();++i){
        if(nodesinchose[i]==0) adjList[i].clear();
        else{
            vector<int> realneighbor;
            for(int j=0;j<adjList[i].size();++j){
                if(nodesinchose[adjList[i][j]]==1) realneighbor.push_back(adjList[i][j]);
            }
            adjList[i]=realneighbor;
            adjList[i].shrink_to_fit();
        }
    }
}

void Graph::bkPivotPrintTree(int kval,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,int xl,int pl,int pr,vector<int>& R,vector<vector<int>>& cliques,int& treeId){
    if(pr<pl){
        if(xl>=pl&&R.size()>=kval) cliques.emplace_back(vector<int>(R.begin(),R.begin()+R.size()));

        //输出节点信息
        cout<<"nodeid: "<<treeId<<endl;
        cout<<"fromvertex: "<<R[R.size()-1]<<endl;
        cout<<"X: ";
        for(int i=xl;i<pl;++i){
            cout<<PX[i]<<",";
        }
        cout<<endl;
        cout<<"P: ";
        for(int i=pl;i<=pr;++i){
            cout<<PX[i]<<",";
        }
        cout<<endl;
        cout<<"pivot: "<<-1<<endl;
        return;
    }
    int psize=pr-pl+1;
    int xsize=pl-xl;

    if(R.size()+psize<kval) return;

    #ifndef nopivot
    //select pivot
    int big=-1;
    int pivotIndex=-1;
    int pivot=-1;
    for(int i=xl;i<=pr;++i){
        int u=PX[i];
        int j;
        for(j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
        }
        if(j>big){
            big=j;
            pivotIndex=i;
            pivot=u;
        }
    }

    //generate real candidate
    vector<int> tempCand;
    tempCand.reserve(psize);
    int neil=pr;
    for(int i=0;i<tempAdjList[pivot].size();++i){
        int v=tempAdjList[pivot][i];
        if(IPX[v]<pl||IPX[v]>pr) break;
        exchange(PX,IPX[v],neil--,IPX);
    }

    // for(int i=pl;i<=neil;++i){
    //     tempCand.push_back(PX[i]);
    // }
    tempCand.assign(PX.begin()+pl,PX.begin()+neil+1);

    #endif

    #ifdef nopivot
    //generate real candidate
    vector<int> tempCand;
    tempCand.assign(PX.begin()+pl,PX.begin()+pr+1);
    if(xl>=pl){
        bool isSubClique=true;
        for(int i=pl;i<=pr;++i){
            int j;
            int u=PX[i];
            for(j=0;j<tempAdjList[u].size();++j){
                int v=tempAdjList[u][j];
                if(IPX[v]<pl||IPX[v]>pr) break;
            }
            if(j!=psize-1){
                isSubClique=false;
                break;
            }
        }
        if(isSubClique){
            tempCand.clear();
            tempCand.push_back(PX[pl]);
        }
    }
    #endif

    //输出节点信息
    int curTreeId=treeId;
    cout<<"nodeid: "<<treeId<<endl;
    cout<<"fromvertex: "<<R[R.size()-1]<<endl;
    cout<<"X: ";
    for(int i=xl;i<pl;++i){
        cout<<PX[i]<<",";
    }
    cout<<endl;
    cout<<"P: ";
    for(int i=pl;i<=pr;++i){
        cout<<PX[i]<<",";
    }
    cout<<endl;
    cout<<"pivot: "<<pivot<<endl;

    vector<int> sonidvec;

    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        
        vector<int> tempNewX;
        tempNewX.reserve(xsize);
        //searching in X
        for(int j=xl;j<pl;++j){
            int v=PX[j];
            for(int k=0;k<tempAdjList[v].size();++k){
                int possibleU=tempAdjList[v][k];
                if(IPX[possibleU]<pl||IPX[possibleU]>pr) break;
                if(possibleU==u){
                    tempNewX.push_back(v);
                    break;
                }
            }
        }
        //no need for searching in P

        //prepare new X and P
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<tempNewX.size();++j){
            exchange(PX,IPX[tempNewX[j]],nxl--,IPX);
        }
        for(int j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
            exchange(PX,IPX[v],npr++,IPX);
        }
        nxl++;
        npr--;

        //shrink tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int numNeighborInNewP=0;
            for(int k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl||IPX[nv]>pr) break;
                if(IPX[nv]<=npr){
                    exchange(tempAdjList[v],k,numNeighborInNewP++);
                }
            }
        }

        R.push_back(u);
        sonidvec.push_back(treeId+1);
        bkPivotPrintTree(kval,PX,IPX,tempAdjList,nxl,pl,npr,R,cliques,++treeId);
        R.pop_back();
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
        
        //update tempAdjList
        for(int j=xl;j<=pr;++j){
            int v=PX[j];
            int uindex=-1;
            int k;
            for(k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl-1||IPX[nv]>pr) break;
                if(nv==u) uindex=k;
            }
            if(uindex==-1) continue;
            exchange(tempAdjList[v],uindex,k-1);
        }
    }

    //recover X
    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        exchange(PX,IPX[u],--pl,IPX);
    }

    //输出子节点
    cout<<"curTreeId: "<<curTreeId<<" sons: ";
    for(int i=0;i<sonidvec.size();++i){
        cout<<sonidvec[i]<<",";
    }
    cout<<endl;
}

void Graph::listMcliquesPrintTree(){
    vector<vector<int> > cliques;//temp

    int adjListSize=adjList.size();

    vector<vector<int> > tempAdjList;
    vector<int> PX,IPX,R;
    PX.resize(adjListSize);
    IPX.resize(adjListSize);
    R.reserve(adjListSize);

    //initialize PX and IPX
    for(int i=0;i<adjListSize;++i){
        PX[i]=IPX[i]=i;
    }

    vector<int> order;
    vector<vector<int> > later;
    int degenaracy=getDegeneracyOrder(order,later);

    #ifdef overallexample6
    order={0,16,15,13,14,12,11,10,1,8,7,2,4,5,9,6,3};
    vector<int> temppos;
    temppos.resize(17,-1);
    for(int i=0;i<order.size();++i) temppos[order[i]]=i;
    later=vector<vector<int> >();
    later.resize(17);
    for(int i=0;i<adjListSize;++i){
        for(int j=0;j<adjList[i].size();++j){
            int u=i,v=adjList[i][j];
            if(temppos[u]<temppos[v]) later[u].push_back(v);
        }
    }
    #endif

    // cerr<<"degeneracy: "<<degenaracy<<endl;

    //initialize tempAdjList
    tempAdjList.resize(adjListSize);
    for(int i=0;i<adjListSize;++i) tempAdjList[i].reserve(degenaracy);

    int treeId=0;
    cout<<"nodeid: "<<treeId<<endl;
    cout<<"fromvertex: "<<-1<<endl;
    cout<<"X: ";
    cout<<endl;
    cout<<"P: ";
    for(int i=0;i<order.size();++i){
        cout<<order[i]<<",";
    }
    cout<<endl;
    cout<<"pivot: "<<-1<<endl;
    vector<int> sonidsave;

    int pl=0;

    for(int i=0;i<order.size();++i){
        int u=order[i];

        #ifdef bkbar
        if(i%(order.size()/100)==0){
            cout<<i<<endl;
            cout<<"clique num: "<<cliques.size()<<endl;
        }
        #endif

        // obtain new P and X
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]<pl) exchange(PX,IPX[v],nxl--,IPX);
            else exchange(PX,IPX[v],npr++,IPX);
        }

        
        nxl++;
        npr--;
        //obtain new tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                //nv is in new P
                if(IPX[nv]>=pl&&IPX[nv]<=npr){
                    tempAdjList[v].push_back(nv);
                    if(j>=pl){
                        tempAdjList[nv].push_back(v);
                    }
                }
            }
        }

        R.push_back(u);
        sonidsave.push_back(treeId+1);
        bkPivotPrintTree(0,PX,IPX,tempAdjList,nxl,pl,npr,R,cliques,++treeId);
        R.pop_back();

        //clear tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            tempAdjList[v].clear();
        }
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}

    }

    //输出子节点
    cout<<"curTreeId: "<<0<<" sons: ";
    for(int i=0;i<sonidsave.size();++i){
        cout<<sonidsave[i]<<",";
    }
    cout<<endl;
}

bool Graph::checkCommonGroup(vector<int>& Pmcliques,int pmr,unf& fans){
    for(int i=0;i<=pmr;++i){
        int c=Pmcliques[i];
        int father=fans.find(c);
        if(visGroup[father]==false){
            visGroup[father]=true;
            visGroups.push_back(father);
        }
    }

    for(int i=0;i<visGroups.size();++i){
        visGroup[visGroups[i]]=false;
    }
    int num=visGroups.size();
    visGroups.clear();

    return num>1;
}

void Graph::bkConnectOverlap(bool needPivot,int nopivotPSize,bool subClique,unf& fans,int kval,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,int xl,int pl,int pr,vector<int>& Pmclique,vector<int>& IPmclique,int pmr,vector<vector<int> >& node2mclique,vector<int>& R){

    if(R.size()==kval-1){
        for(int i=1;i<=pmr;++i){
            fans.merge(Pmclique[i],Pmclique[0]);
        }
        return;
    }

    if(pr<pl){
        // if(xl>=pl&&R.size()>=kval){
        //     cliques.emplace_back(vector<int>(R.begin(),R.begin()+R.size()));
        //     int theNode=tree.getNewNode();
        //     tree.treeNodePool[theNode].leafMark=cliques.size()-1;
        //     tree.treeNodePool[theNode].inNode=R[R.size()-1];
        //     return theNode;
        // }
        // if(xl<pl-1&&R.size()>=kval-1){//需要链接一下clique
        //     //扩展一下fans
        //     fans.updateSize(cliques.size());
        //     connectCliques(tree,f,fans,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,xl,pl,pr,later,tempAdjList,R);
        // }
        return;
    }
    int psize=pr-pl+1;
    int xsize=pl-xl;

    if(R.size()+psize<kval-1) return;

    int originalPl=pl;
    vector<int> tempCand;

    if(subClique){
        tempCand.push_back(PX[pl]);
    }else if(needPivot){
        //select pivot
        int big=-1;
        int pivotIndex=-1;
        int pivot=-1;
        bool isSubClique=true;//检查是不是仅仅只是一个子clique
        for(int i=xl;i<=pr;++i){
            int u=PX[i];
            int j;
            for(j=0;j<tempAdjList[u].size();++j){
                int v=tempAdjList[u][j];
                if(IPX[v]<pl||IPX[v]>pr) break;
            }
            if(j!=psize-1){
                isSubClique=false;
            }
            if(j>big){
                big=j;
                pivotIndex=i;
                pivot=u;
            }
        }

        if(xsize>0) isSubClique=false;//不考虑有x的情况

        //generate real candidate
        tempCand.reserve(psize);
        int neil=pr;
        for(int i=0;i<tempAdjList[pivot].size();++i){
            int v=tempAdjList[pivot][i];
            if(IPX[v]<pl||IPX[v]>pr) break;
            exchange(PX,IPX[v],neil--,IPX);
        }

        // for(int i=pl;i<=neil;++i){
        //     tempCand.push_back(PX[i]);
        // }

        if(isSubClique==true){
            subClique=true;
        }

        tempCand.assign(PX.begin()+pl,PX.begin()+neil+1);
    }else{
        //generate real candidate
        tempCand.assign(PX.begin()+pl,PX.begin()+pr+1);
        // if(savePivot==true) tobeSave=pr+1-pl;
        if(xl>=pl){
            bool isSubClique=true;
            for(int i=pl;i<=pr;++i){
                int j;
                int u=PX[i];
                for(j=0;j<tempAdjList[u].size();++j){
                    int v=tempAdjList[u][j];
                    if(IPX[v]<pl||IPX[v]>pr) break;
                }
                if(j!=psize-1){
                    isSubClique=false;
                    break;
                }
            }
            if(isSubClique){
                tempCand.clear();
                tempCand.push_back(PX[pl]);
                subClique=true;
            }
        }
    }

    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        
        vector<int> tempNewX;
        tempNewX.reserve(xsize);
        //searching in X
        for(int j=xl;j<pl;++j){
            int v=PX[j];
            for(int k=0;k<tempAdjList[v].size();++k){
                int possibleU=tempAdjList[v][k];
                if(IPX[possibleU]<pl||IPX[possibleU]>pr) break;
                if(possibleU==u){
                    tempNewX.push_back(v);
                    break;
                }
            }
        }
        //no need for searching in P

        //prepare new X and P
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<tempNewX.size();++j){
            exchange(PX,IPX[tempNewX[j]],nxl--,IPX);
        }
        for(int j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
            exchange(PX,IPX[v],npr++,IPX);
        }
        nxl++;
        npr--;

        //shrink tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int numNeighborInNewP=0;
            for(int k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl||IPX[nv]>pr) break;
                if(IPX[nv]<=npr){
                    exchange(tempAdjList[v],k,numNeighborInNewP++);
                }
            }
        }

        //get mclique
        int npmr=0;
        // for(int j=0;j<node2mclique[u].size();++j){
        //     int c=node2mclique[u][j];
        //     if(IPmclique[c]<=pmr) exchange(Pmclique,IPmclique[c],npmr++,IPmclique);
        //     else break;
        // }
        npmr--;

        //shrink node2clique
        // for(int j=pl;j<=npr;++j){
        //     int v=PX[j];
        //     int tempnr=0;
        //     for(int k=0;k<node2mclique[v].size();++k){
        //         int c=node2mclique[v][k];
        //         if(IPmclique[c]>pmr) break;
        //         if(IPmclique[c]<=npmr){
        //             exchange(node2mclique[v],k,tempnr++);
        //         }
        //     }
        // }

        R.push_back(u);
        // bkPivot(PX,IPX,tempAdjList,nxl,pl,npr,R,cliques);
        bkConnectOverlap(needPivot&&(npr-pl+1)>nopivotPSize,nopivotPSize,subClique,fans,kval,PX,IPX,tempAdjList,nxl,pl,npr,Pmclique,IPmclique,npmr,node2mclique,R);
        R.pop_back();
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
        
        //update tempAdjList
        for(int j=xl;j<=pr;++j){
            int v=PX[j];
            int uindex=-1;
            int k;
            for(k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl-1||IPX[nv]>pr) break;
                if(nv==u) uindex=k;
            }
            if(uindex==-1) continue;
            exchange(tempAdjList[v],uindex,k-1);
        }
    }

    //recover X
    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        exchange(PX,IPX[u],--pl,IPX);
    }

    // if(R.size()>=kval-1){
    //     //update size of fans
    //     fans.updateSize(cliques.size());
    //     //link cliques
    //     connectCliques(tree,f,fans,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,xl,originalPl,pr,later,tempAdjList,R);
    // }
}

void Graph::listConnectMcliquesOverlap(int kval,int nopivotPSize,unf& fans,vector<vector<int> >& cliques){
    int adjlistSize=adjList.size();
    

    unordered_map<int,vector<int> > cliqueGroup;
    
    for(int i=0;i<fans.fa.size();++i){
        int father=fans.find(i);
        cliqueGroup[father].push_back(i);
    }

    vector<vector<int> > results;
    unordered_map<int,vector<int> >::iterator it=cliqueGroup.begin();
    while(it!=cliqueGroup.end()){
        results.push_back(it->second);
        it++;
    }
    vector<int> nodesoverlap;
    nodesoverlap.resize(adjlistSize,0);
    for(int i=0;i<results.size();++i){

        unordered_set<int> tset;
        for(int j=0;j<results[i].size();++j){
            int c=results[i][j];
            for(int k=0;k<cliques[c].size();++k){
                int u=cliques[c][k];
                tset.insert(u);
            }
        }
        unordered_set<int>::iterator it=tset.begin();
        while(it!=tset.end()){
            nodesoverlap[*it]++;
            it++;
        }
    }
    vector<int> nodeslist;
    for(int i=0;i<adjlistSize;++i){
        if(nodesoverlap[i]>1){
            nodeslist.push_back(i);
        }
    }

    int nodeslistSize=nodeslist.size();
    cerr<<"overlap nodes: "<<nodeslistSize<<" out of "<<adjlistSize<<endl;

    vector<vector<int> > node2mclique;
    node2mclique.resize(adjlistSize);
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2mclique[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }

    vector<vector<int> > tempAdjList;
    vector<int> PX,IPX,Pmcliques,IPmcliques,R;
    Pmcliques.resize(fans.fa.size());
    IPmcliques.resize(fans.fa.size());
    PX.resize(adjlistSize);
    IPX.resize(adjlistSize);

    //initialize PX and IPX
    for(int i=0;i<adjlistSize;++i){
        PX[i]=IPX[i]=i;
    }
    for(int i=0;i<fans.fa.size();++i){
        Pmcliques[i]=IPmcliques[i];
    }

    int pr=0;
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        exchange(PX,IPX[u],pr++,IPX);
    }
    pr--;

    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        int newr=0;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]<=pr){
                exchange(adjList[u],j,newr++);
            }
        }
    }


    vector<vector<int> > later;
    vector<int> order;
    int degenaracy=getDegeneracyOrder(nodeslist,order,later,IPX,pr);
    cerr<<"overlap degeneracy: "<<degenaracy<<endl;
    R.reserve(degenaracy+1);

    //initialize tempAdjList
    tempAdjList.resize(adjlistSize);
    for(int i=0;i<adjlistSize;++i) tempAdjList[i].reserve(degenaracy);

    int pl=0;

    for(int i=0;i<order.size();++i){
        #ifdef bar
        // if(i%(order.size()/100)==0) cout<<i<<endl;
        // if(i>=8887) cout<<i<<endl;
        #endif
        int u=order[i];

        // obtain new P and X
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]>pr) break;
            if(IPX[v]<pl) exchange(PX,IPX[v],nxl--,IPX);
            else exchange(PX,IPX[v],npr++,IPX);
        }

        nxl++;
        npr--;

        int pmr=0;
        for(int j=0;j<node2mclique[u].size();++j){
            int c=node2mclique[u][j];
            exchange(Pmcliques,IPmcliques[c],pmr++,IPmcliques);
        }
        pmr--;

        #ifdef bar
        // if(i%(order.size()/100)==0) cout<<i<<" "<<npr-pl+1<<endl;
        int totoal=0;
        #endif

        //shrink node2clique
        for(int j=pl;j<=npr;++j){
            int v=PX[j];
            int tempnr=0;

            #ifdef bar
            totoal+=node2mclique[v].size();
            #endif

            for(int k=0;k<node2mclique[v].size();++k){
                int c=node2mclique[v][k];
                if(IPmcliques[c]<=pmr){
                    exchange(node2mclique[v],k,tempnr++);
                }
            }
        }

        #ifdef bar
        if(i%(order.size()/100)==0) cout<<i<<" "<<totoal<<endl;
        // int totoal=0;
        #endif

        //obtain new tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                // #ifdef fasterconnect
                // if(IPX[nv]<nxl||IPX[nv]>npr) break;
                // #endif
                //nv is in new P
                if(IPX[nv]>=pl&&IPX[nv]<=npr){
                    tempAdjList[v].push_back(nv);
                    if(j>=pl){
                        tempAdjList[nv].push_back(v);
                    }
                }
            }
        }

        R.push_back(u);
        // bkPivot(PX,IPX,tempAdjList,nxl,pl,npr,R,cliques);
        bkConnectOverlap((npr-pl+1)>nopivotPSize,nopivotPSize,false,fans,kval,PX,IPX,tempAdjList,nxl,pl,npr,Pmcliques,IPmcliques,pmr,node2mclique,R);
        R.pop_back();

        //clear tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            tempAdjList[v].clear();
        }
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
    }
    
}

void Graph::testGroupOverlap(int kval,vector<vector<int> >& cliques,unf& fans){
    int adjlistSize=adjList.size();
    unordered_map<int,vector<int> > cliqueGroup;
    
    #ifndef nooverlap
    //根据fans获取当前的group
    for(int i=0;i<fans.fa.size();++i){
        int father=fans.find(i);
        cliqueGroup[father].push_back(i);
    }

    vector<vector<int> > results;
    unordered_map<int,vector<int> >::iterator it=cliqueGroup.begin();
    while(it!=cliqueGroup.end()){
        results.push_back(it->second);
        it++;
    }

    //找到group之间的overlap nodes
    vector<int> nodesoverlap;
    nodesoverlap.resize(adjlistSize,0);
    for(int i=0;i<results.size();++i){
        unordered_set<int> tset;
        for(int j=0;j<results[i].size();++j){
            int c=results[i][j];
            for(int k=0;k<cliques[c].size();++k){
                int u=cliques[c][k];
                tset.insert(u);
            }
        }
        unordered_set<int>::iterator it=tset.begin();
        while(it!=tset.end()){
            nodesoverlap[*it]++;
            it++;
        }
    }

    vector<int> overlapNodes;
    vector<int> IPX;
    overlapNodes.reserve(adjlistSize);
    IPX.resize(adjlistSize,1);
    for(int i=0;i<adjlistSize;++i){
        if(nodesoverlap[i]>1){
            overlapNodes.push_back(i);
            IPX[i]=0;
        }
    }

    cerr<<"overlap nodes: "<<overlapNodes.size()<<" out of "<<adjlistSize<<endl;

    if(overlapNodes.size()==0) return;



    //根据overlap nodes来削减adjlist
    vector<int> order;
    vector<vector<int> > later;
    
    for(int i=0;i<overlapNodes.size();++i){
        int u=overlapNodes[i];
        // exchange(PX,IPX[u],pr++,IPX);
        int newr=0;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]==0){
                exchange(adjList[u],j,newr++);
            }
        }
    }
    #endif

    #ifdef lesscliqueforoverlapnodes
    //根据overlap nodes来削减nodes2mclique
    vector<vector<int> > node2mclique;
    node2mclique.resize(adjList.size());
    vector<int> focusCliques;
    focusCliques.reserve(cliques.size());
    for(int i=0;i<cliques.size();++i){
        int overlapNodesNum=0;
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            if(nodesoverlap[u]>1){
                overlapNodesNum++;
            }
        }
        if(overlapNodesNum>=kval-1){
            focusCliques.push_back(i);
        }
    }

    for(int i=0;i<focusCliques.size();++i){
        int c=focusCliques[i];
        for(int j=0;j<cliques[c].size();++j){
            int u=cliques[c][j];
            if(nodesoverlap[u]>1){
                node2mclique[u].push_back(c);
            }
        }
    }
    #else
    vector<vector<int> > node2mclique;
    node2mclique.resize(adjList.size());
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2mclique[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }
    #endif

    #ifdef nooverlap
    vector<int> overlapNodes;
    vector<int> IPX;
    overlapNodes.reserve(adjlistSize);
    IPX.resize(adjlistSize,1);
    for(int i=0;i<adjlistSize;++i){
        overlapNodes.push_back(i);
        IPX[i]=0;
    }
    #endif

    // int degeneracy=getDegeneracyOrder(overlapNodes,order,later,IPX,0);
    // cerr<<"overlap degeneracy: "<<degeneracy<<endl;

    // vector<vector<int> > node2mclique;
    // node2mclique.resize(adjlistSize);
    // for(int i=0;i<cliques.size();++i){
    //     for(int j=0;j<cliques[i].size();++j){
    //         int u=cliques[i][j];
    //         node2mclique[u].push_back(i);
    //         // node2cliquesCount[u]++;
    //     }
    // }
    
    struct timeval start,end;
    gettimeofday(&start,NULL);
    listConnectKcliquesPartialNox(kval,overlapNodes,overlapNodes,IPX,0,cliques,node2mclique,fans);
    gettimeofday(&end,NULL);
    cerr<<"kclique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

}

void Graph::kcliqueConnectWithMcliqueNox(unf& fans,int kval,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,vector<int>& Pmcliques,vector<int>& IPmcliques,int pmr,vector<int>& R,vector<vector<int> >& node2clique){
    if(R.size()+theP.size()<kval-1) return;

    #ifdef couttree
    int curid=overallTreeid;
    vector<int> sonsid;
    #endif

    // if(subClique){
    //     int oldRsize=R.size();
    //     int oldPsize=theP.size();
    //     int npmr=pmr;
    //     while(oldRsize<kval-2){
    //         int u=theP[--oldPsize];
    //         // R.push_back(u);
    //         oldRsize++;

    //         //get mclique
    //         int tempr=0;
    //         for(int j=0;j<node2clique[u].size();++j){
    //             int c=node2clique[u][j];
    //             if(IPmcliques[c]<=pmr){
    //                 if(IPmcliques[c]<=npmr) exchange(Pmcliques,IPmcliques[c],tempr++,IPmcliques);
    //             }
    //             else break;
    //         }
    //         npmr=tempr-1;
    //     }
    //     theP.resize(oldPsize);
    //     for(int i=0;i<theP.size();++i){
    //         int u=theP[i];

    //         //get mclique
    //         int tempr=0;
    //         for(int j=0;j<node2clique[u].size();++j){
    //             int c=node2clique[u][j];
    //             if(IPmcliques[c]<=pmr){
    //                 if(IPmcliques[c]<=npmr) exchange(Pmcliques,IPmcliques[c],tempr++,IPmcliques);
    //             }
    //             else break;
    //         }
    //         tempr--;
    //         //connect with mcliques
    //         for(int j=1;j<=tempr;++j){
    //             fans.merge(Pmcliques[j],Pmcliques[0]);
    //         }

    //     }
    //     return;
    // }
    // #ifdef directleaf
    if(R.size()==kval-2){
        for(int i=0;i<theP.size();++i){
            int u=theP[i];

            #ifdef couttree
            ++overallTreeid;
            sonsid.push_back(overallTreeid);
            cout<<"curid: "<<overallTreeid<<" sons: "<<endl;
            #endif

            #ifdef counttree
            treenodecnt++;
            #endif

            //get mclique
            int npmr=0;
            for(int j=0;j<node2clique[u].size();++j){
                int c=node2clique[u][j];
                if(IPmcliques[c]<=pmr) exchange(Pmcliques,IPmcliques[c],npmr++,IPmcliques);
                else break;
            }
            npmr--;
            //connect with mcliques
            for(int j=1;j<=npmr;++j){
                fans.merge(Pmcliques[j],Pmcliques[0]);
            }

        }

        #ifdef couttree
        cout<<"curid: "<<curid<<" sons: ";
        for(int i=0;i<sonsid.size();++i){
            cout<<sonsid[i]<<",";
        }
        cout<<endl;
        #endif
        
        return;
    }
    // #endif

    // if(R.size()==kval-1){
    //     vector<int> cliqueIds;
    //     cliqueIds.reserve(pxr+1);
    //     clique templateclique;
    //     templateclique.theNodes=vector<int>(R.begin(),R.begin()+R.size());
    //     templateclique.selfsort();
    //     for(int i=0;i<=pxr;++i){
    //         int leftu=PX[i];
    //         clique tempClique=templateclique;
    //         // tempClique.theNodes.push_back(leftu);
    //         tempClique.addsort(leftu);

    //         // if(tempClique.theNodes[0]==leftu||tempClique.theNodes[1]==leftu||tempClique.theNodes[0]==tempClique.theNodes[1]){
    //         //     cerr<<"here"<<endl;
    //         // }

    //         int curId=-1;
    //         if(mapclique.find(tempClique)==mapclique.end()){
    //             cliques.emplace_back(tempClique.theNodes);
    //             mapclique[tempClique]=cliques.size()-1;
    //             curId=cliques.size()-1;
    //         }else{
    //             curId=mapclique[tempClique];
    //         }

    //         cliqueIds.push_back(curId);
    //     }

    //     fans.updateSize(cliques.size());
    //     for(int i=1;i<cliqueIds.size();++i){
    //         fans.merge(cliqueIds[i],cliqueIds[0]);
    //     }

    //     return;
    // }

    #ifdef pivotLike
    int big=-1;
    int bigu=-1;
    for(int i=0;i<theP.size();++i){
        int u=theP[i];
        int j;
        for(j=0;j<tempColorAdjList[u].size();++j){
            int v=tempColorAdjList[u][j];
            if(InP[v]!=R.size()+1) break;
            // newP.push_back(v);
        }
        if(big<j){
            big=j;
            bigu=u;
        }
    }

    for(int i=0;i<tempColorAdjList[bigu].size();++i){
        int v=tempColorAdjList[bigu][i];
        if(InP[v]!=R.size()+1) break;
        fullNodeslist[v]=1;
        // newP.push_back(v);
    }
    vector<int> candP;
    candP.reserve(theP.size());
    for(int i=0;i<theP.size();++i){
        int u=theP[i];
        if(fullNodeslist[u]==0) candP.push_back(u);
    }

    for(int i=0;i<tempColorAdjList[bigu].size();++i){
        int v=tempColorAdjList[bigu][i];
        if(InP[v]!=R.size()+1) break;
        fullNodeslist[v]=0;
        // newP.push_back(v);
    }
    
    #endif

    #ifndef pivotLike
    for(int i=0;i<theP.size();++i){
        int u=theP[i];
    #else
    for(int i=0;i<candP.size();++i){
        int u=candP[i];
    #endif
        if(R.size()+node2color[u]+1<kval-1) continue;

        //get mclique
        int npmr=0;
        for(int j=0;j<node2clique[u].size();++j){
            int c=node2clique[u][j];
            if(IPmcliques[c]<=pmr) exchange(Pmcliques,IPmcliques[c],npmr++,IPmcliques);
            else break;
        }
        npmr--;

        #ifdef checkcommongroup
        if(checkCommonGroup(Pmcliques,npmr,fans)==false) continue;
        #endif

        //prepare new P
        vector<int> newP;
        newP.reserve(theP.size());
        for(int j=0;j<tempColorAdjList[u].size();++j){
            int v=tempColorAdjList[u][j];
            if(InP[v]!=R.size()+1) break;
            newP.push_back(v);
        }

        if(R.size()+1+newP.size()<kval-1) continue;

        //prepare tempcoloradjlist
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+2;
        }
        int totalNeighbor=0;
        for(int j=0;j<newP.size();++j){
            int v=newP[j];
            int nr=0;
            for(int k=0;k<tempColorAdjList[v].size();++k){
                int x=tempColorAdjList[v][k];
                if(InP[x]<R.size()+1) break;

                if(InP[x]==R.size()+2){
                    exchange(tempColorAdjList[v],nr++,k);
                }
            }
            totalNeighbor+=nr;
        }

        //shrink node2clique
        for(int j=0;j<newP.size();++j){
            int v=newP[j];
            int tempnr=0;
            for(int k=0;k<node2clique[v].size();++k){
                int c=node2clique[v][k];
                if(IPmcliques[c]>pmr) break;
                if(IPmcliques[c]<=npmr){
                    exchange(node2clique[v],k,tempnr++);
                }
            }
        }

        #ifdef avoidSubClique
        if(totalNeighbor+totalNeighbor==(newP.size()*(newP.size()-1))){
            int oldRsize=R.size()+1;
            int oldPsize=newP.size();
            int nnpmr=npmr;
            while(oldRsize<kval-2){
                int v=newP[--oldPsize];
                // R.push_back(u);
                oldRsize++;

                //get mclique
                int tempr=0;
                for(int j=0;j<node2clique[v].size();++j){
                    int c=node2clique[v][j];
                    if(IPmcliques[c]<=npmr){
                        if(IPmcliques[c]<=nnpmr) exchange(Pmcliques,IPmcliques[c],tempr++,IPmcliques);
                    }
                    else break;
                }
                nnpmr=tempr-1;
            }
            newP.resize(oldPsize);
            for(int j=0;j<newP.size();++j){
                int v=newP[j];

                //get mclique
                int tempr=0;
                for(int k=0;k<node2clique[v].size();++k){
                    int c=node2clique[v][k];
                    if(IPmcliques[c]<=npmr){
                        if(IPmcliques[c]<=nnpmr) exchange(Pmcliques,IPmcliques[c],tempr++,IPmcliques);
                    }
                    else break;
                }
                tempr--;
                //connect with mcliques
                for(int k=1;k<=tempr;++k){
                    fans.merge(Pmcliques[k],Pmcliques[0]);
                }

            }

            //reset InP//可否挪到外面去？
            for(int j=0;j<newP.size();++j){
                InP[newP[j]]=R.size()+1;
            }
            continue;
        }
        #endif

        R.push_back(u);
        // if(R.size()==2&&R[0]==25640&&R[1]==123){
        //     cerr<<"here"<<endl;
        // }
        // kcliqueConnect(fans,kval,former,PPos,PX,IPX,InP,newP,node2color,tempColorAdjList,npxr,R,cliques,mapclique);
        // kcliqueConnectWithMclique(fans,kval,former,PPos,PX,IPX,InP,newP,node2color,tempColorAdjList,npxr,Pmcliques,IPmcliques,npmr,R,cliques,node2clique,mapclique);
        #ifdef couttree
        overallTreeid++;
        sonsid.push_back(overallTreeid);
        #endif

        #ifdef counttree
        treenodecnt++;
        #endif
        kcliqueConnectWithMcliqueNox(fans,kval,InP,newP,node2color,tempColorAdjList,Pmcliques,IPmcliques,npmr,R,node2clique);
        R.pop_back();

        //reset InP//可否挪到外面去？
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+1;
        }

    }

    #ifdef couttree
    cout<<"curid: "<<curid<<" sons: ";
    for(int i=0;i<sonsid.size();++i){
        cout<<sonsid[i]<<",";
    }
    cout<<endl;
    #endif
}

void Graph::listConnectKcliquesPartialNox(int kval,vector<int>& nodeslist,vector<int>& PX,vector<int>& IPX,int pr,vector<vector<int> >& cliques,vector<vector<int> >& node2clique,unf& fans){
    int nodeslistSize=nodeslist.size();
    int adjlistSize=adjList.size();

    vector<int> order;
    vector<vector<int> >later;
    int degeneracy=getDegeneracyOrder(nodeslist,order,later,IPX,pr);
    cerr<<"partial degeneracy: "<<degeneracy<<endl;

    //coloring the nodes
    vector<int> node2color;
    node2color.resize(adjlistSize,-1);

    vector<int> colorFlag;
    colorFlag.resize(degeneracy+1,-1);
    int bigColor=-1;

    for(int i=order.size()-1;i>=0;--i){
        int u=order[i];
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]>pr) break;
            if(node2color[v]!=-1){
                colorFlag[node2color[v]]=u;
            }
        }
        int j;
        for(j=0;j<degeneracy+1;++j){
            if(colorFlag[j]!=u){
                node2color[u]=j;
                if(j>bigColor) bigColor=j;
                break;
            }
        }
        if(j==degeneracy+1){
            cerr<<"no color"<<endl;
            exit(0);
        }
    }

    cerr<<"big color: "<<bigColor<<endl;

    //get DAG
    vector<vector<int> > colorLater;
    colorLater.resize(adjlistSize);
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        for(int j=0;j<later[u].size();++j){
            int v=later[u][j];
            if(node2color[u]<node2color[v]){
                colorLater[v].push_back(u);
            }else if(node2color[u]>node2color[v]){
                colorLater[u].push_back(v);
            }else{
                cerr<<"error in color"<<endl;
                exit(0);
            }
        }
    }
    int bigDegree=0;
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        if(bigDegree<colorLater[u].size()) bigDegree=colorLater[u].size();
    }

    vector<int> R,InP;
    vector<int> Pmcliques,IPmcliques;
    Pmcliques.resize(cliques.size());
    IPmcliques.resize(cliques.size());
    for(int i=0;i<cliques.size();++i){
        Pmcliques[i]=IPmcliques[i]=i;
    }
    vector<vector<int> > tempColorAdjList;
    tempColorAdjList.resize(adjlistSize);
    for(int i=0;i<nodeslistSize;++i){
        tempColorAdjList[nodeslist[i]].reserve(bigDegree);
    }
    InP.resize(adjlistSize,1);
    R.reserve(kval);
    vector<int> theP;
    theP.reserve(bigDegree);
    fullNodeslist.resize(adjlistSize,0);
    // unordered_map<clique,int,hashClique> mapclique;

    // vector<vector<vector<int> > > former;
    // vector<vector<int> > PPos;
    // former.resize(kval);
    // PPos.resize(kval);
    // for(int i=0;i<kval;++i){
    //     former[i].resize(bigDegree);
    //     PPos[i].resize(adjlistSize);
    // }

    #ifdef couttree
    overallTreeid=0;
    int curtreeid=overallTreeid;
    vector<int> sonsid;
    #endif

    #ifdef counttree
    treenodecnt=1;
    #endif

    for(int i=0;i<order.size();++i){
        int u=order[i];
        if(node2color[u]+1<kval-1){//等于kval-1也行
            continue;
        }

        int pmr=0;
        for(int j=0;j<node2clique[u].size();++j){
            int c=node2clique[u][j];
            exchange(Pmcliques,IPmcliques[c],pmr++,IPmcliques);
        }
        pmr--;

        #ifdef checkcommongroup
        if(checkCommonGroup(Pmcliques,pmr,fans)==false) continue;
        #endif

        for(int j=0;j<colorLater[u].size();++j){
            int v=colorLater[u][j];
            // if(IPX[v]>pr) break;
            // exchange(PX,pxr++,IPX[v],IPX);
            // if(node2color[v]<node2color[u]){
            InP[v]=2;
            theP.push_back(v);
            // }
        }


        // savePX.assign(PX.begin(),PX.begin()+pxr+1);

        //debug
        // int cnt=0;

        for(int j=0;j<theP.size();++j){
            int v=theP[j];
            for(int k=0;k<colorLater[v].size();++k){
                int nv=colorLater[v][k];
                if(InP[nv]==2) tempColorAdjList[v].push_back(nv);
                //debug
                // if(u==25640){
                //     if(nv==9) cnt++;
                // }
            }
        }

        #ifdef bar
        if(i%(order.size()/100)==0) cout<<i<<endl;
        // int totoal=0;
        #endif

        for(int j=0;j<theP.size();++j){
            int v=theP[j];
            int tempnr=0;

            #ifdef bar
            // totoal+=node2clique[v].size();
            #endif

            for(int k=0;k<node2clique[v].size();++k){
                int c=node2clique[v][k];
                if(IPmcliques[c]<=pmr){
                    exchange(node2clique[v],k,tempnr++);
                }
            }
        }

        #ifdef bar
        // if(i%(order.size()/100)==0) cout<<i<<" "<<totoal<<endl;
        // int totoal=0;
        #endif

        R.push_back(u);
        //debug
        // if(R[0]==25640){
        //     cerr<<"here"<<endl;
        //     cerr<<tempColorAdjList[123][0]<<" "<<tempColorAdjList[123][1]<<" "<<tempColorAdjList[123][2]<<endl;
        //     cerr<<cnt<<endl;
        // }
        // kcliqueConnect(fans,kval,former,PPos,PX,IPX,InP,theP,node2color,tempColorAdjList,pxr,R,cliques,mapclique);
        #ifdef couttree
        overallTreeid++;
        sonsid.push_back(overallTreeid);
        #endif

        #ifdef counttree
        treenodecnt++;
        #endif
        kcliqueConnectWithMcliqueNox(fans,kval,InP,theP,node2color,tempColorAdjList,Pmcliques,IPmcliques,pmr,R,node2clique);
        R.pop_back();

        //clear tempcoloradjlist
        for(int j=0;j<theP.size();++j){
            tempColorAdjList[theP[j]].clear();
        }
        // for(int j=0;j<savePX.size();++j){
        //     tempColorAdjList[savePX[j]].clear();
        // }
        for(int j=0;j<theP.size();++j){
            InP[theP[j]]=1;
        }
        theP.clear();
        
    }

    #ifdef couttree
    cout<<"curid: "<<curtreeid<<" sons: ";
    for(int i=0;i<sonsid.size();++i){
        cout<<sonsid[i]<<",";
    }
    cout<<endl;

    #endif

    #ifdef counttree
    cout<<"treenodecnt: "<<treenodecnt<<endl;
    #endif
}

void Graph::kcpc_combine_temp_nox(int kval,int nopivotPSize,int degeneracyPercent,vector<vector<int> >& cliques,unf& fans){
    struct timeval start,end;

    int nodesize=adjList.size();

    vector<int> PX,IPX,R;
    PX.resize(nodesize);
    IPX.resize(nodesize);
    R.reserve(nodesize);
    //initialize PX and IPX
    for(int i=0;i<nodesize;++i){
        PX[i]=IPX[i]=i;
    }

    vector<int> dorder,coreNumber;
    vector<int> dorderPos;
    vector<vector<int> > dlater;
    int degeneracy=getDegeneracyOrder(dorder,dlater);
    dorderPos.resize(nodesize);
    for(int i=0;i<dorder.size();++i){
        dorderPos[dorder[i]]=i;
    }

    cerr<<"degeneracy: "<<degeneracy<<endl;

    vector<int> nodes_mclique;
    nodes_mclique=PX;

    int pr=PX.size()-1;
    int split=degeneracyPercent/100.0*dorder.size();

    // for(split=dorder.size()-1;split>=0;--split){
    //     int u=dorder[split];
    //     if(splitType=='v'){
    //         if(coreNumber[u]<degeneracySplit) break;
    //     }else if(splitType=='p'){
    //         if(dorder.size()-split>percent) break;
    //     }
        
    //     // exchange(PX,IPX[u],pr++,IPX);
    //     for(int j=0;j<adjList[u].size();++j){
    //         int v=adjList[u][j];
    //         if(coreNumber[v]<degeneracySplit){
    //             int invadersize=invader_mclique.size();
    //             if(invadersize==0||invader_mclique[invadersize-1]!=u) invader_mclique.push_back(u);
    //             if(IPX[v]>=pr) exchange(PX,IPX[v],pr++,IPX);
    //         }
    //     }
    // }
    // ++split;
    
    cerr<<"mclique part node: "<<nodes_mclique.size()<<" out of "<<nodesize<<endl;

    //分割完毕，处理局部图
    // for(int i=0;i<nodes_mclique.size();++i){
    //     int u=nodes_mclique[i];
    //     int newr=0;
    //     for(int j=0;j<adjList[u].size();++j){
    //         int v=adjList[u][j];
    //         if(IPX[v]<=pr){
    //             exchange(adjList[u],j,newr++);
    //         }
    //     }
    // }
    // auto cmp=[&coreNumber](int a,int b){
    //     if(coreNumber[a]==coreNumber[b]){
    //         return a<b;
    //     }
    //     return coreNumber[a]<coreNumber[b];
    // };
    // sort(order_mclique.begin(),order_mclique.end(),cmp);
    gettimeofday(&start,NULL);
    if(nodes_mclique.size()>0) listConnectMcliquesPartial(kval,nopivotPSize,nodes_mclique,PX,IPX,pr,cliques,fans);
    gettimeofday(&end,NULL);
    cerr<<"maximal clique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    //wait
    int mcliquer=cliques.size()-1;
    vector<vector<int> > node2mclique;
    node2mclique.resize(nodesize);
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2mclique[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }

    //step2
    //处理第二个局部图
    pr=0;
    for(int i=0;i<split;++i){
        int u=dorder[i];
        exchange(PX,IPX[u],pr++,IPX);
        int newr=0;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(dorderPos[v]<split){
                exchange(adjList[u],j,newr++);
            }
        }
    }
    pr--;

    vector<int> nodes_kclique;
    nodes_kclique.assign(dorder.begin(),dorder.begin()+split);

    cerr<<"kclique split node: "<<split<<endl;
    cerr<<"kclique part node: "<<nodes_kclique.size()<<" out of "<<nodesize<<endl;

    gettimeofday(&start,NULL);
    if(nodes_kclique.size()>0) listConnectKcliquesPartialNox(kval,nodes_kclique,PX,IPX,pr,cliques,node2mclique,fans);
    gettimeofday(&end,NULL);
    cerr<<"kclique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    //final
    gettimeofday(&start,NULL);
    finalMclique(nodes_mclique,cliques,mcliquer,kval,fans);
    gettimeofday(&end,NULL);
    cerr<<"final maximal clique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

}

void Graph::finalMclique(vector<int>& nodeslist,vector<vector<int> >& cliques,int mcliquer,int kval,unf& fans){
    unordered_map<int,int> groupMap;
    vector<int> clique2group;
    vector<vector<int> > group2clique;
    clique2group.resize(mcliquer+1);

    int groupNum=0;
    for(int i=0;i<=mcliquer;++i){
        // if(fans.fa[i]==i){
        //     groupMap[i]=groupNum++;
        // }
        int father=fans.find(i);
        if(groupMap.find(father)==groupMap.end()){
            groupMap[father]=groupNum++;
        }
    }

    cerr<<"group num: "<<groupNum<<" out of "<<mcliquer+1<<endl;

    group2clique.resize(groupNum);
    for(int i=0;i<=mcliquer;++i){
        int father=fans.find(i);
        // if(groupMap.find(father)==groupMap.end()) cerr<<"here"<<endl;
        int groupId=groupMap[father];
        group2clique[groupId].push_back(i);
        clique2group[i]=groupId;
    }

    int bignode=-1;
    // for(int i=0;i<=mcliquer;++i){
    //     for(int j=0;j<cliques[i].size();++j){
    //         int u=cliques[i][j];
    //         if(bignode<u) bignode=u;
    //     }
    // }
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        if(bignode<u) bignode=u;
    }

    vector<vector<int> > node2clique;
    node2clique.resize(bignode+1);
    for(int i=0;i<groupNum;++i){
        for(int j=0;j<group2clique[i].size();++j){
            int c=group2clique[i][j];
            for(int k=0;k<cliques[c].size();++k){
                int u=cliques[c][k];
                node2clique[u].push_back(c);
            }
        }
    }

    vector<vector<int> > node2cliqueJump;
    node2cliqueJump.resize(bignode+1);
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        int next=node2clique[u].size();
        if(next==0) continue;
        node2cliqueJump[u].resize(next);
        int curGroup=clique2group[node2clique[u][next-1]];
        for(int j=node2clique[u].size()-1;j>=0;--j){
            int c=node2clique[u][j];
            if(clique2group[c]==curGroup) node2cliqueJump[u][j]=next;
            else{
                curGroup=clique2group[c];
                next=j+1;
                node2cliqueJump[u][j]=next;
            }
        }
    }


    //不考虑group顺序
    vector<int> overlap,computed;
    overlap.resize(mcliquer+1,0);
    computed.reserve(mcliquer+1);
    for(int i=0;i<=mcliquer;++i){
        int curGroup=clique2group[i];
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            for(int k=0;k<node2clique[u].size();){
                int nc=node2clique[u][k];
                if(clique2group[nc]==curGroup){
                    k=node2cliqueJump[u][k];
                }
                else if(fans.find(nc)==fans.find(i)){
                    k=node2cliqueJump[u][k];
                     
                }
                else{
                    if(overlap[nc]++ == 0){
                        computed.push_back(nc);
                    }
                    if(overlap[nc]==kval-1){
                        fans.merge(nc,i);
                        k=node2cliqueJump[u][k];
                    }else{
                        k++;
                    }
                }
            }
        }

        for(int j=0;j<computed.size();++j){
            overlap[computed[j]]=0;
        }
        computed.clear();
    }
}

void Graph::kcliqueConnectWithMclique(unf& fans,int kval,vector<vector<vector<int> > >& former,vector<vector<int> >& PPos,vector<int>& PX,vector<int>& IPX,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,int pxr,vector<int>& Pmcliques,vector<int>& IPmcliques,int pmr,vector<int>& R,vector<vector<int>>& cliques,vector<vector<int> >& node2clique,unordered_map<clique,int,hashClique>& mapclique){
    if(R.size()+theP.size()<kval-1) return;

    #ifdef fasterformer

    int layer=R.size();
    if(R.size()!=kval-1){//默认有directleaf
        for(int i=0;i<theP.size();++i){
            PPos[layer][theP[i]]=i;
            former[layer][i].clear();
        }
        for(int i=0;i<=pxr;++i){
            int u=PX[i];
            for(int j=0;j<tempColorAdjList[u].size();++j){
                int v=tempColorAdjList[u][j];
                if(InP[v]!=R.size()+1) break;
                former[layer][PPos[layer][v]].push_back(u);
            }
        }
    }
    #endif

    // #ifdef directleaf
    if(R.size()==kval-2){
        for(int i=0;i<theP.size();++i){
            int u=theP[i];
            vector<int> leftus;
            leftus.reserve(pxr+1);
            for(int j=0;j<tempColorAdjList[u].size();++j){
                int v=tempColorAdjList[u][j];
                if(InP[v]!=R.size()+1) break;
                leftus.push_back(v);
            }

            #ifdef fasterformer
            for(int j=0;j<former[layer][PPos[layer][u]].size();++j){
                leftus.push_back(former[layer][PPos[layer][u]][j]);
            }
            #else
            for(int j=0;j<=pxr;++j){
                int v=PX[j];
                if(node2color[v]<=node2color[u]) continue;
                for(int k=0;k<tempColorAdjList[v].size();++k){
                    int vv=tempColorAdjList[v][k];
                    if(InP[vv]!=R.size()+1) break;
                    if(vv==u){
                        leftus.push_back(v);
                        break;
                    }
                }
            }
            #endif

            //get mclique
            int npmr=0;
            for(int j=0;j<node2clique[u].size();++j){
                int c=node2clique[u][j];
                if(IPmcliques[c]<=pmr) exchange(Pmcliques,IPmcliques[c],npmr++,IPmcliques);
                else break;
            }
            npmr--;

            clique templateclique;
            templateclique.theNodes=vector<int>(R.begin(),R.begin()+R.size());
            templateclique.theNodes.push_back(u);
            templateclique.selfsort();
            vector<int> cliqueIds;
            cliqueIds.reserve(leftus.size());
            for(int j=0;j<leftus.size();++j){
                int v=leftus[j];
                clique tempClique=templateclique;
                tempClique.addsort(v);

                int curId=-1;
                if(mapclique.find(tempClique)==mapclique.end()){
                    cliques.emplace_back(tempClique.theNodes);
                    mapclique[tempClique]=cliques.size()-1;
                    curId=cliques.size()-1;
                }else{
                    curId=mapclique[tempClique];
                }

                cliqueIds.push_back(curId);
            }
            
            fans.updateSize(cliques.size());
            for(int j=1;j<cliqueIds.size();++j){
                fans.merge(cliqueIds[j],cliqueIds[0]);
            }
            //connect with mcliques
            for(int j=1;j<=npmr;++j){
                fans.merge(Pmcliques[j],Pmcliques[0]);
            }
            if(cliqueIds.size()>0&&npmr>=0){
                fans.merge(Pmcliques[0],cliqueIds[0]);
            }

        }
        return;
    }
    // #endif

    // if(R.size()==kval-1){
    //     vector<int> cliqueIds;
    //     cliqueIds.reserve(pxr+1);
    //     clique templateclique;
    //     templateclique.theNodes=vector<int>(R.begin(),R.begin()+R.size());
    //     templateclique.selfsort();
    //     for(int i=0;i<=pxr;++i){
    //         int leftu=PX[i];
    //         clique tempClique=templateclique;
    //         // tempClique.theNodes.push_back(leftu);
    //         tempClique.addsort(leftu);

    //         // if(tempClique.theNodes[0]==leftu||tempClique.theNodes[1]==leftu||tempClique.theNodes[0]==tempClique.theNodes[1]){
    //         //     cerr<<"here"<<endl;
    //         // }

    //         int curId=-1;
    //         if(mapclique.find(tempClique)==mapclique.end()){
    //             cliques.emplace_back(tempClique.theNodes);
    //             mapclique[tempClique]=cliques.size()-1;
    //             curId=cliques.size()-1;
    //         }else{
    //             curId=mapclique[tempClique];
    //         }

    //         cliqueIds.push_back(curId);
    //     }

    //     fans.updateSize(cliques.size());
    //     for(int i=1;i<cliqueIds.size();++i){
    //         fans.merge(cliqueIds[i],cliqueIds[0]);
    //     }

    //     return;
    // }


    for(int i=0;i<theP.size();++i){
        int u=theP[i];
        if(R.size()+node2color[u]+1<kval-1) continue;

        int npxr=0;

        //prepare new P
        vector<int> newP;
        newP.reserve(theP.size());
        for(int j=0;j<tempColorAdjList[u].size();++j){
            int v=tempColorAdjList[u][j];
            if(InP[v]!=R.size()+1) break;
            newP.push_back(v);
            exchange(PX,IPX[v],npxr++,IPX);
        }

        //prepare new X

        #ifdef fasterformer
        for(int j=0;j<former[layer][PPos[layer][u]].size();++j){
            int v=former[layer][PPos[layer][u]][j];
            exchange(PX,IPX[v],npxr++,IPX);
        }
        #else
        for(int j=0;j<=pxr;++j){
            int vu=PX[j];
            if(node2color[vu]<=node2color[u]) continue;
            for(int k=0;k<tempColorAdjList[vu].size();++k){
                int tu=tempColorAdjList[vu][k];
                if(InP[tu]!=R.size()+1) break;
                if(tu==u){
                    exchange(PX,IPX[vu],npxr++,IPX);
                    break;
                }
            }
        }
        #endif
        npxr--;

        //prepare tempcoloradjlist
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+2;
        }
        for(int j=0;j<=npxr;++j){
            int v=PX[j];
            int nr=0;
            for(int k=0;k<tempColorAdjList[v].size();++k){
                int x=tempColorAdjList[v][k];
                if(InP[x]<R.size()+1) break;

                if(InP[x]==R.size()+2){
                    exchange(tempColorAdjList[v],nr++,k);
                }
            }
        }

        //get mclique
        int npmr=0;
        for(int j=0;j<node2clique[u].size();++j){
            int c=node2clique[u][j];
            if(IPmcliques[c]<=pmr) exchange(Pmcliques,IPmcliques[c],npmr++,IPmcliques);
            else break;
        }
        npmr--;

        //shrink node2clique
        for(int j=0;j<newP.size();++j){
            int v=newP[j];
            int tempnr=0;
            for(int k=0;k<node2clique[v].size();++k){
                int c=node2clique[v][k];
                if(IPmcliques[c]>pmr) break;
                if(IPmcliques[c]<=npmr){
                    exchange(node2clique[v],k,tempnr++);
                }
            }
        }

        R.push_back(u);
        // if(R.size()==2&&R[0]==25640&&R[1]==123){
        //     cerr<<"here"<<endl;
        // }
        // kcliqueConnect(fans,kval,former,PPos,PX,IPX,InP,newP,node2color,tempColorAdjList,npxr,R,cliques,mapclique);
        kcliqueConnectWithMclique(fans,kval,former,PPos,PX,IPX,InP,newP,node2color,tempColorAdjList,npxr,Pmcliques,IPmcliques,npmr,R,cliques,node2clique,mapclique);
        R.pop_back();

        //reset InP//可否挪到外面去？
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+1;
        }

    }
}

void Graph::listConnectKcliquesPartial(int kval,vector<int>& nodeslist,vector<int>& PX,vector<int>& IPX,int pr,vector<vector<int> >& cliques,vector<vector<int> >& node2clique,unf& fans){
    int nodeslistSize=nodeslist.size();
    int adjlistSize=adjList.size();

    vector<int> order;
    vector<vector<int> >later;
    int degeneracy=getDegeneracyOrder(nodeslist,order,later,IPX,pr);

    //coloring the nodes
    vector<int> node2color;
    node2color.resize(adjlistSize,-1);

    vector<int> colorFlag;
    colorFlag.resize(degeneracy+1,-1);
    int bigColor=-1;

    for(int i=order.size()-1;i>=0;--i){
        int u=order[i];
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]>pr) break;
            if(node2color[v]!=-1){
                colorFlag[node2color[v]]=u;
            }
        }
        int j;
        for(j=0;j<degeneracy+1;++j){
            if(colorFlag[j]!=u){
                node2color[u]=j;
                if(j>bigColor) bigColor=j;
                break;
            }
        }
        if(j==degeneracy+1){
            cerr<<"no color"<<endl;
            exit(0);
        }
    }

    cerr<<"big color: "<<bigColor<<endl;

    //get DAG
    vector<vector<int> > colorLater;
    colorLater.resize(adjlistSize);
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        for(int j=0;j<later[u].size();++j){
            int v=later[u][j];
            if(node2color[u]<node2color[v]){
                colorLater[v].push_back(u);
            }else if(node2color[u]>node2color[v]){
                colorLater[u].push_back(v);
            }else{
                cerr<<"error in color"<<endl;
                exit(0);
            }
        }
    }
    int bigDegree=0;
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        if(bigDegree<colorLater[u].size()) bigDegree=colorLater[u].size();
    }

    vector<int> R,InP;
    vector<int> Pmcliques,IPmcliques;
    Pmcliques.resize(cliques.size());
    IPmcliques.resize(cliques.size());
    for(int i=0;i<cliques.size();++i){
        Pmcliques[i]=IPmcliques[i]=i;
    }
    vector<vector<int> > tempColorAdjList;
    tempColorAdjList.resize(adjlistSize);
    for(int i=0;i<nodeslistSize;++i){
        tempColorAdjList[nodeslist[i]].reserve(bigDegree);
    }
    InP.resize(adjlistSize,1);
    R.reserve(kval);
    vector<int> theP;
    theP.reserve(bigDegree);
    unordered_map<clique,int,hashClique> mapclique;

    vector<vector<vector<int> > > former;
    vector<vector<int> > PPos;
    former.resize(kval);
    PPos.resize(kval);
    for(int i=0;i<kval;++i){
        former[i].resize(bigDegree);
        PPos[i].resize(adjlistSize);
    }

    for(int i=0;i<order.size();++i){
        int u=order[i];
        if(node2color[u]+1<kval-1){//等于kval-1也行
            continue;
        }

        int pxr=0;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]>pr) break;
            exchange(PX,pxr++,IPX[v],IPX);
            if(node2color[v]<node2color[u]){
                InP[v]=2;
                theP.push_back(v);
            }
        }
        pxr--;

        int pmr=0;
        for(int j=0;j<node2clique[u].size();++j){
            int c=node2clique[u][j];
            exchange(Pmcliques,IPmcliques[c],pmr++,IPmcliques);
        }
        pmr--;

        // savePX.assign(PX.begin(),PX.begin()+pxr+1);

        //debug
        // int cnt=0;

        for(int j=0;j<=pxr;++j){
            int v=PX[j];
            for(int k=0;k<colorLater[v].size();++k){
                int nv=colorLater[v][k];
                if(InP[nv]==2) tempColorAdjList[v].push_back(nv);
                //debug
                // if(u==25640){
                //     if(nv==9) cnt++;
                // }
            }
        }

        for(int j=0;j<theP.size();++j){
            int v=theP[j];
            int tempnr=0;
            for(int k=0;k<node2clique[v].size();++k){
                int c=node2clique[v][k];
                if(IPmcliques[c]<=pmr){
                    exchange(node2clique[v],k,tempnr++);
                }
            }
        }

        R.push_back(u);
        //debug
        // if(R[0]==25640){
        //     cerr<<"here"<<endl;
        //     cerr<<tempColorAdjList[123][0]<<" "<<tempColorAdjList[123][1]<<" "<<tempColorAdjList[123][2]<<endl;
        //     cerr<<cnt<<endl;
        // }
        // kcliqueConnect(fans,kval,former,PPos,PX,IPX,InP,theP,node2color,tempColorAdjList,pxr,R,cliques,mapclique);
        kcliqueConnectWithMclique(fans,kval,former,PPos,PX,IPX,InP,theP,node2color,tempColorAdjList,pxr,Pmcliques,IPmcliques,pmr,R,cliques,node2clique,mapclique);
        R.pop_back();

        //clear tempcoloradjlist
        for(int j=0;j<=pxr;++j){
            tempColorAdjList[PX[j]].clear();
        }
        // for(int j=0;j<savePX.size();++j){
        //     tempColorAdjList[savePX[j]].clear();
        // }
        for(int j=0;j<theP.size();++j){
            InP[theP[j]]=1;
        }
        theP.clear();
        
    }

}

void Graph::listConnectMcliquesPartial(int kval,int nopivotPSize,vector<int>& nodeslist,vector<int>& PX,vector<int>& IPX,int pr,vector<vector<int>>& cliques,unf& fans){
    int nodeslistSize=nodeslist.size();
    int adjlistSize=adjList.size();
    vector<vector<int> > partialDorderList;

    cliqueTree tree;
    tree.root=tree.getNewNode();
    tree.treeNodePool[tree.root].inNode=-1;
    tree.treeNodePool[tree.root].leafMark=-1;

    vector<vector<int> > later;
    vector<int> order;
    vector<int> orderIndex;
    vector<int> R;
    int degenaracy=getDegeneracyOrder(nodeslist,order,later,IPX,pr);

    R.reserve(degenaracy);
    orderIndex.resize(adjlistSize);
    for(int i=0;i<order.size();++i){
        orderIndex[order[i]]=i;
    }

    //initialize tempAdjList
    partialDorderList.resize(adjlistSize);
    for(int i=0;i<nodeslistSize;++i){
        int u=nodeslist[i];
        partialDorderList[u].reserve(degenaracy);
    }

    int pl=0;
    vector<int> firstLayerSons,xTreeNodesStack;
    // firstLayerSons.reserve(adjListSize);
    firstLayerSons.resize(adjlistSize,-1);
    xTreeNodesStack.reserve(nodeslistSize);
    unf f;
    f.init(nodeslistSize);

    //k应大于等于3，所以第一层不需要处理
    for(int i=0;i<order.size();++i){
        int u=order[i];

        // obtain new P and X
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]>pr) break;
            if(IPX[v]<pl) exchange(PX,IPX[v],nxl--,IPX);
            else exchange(PX,IPX[v],npr++,IPX);
        }

        nxl++;
        npr--;
        //shrink later
        #ifdef fasterconnect
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int nsize=0;
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                if(IPX[nv]>=nxl&&IPX[nv]<=npr){
                    exchange(later[v],k,nsize++);
                }
            }
        }
        #endif

        //obtain new tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                #ifdef fasterconnect
                if(IPX[nv]<nxl||IPX[nv]>npr) break;
                #endif
                //nv is in new P
                if(IPX[nv]>=pl&&IPX[nv]<=npr){
                    partialDorderList[v].push_back(nv);
                    if(j>=pl){
                        partialDorderList[nv].push_back(v);
                    }
                }
            }
        }

        R.push_back(u);
        // bkPivot(PX,IPX,tempAdjList,nxl,pl,npr,R,cliques);
        int node=bkConnect((npr-pl+1)>nopivotPSize,nopivotPSize,false,false,false,tree,f,fans,kval,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,partialDorderList,later,nxl,pl,npr,R,cliques);
        R.pop_back();
        if(node!=-1){
            tree.treeNodePool[tree.root].sons.push_back(node);
            firstLayerSons[u]=tree.treeNodePool[tree.root].sons.size()-1;
        }

        //clear partialDorderList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            partialDorderList[v].clear();
        }
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
    }
}

void Graph::kcpc_combine_temp(int kval,int nopivotPSize,int degeneracySplit,char splitType,int minvade,vector<vector<int> >& cliques,unf& fans){
    struct timeval start,end;

    int nodesize=adjList.size();

    vector<int> PX,IPX,R;
    PX.resize(nodesize);
    IPX.resize(nodesize);
    R.reserve(nodesize);
    //initialize PX and IPX
    for(int i=0;i<nodesize;++i){
        PX[i]=IPX[i]=i;
    }

    vector<int> dorder,coreNumber,dorderPos;
    vector<vector<int> > dlater;
    int degeneracy=getDegeneracyOrder(dorder,coreNumber,dlater);

    cerr<<"degeneracy: "<<degeneracy<<endl;
    dorderPos.resize(nodesize);
    for(int i=0;i<dorder.size();++i) dorderPos[dorder[i]]=i;

    vector<int> nodes_mclique;
    vector<int> invader_mclique;
    invader_mclique.reserve(nodesize);

    int pr=0;
    int split;
    int percent=degeneracySplit/100.0*dorder.size();
    

    for(split=dorder.size()-1;split>=0;--split){
        int u=dorder[split];
        if(splitType=='v'){
            if(coreNumber[u]<degeneracySplit) break;
        }else if(splitType=='p'){
            if(dorder.size()-split>percent) break;
        }
    }
    ++split;

    for(int i=dorder.size()-1;i>=split;--i){
        int u=dorder[i];
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if((splitType=='v'&&coreNumber[v]<degeneracySplit)||(splitType=='p'&&dorderPos[v]<split)){
                int invadersize=invader_mclique.size();
                if(invadersize==0||invader_mclique[invadersize-1]!=u) invader_mclique.push_back(u);
                if(IPX[v]>=pr) exchange(PX,IPX[v],pr++,IPX);
            }
        }
    }

    // for(split=dorder.size()-1;split>=0;--split){
    //     int u=dorder[split];
    //     if(splitType=='v'){
    //         if(coreNumber[u]<degeneracySplit) break;
    //     }else if(splitType=='p'){
    //         if(dorder.size()-split>percent) break;
    //     }
        
    //     // exchange(PX,IPX[u],pr++,IPX);
    //     for(int j=0;j<adjList[u].size();++j){
    //         int v=adjList[u][j];
    //         if(coreNumber[v]<degeneracySplit){
    //             int invadersize=invader_mclique.size();
    //             if(invadersize==0||invader_mclique[invadersize-1]!=u) invader_mclique.push_back(u);
    //             if(IPX[v]>=pr) exchange(PX,IPX[v],pr++,IPX);
    //         }
    //     }
    // }
    // ++split;

    if(minvade==0) pr=0;
    for(int i=split;i<dorder.size();++i){
        int u=dorder[i];
        exchange(PX,IPX[u],pr++,IPX);
    }
    pr--;
    nodes_mclique.assign(PX.begin(),PX.begin()+pr+1);
    
    cerr<<"mclique split node: "<<dorder.size()-split<<endl;
    cerr<<"mclique part node: "<<nodes_mclique.size()<<" out of "<<nodesize<<endl;

    //分割完毕，处理局部图
    for(int i=0;i<nodes_mclique.size();++i){
        int u=nodes_mclique[i];
        int newr=0;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]<=pr){
                exchange(adjList[u],j,newr++);
            }
        }
    }
    // auto cmp=[&coreNumber](int a,int b){
    //     if(coreNumber[a]==coreNumber[b]){
    //         return a<b;
    //     }
    //     return coreNumber[a]<coreNumber[b];
    // };
    // sort(order_mclique.begin(),order_mclique.end(),cmp);
    gettimeofday(&start,NULL);
    if(nodes_mclique.size()>0) listConnectMcliquesPartial(kval,nopivotPSize,nodes_mclique,PX,IPX,pr,cliques,fans);
    gettimeofday(&end,NULL);
    cerr<<"maximal clique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    //wait
    int mcliquer=cliques.size()-1;
    vector<vector<int> > node2mclique;
    node2mclique.resize(nodesize);
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2mclique[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }

    //step2
    //处理第二个局部图
    pr=0;
    for(int i=0;i<split;++i){
        int u=dorder[i];
        exchange(PX,IPX[u],pr++,IPX);

    }
    if(minvade==0){
        for(int i=0;i<invader_mclique.size();++i){
            int u=invader_mclique[i];
            exchange(PX,IPX[u],pr++,IPX);
        }
    }
    pr--;

    for(int i=0;i<=pr;++i){
        int u=PX[i];
        int newr=0;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]<=pr){
                exchange(adjList[u],j,newr++);
            }
        }
    }

    vector<int> nodes_kclique;
    nodes_kclique.assign(PX.begin(),PX.begin()+pr+1);

    cerr<<"kclique split node: "<<split<<endl;
    cerr<<"kclique part node: "<<nodes_kclique.size()<<" out of "<<nodesize<<endl;

    gettimeofday(&start,NULL);
    if(nodes_kclique.size()>0) listConnectKcliquesPartial(kval,nodes_kclique,PX,IPX,pr,cliques,node2mclique,fans);
    gettimeofday(&end,NULL);
    cerr<<"kclique num: "<<cliques.size()-mcliquer-1<<endl;
    cerr<<"kclique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    //final
    gettimeofday(&start,NULL);
    if(mcliquer>=0) finalMclique(nodes_mclique,cliques,mcliquer,kval,fans);
    gettimeofday(&end,NULL);
    cerr<<"final maximal clique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

}

// int Graph::kcliquelist_combine(int kval,vector<int>& order,vector<int>& coreNumber,int degeneracy,int split,int degeneracySplit,vector<vector<int> >& cliques,vector<vector<int> >& later,vector<vector<int> >& tempColorAdjList){
//     int nodesize=adjList.size();

//     //coloring the nodes
//     vector<int> node2color;
//     node2color.resize(nodesize,-1);
//     vector<int> colorFlag;
//     colorFlag.resize(degeneracy+1,-1);
//     int bigColor=-1;

//     for(int i=split-1;i>=0;--i){
//         int u=order[i];
//         for(int j=0;j<adjList[u].size();++j){
//             int v=adjList[u][j];
//             if(coreNumber[v]>=degeneracySplit) continue;
//             if(node2color[v]!=-1){
//                 colorFlag[node2color[v]]=u;
//             }
//         }
//         int j;
//         for(j=0;j<degeneracy+1;++j){
//             if(colorFlag[j]!=u){
//                 node2color[u]=j;
//                 if(j>bigColor) bigColor=j;
//                 break;
//             }
//         }
//         if(j==degeneracy+1){
//             cerr<<"no color"<<endl;
//             exit(0);
//         }
//     }

//     cerr<<"big color: "<<bigColor<<endl;

//     //get DAG
//     vector<vector<int> > colorLater;
//     colorLater.resize(nodesize);
//     for(int i=0;i<split;++i){
//         int u=order[i];
//         for(int j=0;j<later[u].size();++j){
//             int v=later[u][j];
//             if(coreNumber[v]>=degeneracySplit) continue;
//             if(node2color[u]<node2color[v]){
//                 colorLater[v].push_back(u);
//             }else if(node2color[u]>node2color[v]){
//                 colorLater[u].push_back(v);
//             }else{
//                 cerr<<"error in color"<<endl;
//                 exit(0);
//             }
//         }
//     }
//     int bigDegree=0;
//     for(int i=0;i<split;++i){
//         int u=order[i];
//         if(bigDegree<colorLater[u].size()) bigDegree=colorLater[u].size();
//     }

//     vector<int> PX,IPX,R;
//     vector<int> InP;
//     for(int i=0;i<split;++i){
//         tempColorAdjList[order[i]].reserve(bigDegree);
//     }
//     InP.resize(nodesize,1);
//     PX.resize(nodesize);
//     IPX.resize(nodesize);
//     R.reserve(kval);
//     vector<int> theP;
//     theP.reserve(bigDegree);
//     unordered_map<clique,int,hashClique> mapclique;
//     for(int i=0;i<PX.size();++i){
//         PX[i]=i;IPX[i]=i;
//     }

//     vector<vector<vector<int> > > former;
//     vector<vector<int> > PPos;
//     former.resize(kval);
//     PPos.resize(kval);
//     for(int i=0;i<kval;++i){
//         former[i].resize(bigDegree);
//         PPos[i].resize(nodesize);
//     }

//     for(int i=0;i<split;++i){
//         int u=order[i];
//         if(node2color[u]+1<kval-1){
//             continue;
//         }

//         int pxr=0;
//         for(int j=0;j<adjList[u].size();++j){
//             int v=adjList[u][j];
//             if(coreNumber[v]>=degeneracySplit) continue;
//             exchange(PX,pxr++,IPX[v],IPX);
//             if(node2color[v]<node2color[u]){
//                 InP[v]=2;
//                 theP.push_back(v);
//             }
//         }
//         pxr--;

//         for(int j=0;j<=pxr;++j){
//             int v=PX[j];
//             for(int k=0;k<colorLater[v].size();++k){
//                 int nv=colorLater[v][k];
//                 if(InP[nv]==2) tempColorAdjList[v].push_back(nv);
//                 //debug
//                 // if(u==25640){
//                 //     if(nv==9) cnt++;
//                 // }
//             }
//         }
//     }

// }

void Graph::kcpc_combine(int kval,int nopivotPSize,int degeneracySplit,vector<vector<int> >& cliques,unf& fans){
    //get degeneracy
    int nodesize=adjList.size();

    vector<int> PX,IPX,R;
    PX.resize(nodesize);
    IPX.resize(nodesize);
    R.reserve(nodesize);
    //initialize PX and IPX
    for(int i=0;i<nodesize;++i){
        PX[i]=IPX[i]=i;
    }

    //split
    vector<int> order,coreNumber;
    vector<vector<int> > later;
    int degeneracy=getDegeneracyOrder(order,coreNumber,later);
    vector<int> neworder;
    int pr=0;
    int split;
    for(split=order.size()-1;split>=0;--split){
        int u=order[split];
        if(coreNumber[u]<degeneracySplit) break;
        exchange(PX,IPX[u],pr++,IPX);
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(coreNumber[v]<degeneracySplit&&IPX[v]>=pr){
                exchange(PX,IPX[v],pr++,IPX);
            }
        }
    }
    ++split;
    pr--;

    neworder.assign(PX.begin(),PX.begin()+pr+1);

    auto cmp=[&coreNumber](int a,int b){
        if(coreNumber[a]==coreNumber[b]){
            return a<b;
        }
        return coreNumber[a]<coreNumber[b];
    };

    sort(neworder.begin(),neworder.end(),cmp);

    cerr<<"mclique part node: "<<neworder.size()<<" out of "<<nodesize<<endl;


    cliqueTree tree;
    tree.root=tree.getNewNode();
    tree.treeNodePool[tree.root].inNode=-1;
    tree.treeNodePool[tree.root].leafMark=-1;

    vector<int> orderIndex;
    orderIndex.resize(nodesize);
    for(int i=0;i<neworder.size();++i){
        orderIndex[neworder[i]]=i;
    }

    vector<vector<int> > tempAdjList;
    //initialize tempAdjList
    tempAdjList.resize(nodesize);
    for(int i=0;i<nodesize;++i) tempAdjList[i].reserve(degeneracy);

    int pl=0;
    vector<int> firstLayerSons,xTreeNodesStack;
    firstLayerSons.resize(nodesize,0);
    xTreeNodesStack.reserve(nodesize);
    unf f;
    f.init(nodesize);

    for(int i=0;i<neworder.size();++i){
        int u=neworder[i];

        // obtain new P and X
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]<pl) exchange(PX,IPX[v],nxl--,IPX);
            else if(IPX[v]<=pr) exchange(PX,IPX[v],npr++,IPX);
        }

        nxl++;
        npr--;
        //shrink later
        #ifdef fasterconnect
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int nsize=0;
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                if(IPX[nv]>=nxl&&IPX[nv]<=npr){
                    exchange(later[v],k,nsize++);
                }
            }
        }
        #endif

        //obtain new tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                #ifdef fasterconnect
                if(IPX[nv]<nxl||IPX[nv]>npr) break;
                #endif
                //nv is in new P
                if(IPX[nv]>=pl&&IPX[nv]<=npr){
                    tempAdjList[v].push_back(nv);
                    if(j>=pl){
                        tempAdjList[nv].push_back(v);
                    }
                }
            }
        }

        R.push_back(u);
        int node=bkConnect((npr-pl+1)>nopivotPSize,nopivotPSize,false,false,false,tree,f,fans,kval,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,tempAdjList,later,nxl,pl,npr,R,cliques);
        R.pop_back();
        if(node!=-1){
            tree.treeNodePool[tree.root].sons.push_back(node);
            firstLayerSons[u]=tree.treeNodePool[tree.root].sons.size()-1;
        }

        //clear tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            tempAdjList[v].clear();
        }
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
        
    }

    //step 2
    vector<vector<int> > node2mclique;
    node2mclique.resize(nodesize);
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2mclique[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }



}

void Graph::listkclique(int kval,int& cliqueNum,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,vector<int>& R,vector<vector<int>>& cliques){
    if(R.size()+theP.size()<kval) return;
    if(R.size()==kval-2){
        for(int i=0;i<theP.size();++i){
            int u=theP[i];
            for(int j=0;j<tempColorAdjList[u].size();++j){
                int v=tempColorAdjList[u][j];
                if(InP[v]!=R.size()+1) break;
                cliqueNum++;
            }
        }
        return;
    }
    if(R.size()==kval){

        #ifdef savekclique
        cliques.emplace_back(vector<int>(R.begin(),R.begin()+R.size()));
        #endif
        cliqueNum++;
        return;
    }

    for(int i=0;i<theP.size();++i){
        int u=theP[i];
        if(R.size()+node2color[u]+1<kval) continue;


        //prepare new P
        vector<int> newP;
        newP.reserve(theP.size());
        for(int j=0;j<tempColorAdjList[u].size();++j){
            int v=tempColorAdjList[u][j];
            if(InP[v]!=R.size()+1) break;
            newP.push_back(v);
        }

        //prepare tempcoloradjlist
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+2;
        }
        for(int j=0;j<newP.size();++j){
            int v=newP[j];
            int nr=0;
            for(int k=0;k<tempColorAdjList[v].size();++k){
                int x=tempColorAdjList[v][k];
                if(InP[x]<R.size()+1) break;

                if(InP[x]==R.size()+2){
                    exchange(tempColorAdjList[v],nr++,k);
                }
            }
        }

        R.push_back(u);
        // if(R.size()==2&&R[0]==25640&&R[1]==123){
        //     cerr<<"here"<<endl;
        // }
        listkclique(kval,cliqueNum,InP,newP,node2color,tempColorAdjList,R,cliques);
        R.pop_back();

        //reset InP//可否挪到外面去？
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+1;
        }

    }
}

int Graph::kcliquelist(int kval,vector<vector<int> >& cliques){

    struct timeval start,end;

    int nodeSize=adjList.size();
    vector<int> order;
    vector<vector<int> >later;
    gettimeofday(&start,NULL);
    int degeneracy=getDegeneracyOrder(order,later);

    //coloring the nodes
    vector<int> node2color;
    node2color.resize(nodeSize,-1);

    vector<int> colorFlag;
    colorFlag.resize(degeneracy+1,-1);
    int bigColor=-1;

    for(int i=order.size()-1;i>=0;--i){
        int u=order[i];
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(node2color[v]!=-1){
                colorFlag[node2color[v]]=u;
            }
        }
        int j;
        for(j=0;j<degeneracy+1;++j){
            if(colorFlag[j]!=u){
                node2color[u]=j;
                if(j>bigColor) bigColor=j;
                break;
            }
        }
        if(j==degeneracy+1){
            cerr<<"no color"<<endl;
            exit(0);
        }
    }

    cerr<<"big color: "<<bigColor<<endl;

    //get DAG
    vector<vector<int> > colorLater;
    colorLater.resize(nodeSize);
    for(int i=0;i<later.size();++i){
        for(int j=0;j<later[i].size();++j){
            int u=i;
            int v=later[i][j];
            if(node2color[u]<node2color[v]){
                colorLater[v].push_back(u);
            }else if(node2color[u]>node2color[v]){
                colorLater[u].push_back(v);
            }else{
                cerr<<"error in color"<<endl;
                exit(0);
            }
        }
    }
    int bigDegree=0;
    for(int i=0;i<colorLater.size();++i){
        if(bigDegree<colorLater[i].size()) bigDegree=colorLater[i].size();
    }

    gettimeofday(&end,NULL);
    cerr<<"degeneracy and color time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;


    vector<int> R,InP;
    vector<vector<int> > tempColorAdjList;
    tempColorAdjList.resize(nodeSize);
    for(int i=0;i<nodeSize;++i) tempColorAdjList[i].reserve(bigDegree);
    InP.resize(nodeSize,1);
    R.reserve(kval);
    vector<int> theP;
    theP.reserve(bigDegree);

    int cliqueNum=0;

    for(int i=0;i<order.size();++i){
        int u=order[i];
        if(node2color[u]+1<kval){
            continue;
        }

        for(int j=0;j<colorLater[u].size();++j){
            int v=colorLater[u][j];
            InP[v]=2;
            theP.push_back(v);
        }

        // savePX.assign(PX.begin(),PX.begin()+pxr+1);

        //debug
        // int cnt=0;

        for(int j=0;j<theP.size();++j){
            int v=theP[j];
            for(int k=0;k<colorLater[v].size();++k){
                int nv=colorLater[v][k];
                if(InP[nv]==2) tempColorAdjList[v].push_back(nv);
                //debug
                // if(u==25640){
                //     if(nv==9) cnt++;
                // }
            }
        }

        R.push_back(u);
        //debug
        // if(R[0]==25640){
        //     cerr<<"here"<<endl;
        //     cerr<<tempColorAdjList[123][0]<<" "<<tempColorAdjList[123][1]<<" "<<tempColorAdjList[123][2]<<endl;
        //     cerr<<cnt<<endl;
        // }
        listkclique(kval,cliqueNum,InP,theP,node2color,tempColorAdjList,R,cliques);
        R.pop_back();

        //clear tempcoloradjlist
        for(int j=0;j<theP.size();++j){
            tempColorAdjList[theP[j]].clear();
        }
        // for(int j=0;j<savePX.size();++j){
        //     tempColorAdjList[savePX[j]].clear();
        // }
        for(int j=0;j<theP.size();++j){
            InP[theP[j]]=1;
        }
        theP.clear();
        
    }
    return cliqueNum;
}

void Graph::kcliqueConnect(unf& fans,int kval,vector<vector<vector<int> > >& former,vector<vector<int> >& PPos,vector<int>& PX,vector<int>& IPX,vector<int>& InP,vector<int>& theP,vector<int>& node2color,vector<vector<int> >& tempColorAdjList,int pxr,vector<int>& R,vector<vector<int>>& cliques,unordered_map<clique,int,hashClique>& mapclique){
    // 不用特地找kclique
    // if(R.size()==kval){
    //     // cliques.emplace_back(vector<int>(R.begin(),R.begin()+R.size()));
    //     clique curclique;
    //     curclique.theNodes=vector<int>(R.begin(),R.begin()+R.size());
    //     sort(curclique.theNodes.begin(),curclique.theNodes.end());
    //     if(mapclique.find(curclique)==mapclique.end()){

    //     }
    // }

    #ifdef couttree
    int curtreeId=overallTreeid;
    vector<int> sonids;
    #endif

    if(R.size()+theP.size()<kval-1) return;

    #ifdef fasterformer

    int layer=R.size();
    if(R.size()!=kval-1){//默认有directleaf
        for(int i=0;i<theP.size();++i){
            PPos[layer][theP[i]]=i;
            former[layer][i].clear();
        }
        for(int i=0;i<=pxr;++i){
            int u=PX[i];
            for(int j=0;j<tempColorAdjList[u].size();++j){
                int v=tempColorAdjList[u][j];
                if(InP[v]!=R.size()+1) break;
                former[layer][PPos[layer][v]].push_back(u);
            }
        }
    }
    #endif

    #ifdef directleaf
    if(R.size()==kval-2){
        for(int i=0;i<theP.size();++i){

            #ifdef couttree
            ++overallTreeid;
            cout<<"curid: "<<overallTreeid<<" sons: "<<endl;
            sonids.push_back(overallTreeid);
            #endif

            #ifdef counttree
            treenodecnt++;
            #endif

            int u=theP[i];
            vector<int> leftus;
            leftus.reserve(pxr+1);
            for(int j=0;j<tempColorAdjList[u].size();++j){
                int v=tempColorAdjList[u][j];
                if(InP[v]!=R.size()+1) break;
                leftus.push_back(v);
            }

            #ifdef fasterformer
            for(int j=0;j<former[layer][PPos[layer][u]].size();++j){
                leftus.push_back(former[layer][PPos[layer][u]][j]);
            }
            #else
            for(int j=0;j<=pxr;++j){
                int v=PX[j];
                if(node2color[v]<=node2color[u]) continue;
                for(int k=0;k<tempColorAdjList[v].size();++k){
                    int vv=tempColorAdjList[v][k];
                    if(InP[vv]!=R.size()+1) break;
                    if(vv==u){
                        leftus.push_back(v);
                        break;
                    }
                }
            }
            #endif

            clique templateclique;
            templateclique.theNodes=vector<int>(R.begin(),R.begin()+R.size());
            templateclique.theNodes.push_back(u);
            templateclique.selfsort();
            vector<int> cliqueIds;
            cliqueIds.reserve(leftus.size());
            for(int j=0;j<leftus.size();++j){
                int v=leftus[j];
                clique tempClique=templateclique;
                tempClique.addsort(v);

                int curId=-1;
                if(mapclique.find(tempClique)==mapclique.end()){
                    cliques.emplace_back(tempClique.theNodes);
                    mapclique[tempClique]=cliques.size()-1;
                    curId=cliques.size()-1;
                }else{
                    curId=mapclique[tempClique];
                }

                cliqueIds.push_back(curId);
            }
            
            fans.updateSize(cliques.size());
            for(int i=1;i<cliqueIds.size();++i){
                fans.merge(cliqueIds[i],cliqueIds[0]);
            }
        }

        #ifdef couttree
        cout<<"curid: "<<curtreeId<<" sons: ";
        for(int i=0;i<sonids.size();++i){
            cout<<sonids[i]<<",";
        }
        cout<<endl;
        #endif


        return;
    }
    #endif

    if(R.size()==kval-1){
        vector<int> cliqueIds;
        cliqueIds.reserve(pxr+1);
        clique templateclique;
        templateclique.theNodes=vector<int>(R.begin(),R.begin()+R.size());
        templateclique.selfsort();
        for(int i=0;i<=pxr;++i){
            int leftu=PX[i];
            clique tempClique=templateclique;
            // tempClique.theNodes.push_back(leftu);
            tempClique.addsort(leftu);

            // if(tempClique.theNodes[0]==leftu||tempClique.theNodes[1]==leftu||tempClique.theNodes[0]==tempClique.theNodes[1]){
            //     cerr<<"here"<<endl;
            // }

            int curId=-1;
            if(mapclique.find(tempClique)==mapclique.end()){
                cliques.emplace_back(tempClique.theNodes);
                mapclique[tempClique]=cliques.size()-1;
                curId=cliques.size()-1;
            }else{
                curId=mapclique[tempClique];
            }

            cliqueIds.push_back(curId);
        }

        fans.updateSize(cliques.size());
        for(int i=1;i<cliqueIds.size();++i){
            fans.merge(cliqueIds[i],cliqueIds[0]);
        }

        return;
    }


    for(int i=0;i<theP.size();++i){
        int u=theP[i];
        if(R.size()+node2color[u]+1<kval-1) continue;

        int npxr=0;

        //prepare new P
        vector<int> newP;
        newP.reserve(theP.size());
        for(int j=0;j<tempColorAdjList[u].size();++j){
            int v=tempColorAdjList[u][j];
            if(InP[v]!=R.size()+1) break;
            newP.push_back(v);
            exchange(PX,IPX[v],npxr++,IPX);
        }

        //prepare new X

        #ifdef fasterformer
        for(int j=0;j<former[layer][PPos[layer][u]].size();++j){
            int v=former[layer][PPos[layer][u]][j];
            exchange(PX,IPX[v],npxr++,IPX);
        }
        #else
        for(int j=0;j<=pxr;++j){
            int vu=PX[j];
            if(node2color[vu]<=node2color[u]) continue;
            for(int k=0;k<tempColorAdjList[vu].size();++k){
                int tu=tempColorAdjList[vu][k];
                if(InP[tu]!=R.size()+1) break;
                if(tu==u){
                    exchange(PX,IPX[vu],npxr++,IPX);
                    break;
                }
            }
        }
        #endif
        npxr--;

        //prepare tempcoloradjlist
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+2;
        }
        for(int j=0;j<=npxr;++j){
            int v=PX[j];
            int nr=0;
            for(int k=0;k<tempColorAdjList[v].size();++k){
                int x=tempColorAdjList[v][k];
                if(InP[x]<R.size()+1) break;

                if(InP[x]==R.size()+2){
                    exchange(tempColorAdjList[v],nr++,k);
                }
            }
        }

        R.push_back(u);
        // if(R.size()==2&&R[0]==25640&&R[1]==123){
        //     cerr<<"here"<<endl;
        // }
        #ifdef couttree
        overallTreeid++;
        sonids.push_back(overallTreeid);
        #endif

        #ifdef counttree
        treenodecnt++;
        #endif
        kcliqueConnect(fans,kval,former,PPos,PX,IPX,InP,newP,node2color,tempColorAdjList,npxr,R,cliques,mapclique);
        R.pop_back();

        //reset InP//可否挪到外面去？
        for(int j=0;j<newP.size();++j){
            InP[newP[j]]=R.size()+1;
        }

    }

    #ifdef couttree
    cout<<"curid: "<<curtreeId<<" sons: ";
    for(int i=0;i<sonids.size();++i){
        cout<<sonids[i]<<",";
    }
    cout<<endl;
    #endif
}

void Graph::listConnectCliques(int kval,vector<vector<int> >& cliques,unf& fans){
    #ifdef couttree
    overallTreeid=0;
    #endif

    #ifdef counttree
    treenodecnt=0;
    #endif

    int nodeSize=adjList.size();

    vector<int> order;
    vector<vector<int> >later;
    int degeneracy=getDegeneracyOrder(order,later);

    //coloring the nodes
    vector<int> node2color;
    node2color.resize(nodeSize,-1);

    vector<int> colorFlag;
    colorFlag.resize(degeneracy+1,-1);
    int bigColor=-1;

    for(int i=order.size()-1;i>=0;--i){
        int u=order[i];
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(node2color[v]!=-1){
                colorFlag[node2color[v]]=u;
            }
        }
        int j;
        for(j=0;j<degeneracy+1;++j){
            if(colorFlag[j]!=u){
                node2color[u]=j;
                if(j>bigColor) bigColor=j;
                break;
            }
        }
        if(j==degeneracy+1){
            cerr<<"no color"<<endl;
            exit(0);
        }
    }

    cerr<<"big color: "<<bigColor<<endl;


    //get DAG
    vector<vector<int> > colorLater;
    colorLater.resize(nodeSize);
    for(int i=0;i<later.size();++i){
        for(int j=0;j<later[i].size();++j){
            int u=i;
            int v=later[i][j];
            if(node2color[u]<node2color[v]){
                colorLater[v].push_back(u);
            }else if(node2color[u]>node2color[v]){
                colorLater[u].push_back(v);
            }else{
                cerr<<"error in color"<<endl;
                exit(0);
            }
        }
    }
    int bigDegree=0;
    for(int i=0;i<colorLater.size();++i){
        if(bigDegree<colorLater[i].size()) bigDegree=colorLater[i].size();
    }


    // auto cmp=[&node2color](int a,int b){
    //     if(node2color[a]==node2color[b]){
    //         return a<b;
    //     }
    //     return node2color[a]>node2color[b];
    // };

    // vector<int> colorOrder=order;
    // sort(colorOrder.begin(),colorOrder.end(),cmp);//可能不需要

    //find k-1 cliques
    vector<int> PX,IPX,R;
    vector<int> InP;
    vector<vector<int> > tempColorAdjList;
    tempColorAdjList.resize(nodeSize);
    for(int i=0;i<nodeSize;++i) tempColorAdjList[i].reserve(bigDegree);
    InP.resize(nodeSize,1);
    PX.resize(nodeSize);
    IPX.resize(nodeSize);
    R.reserve(kval);
    vector<int> theP;
    theP.reserve(bigDegree);
    unordered_map<clique,int,hashClique> mapclique;
    for(int i=0;i<PX.size();++i){
        PX[i]=i;IPX[i]=i;
    }

    vector<vector<vector<int> > > former;
    vector<vector<int> > PPos;
    former.resize(kval);
    PPos.resize(kval);
    for(int i=0;i<kval;++i){
        former[i].resize(bigDegree);
        PPos[i].resize(nodeSize);
    }

    //debug
    // vector<int> savePX;
    // savePX.reserve(nodeSize);

    #ifdef couttree
    int curtreeid=overallTreeid;
    vector<int> sonids;
    #endif

    for(int i=0;i<order.size();++i){
        int u=order[i];
        if(node2color[u]+1<kval-1){//等于kval-1也行
            continue;
        }

        int pxr=0;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            exchange(PX,pxr++,IPX[v],IPX);
            if(node2color[v]<node2color[u]){
                InP[v]=2;
                theP.push_back(v);
            }
        }
        pxr--;

        // savePX.assign(PX.begin(),PX.begin()+pxr+1);

        //debug
        // int cnt=0;

        for(int j=0;j<=pxr;++j){
            int v=PX[j];
            for(int k=0;k<colorLater[v].size();++k){
                int nv=colorLater[v][k];
                if(InP[nv]==2) tempColorAdjList[v].push_back(nv);
                //debug
                // if(u==25640){
                //     if(nv==9) cnt++;
                // }
            }
        }

        R.push_back(u);
        //debug
        // if(R[0]==25640){
        //     cerr<<"here"<<endl;
        //     cerr<<tempColorAdjList[123][0]<<" "<<tempColorAdjList[123][1]<<" "<<tempColorAdjList[123][2]<<endl;
        //     cerr<<cnt<<endl;
        // }
        #ifdef couttree
        overallTreeid++;
        sonids.push_back(overallTreeid);
        #endif

        #ifdef counttree
        treenodecnt++;
        #endif
        kcliqueConnect(fans,kval,former,PPos,PX,IPX,InP,theP,node2color,tempColorAdjList,pxr,R,cliques,mapclique);
        R.pop_back();

        //clear tempcoloradjlist
        for(int j=0;j<=pxr;++j){
            tempColorAdjList[PX[j]].clear();
        }
        // for(int j=0;j<savePX.size();++j){
        //     tempColorAdjList[savePX[j]].clear();
        // }
        for(int j=0;j<theP.size();++j){
            InP[theP[j]]=1;
        }
        theP.clear();
        
    }

    #ifdef couttree
    cout<<"curid: "<<curtreeid<<" sons: ";
    for(int i=0;i<sonids.size();++i){
        cout<<sonids[i]<<",";
    }
    cout<<endl;
    #endif

    #ifdef counttree
    cout<<"treenodecnt: "<<treenodecnt<<endl;
    #endif

}

inline int Graph::getAnyCliqueId(cliqueTree& tree, unordered_set<int>& theParts,unordered_set<int>& RParts,int startTreeNode){
    while(true){
        // int ssize=tree.treeNodePool[tree.root].sons.size();
        if(tree.treeNodePool[startTreeNode].leafMark>=0){
            return tree.treeNodePool[startTreeNode].leafMark;
        }
        vector<int>& sons=tree.treeNodePool[startTreeNode].sons;

        bool found=false;
        for(int i=0;i<sons.size();++i){
            int theInNode=tree.treeNodePool[sons[i]].inNode;
            if(theParts.find(theInNode)!=theParts.end()||RParts.find(theInNode)!=RParts.end()){
                startTreeNode=sons[i];
                found=true;
                break;
            }
        }

        if(found==false){
            cout<<"error"<<endl;//理论上不可能有这种情况
            exit(0);
        }
    }

}

void Graph::connectCliques(cliqueTree& tree,unf& f,unf& fans,vector<int>& orderIndex,vector<int>& firstLayerSons,vector<int>& xTreeNodesStack,vector<int>& PX,vector<int>& IPX,int xl,int pl,int pr,vector<vector<int> >& later,vector<vector<int> >& tempAdjList,vector<int>& R){
    //对PUX进行分块
    f.reinit(xl,pr);

    #ifdef fasterconnect
    for(int i=xl;i<=pr;++i){
        int u=PX[i];
        for(int j=0;j<later[u].size();++j){
            int v=later[u][j];
            if(IPX[v]<xl||IPX[v]>pr) break;
            f.merge(i,IPX[v]);
        }
    }
    #else
    for(int i=xl;i<pl;++i){
        int u=PX[i];
        for(int j=0;j<later[u].size();++j){
            int v=later[u][j];
            if(IPX[v]>=xl&&IPX[v]<=pr){
                f.merge(i,IPX[v]);
            }
        }

        for(int j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
            f.merge(i,IPX[v]);
        }
    }

    for(int i=pl;i<=pr;++i){
        int u=PX[i];
        for(int j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
            f.merge(i,IPX[v]);
        }
    }
    #endif

    //计算PUX中有多少连通块
    int parts=0;
    for(int i=xl;i<=pr;++i){
        if(f.fa[i]==i) ++parts;
    }
    if(parts<=1) return;

    //分离出每一个连通块和其中的最小order节点
    unordered_map<int,unordered_set<int> > listParts;
    unordered_map<int,int> partsFirst;
    for(int i=xl;i<=pr;++i){
        int val=PX[i];
        int father=f.find(i);
        listParts[father].insert(val);
        if(partsFirst.find(father)==partsFirst.end()) partsFirst[father]=val;
        else{
            int curOrder=orderIndex[partsFirst[father]];
            if(orderIndex[val]<curOrder){
                partsFirst[father]=val;
            }
        }
    }
    vector<int> holdCliqueIDs;
    holdCliqueIDs.reserve(parts);

    unordered_set<int> RParts(R.begin(),R.end());

    //debug
    // if(RParts.size()==3&&RParts.find(15914)!=RParts.end()&&RParts.find(15913)!=RParts.end()&&RParts.find(17329)!=RParts.end()){
    //     exit(0);
    // }


    //处理每个part
    unordered_map<int,unordered_set<int> >::iterator it=listParts.begin();
    while(it!=listParts.end()){
        unordered_set<int>& theParts=it->second;

        //找到当前part第一个出现的节点在firstLayerStack或xTreeNodesStack中第一个出现的地方
        int firstTreeNode;
        int first=partsFirst[it->first];
        // int firstPos=lower_bound(firstLayerStack.begin(),firstLayerStack.end(),orderIndex[first])-firstLayerStack.begin();
        if(firstLayerSons[first]==-1){// 在firstLayerStack里没找到
            //在xTreeNodesStack里找
            for(int i=0;i<xTreeNodesStack.size();++i){
                int theInNode=tree.treeNodePool[xTreeNodesStack[i]].inNode;
                if(theParts.find(theInNode)!=theParts.end()){//一定会有成立的情况
                    holdCliqueIDs.push_back(getAnyCliqueId(tree,theParts,RParts,xTreeNodesStack[i]));
                    break;
                }
            }
        }else{
            holdCliqueIDs.push_back(getAnyCliqueId(tree,theParts,RParts,tree.treeNodePool[tree.root].sons[firstLayerSons[first]]));
        }

        it++;
    }
    
    //链接得到的cliques

    for(int i=1;i<holdCliqueIDs.size();++i){
        fans.merge(holdCliqueIDs[i],holdCliqueIDs[0]);
    }

}

int Graph::bkConnect(bool needPivot,int nopivotPSize,bool savePivot,bool connectDirect,bool subClique,cliqueTree& tree,unf& f,unf& fans,int kval,vector<int>& orderIndex,vector<int>& firstLayerSons,vector<int>& xTreeNodesStack,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,vector<vector<int> >& later,int xl,int pl,int pr,vector<int>& R,vector<vector<int>>& cliques){

    //subClique为true时不会成立
    if(savePivot==true&&connectDirect==true){
        if(pr-xl+1>=2&&R.size()>=kval-1){
            fans.updateSize(cliques.size());
            connectCliques(tree,f,fans,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,xl,pl,pr,later,tempAdjList,R);
        }

        return -1;
    }

    if(pr<pl){
        if(xl>=pl&&R.size()>=kval){

            #ifdef nopivotStep
            if(maximumClique<R.size()) maximumClique=R.size();
            #endif

            cliques.emplace_back(vector<int>(R.begin(),R.begin()+R.size()));
            int theNode=tree.getNewNode();
            tree.treeNodePool[theNode].leafMark=cliques.size()-1;
            tree.treeNodePool[theNode].inNode=R[R.size()-1];
            return theNode;
        }
        if(xl<pl-1&&R.size()>=kval-1){//需要链接一下clique
            //扩展一下fans
            fans.updateSize(cliques.size());
            connectCliques(tree,f,fans,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,xl,pl,pr,later,tempAdjList,R);
        }
        return -1;
    }
    int psize=pr-pl+1;
    int xsize=pl-xl;

    if(R.size()+psize<kval-1) return -1;

    int originalPl=pl;
    vector<int> tempCand;
    int tobeSave;

    if(subClique){
        tempCand.push_back(PX[pl]);
        savePivot=false;
    }else if(needPivot){
        //select pivot
        int big=-1;
        int pivotIndex=-1;
        int pivot=-1;
        bool isSubClique=true;//检查是不是仅仅只是一个子clique
        for(int i=xl;i<=pr;++i){
            int u=PX[i];
            int j;
            for(j=0;j<tempAdjList[u].size();++j){
                int v=tempAdjList[u][j];
                if(IPX[v]<pl||IPX[v]>pr) break;
            }
            if(j!=psize-1){
                isSubClique=false;
            }
            if(j>big){
                big=j;
                pivotIndex=i;
                pivot=u;
            }
        }

        if(xsize>0) isSubClique=false;//不考虑有x的情况

        //generate real candidate
        tempCand.reserve(psize);
        int neil=pr;
        for(int i=0;i<tempAdjList[pivot].size();++i){
            int v=tempAdjList[pivot][i];
            if(IPX[v]<pl||IPX[v]>pr) break;
            exchange(PX,IPX[v],neil--,IPX);
        }

        // for(int i=pl;i<=neil;++i){
        //     tempCand.push_back(PX[i]);
        // }

        if(isSubClique==true){
            savePivot=false;
            subClique=true;
        }

        if(savePivot==true) tempCand.assign(PX.begin()+pl,PX.begin()+pr+1);
        else tempCand.assign(PX.begin()+pl,PX.begin()+neil+1);
        tobeSave=neil+1-pl;
    }else{
        //generate real candidate
        tempCand.assign(PX.begin()+pl,PX.begin()+pr+1);
        if(savePivot==true) tobeSave=pr+1-pl;
        if(xl>=pl){
            bool isSubClique=true;
            for(int i=pl;i<=pr;++i){
                int j;
                int u=PX[i];
                for(j=0;j<tempAdjList[u].size();++j){
                    int v=tempAdjList[u][j];
                    if(IPX[v]<pl||IPX[v]>pr) break;
                }
                if(j!=psize-1){
                    isSubClique=false;
                    break;
                }
            }
            if(isSubClique){
                tempCand.clear();
                tempCand.push_back(PX[pl]);
                if(savePivot==true) tobeSave=1;
                subClique=true;
            }
        }
    }

    int curTreeNode=-1;
    int inTreeVertex=R[R.size()-1];
    int oriXTreeStackSize=xTreeNodesStack.size();
    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        
        vector<int> tempNewX;
        tempNewX.reserve(xsize);
        //searching in X
        for(int j=xl;j<pl;++j){
            int v=PX[j];
            for(int k=0;k<tempAdjList[v].size();++k){
                int possibleU=tempAdjList[v][k];
                if(IPX[possibleU]<pl||IPX[possibleU]>pr) break;
                if(possibleU==u){
                    tempNewX.push_back(v);
                    break;
                }
            }
        }
        //no need for searching in P

        //prepare new X and P
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<tempNewX.size();++j){
            exchange(PX,IPX[tempNewX[j]],nxl--,IPX);
        }
        for(int j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
            exchange(PX,IPX[v],npr++,IPX);
        }
        nxl++;
        npr--;

        //shrink later
        #ifdef fasterconnect
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int nsize=0;
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                if(IPX[nv]<xl||IPX[nv]>pr) break;
                if(IPX[nv]>=nxl&&IPX[nv]<=npr){
                    exchange(later[v],k,nsize++);
                }
            }
        }
        #endif

        //shrink tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int numNeighborInNewP=0;
            for(int k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl||IPX[nv]>pr) break;
                if(IPX[nv]<=npr){
                    exchange(tempAdjList[v],k,numNeighborInNewP++);
                }
            }
        }

        R.push_back(u);
        // bkPivot(PX,IPX,tempAdjList,nxl,pl,npr,R,cliques);
        int res=bkConnect(needPivot&&(npr-pl+1)>nopivotPSize,nopivotPSize,savePivot,i>=tobeSave,subClique,tree,f,fans,kval,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,tempAdjList,later,nxl,pl,npr,R,cliques);
        if(res>=0){
            if(curTreeNode==-1){
                curTreeNode=tree.getNewNode();
                tree.treeNodePool[curTreeNode].leafMark=-1;
                tree.treeNodePool[curTreeNode].inNode=inTreeVertex;
            }
            tree.treeNodePool[curTreeNode].sons.push_back(res);
            xTreeNodesStack.push_back(res);
        }
        R.pop_back();
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
        
        //update tempAdjList
        for(int j=xl;j<=pr;++j){
            int v=PX[j];
            int uindex=-1;
            int k;
            for(k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl-1||IPX[nv]>pr) break;
                if(nv==u) uindex=k;
            }
            if(uindex==-1) continue;
            exchange(tempAdjList[v],uindex,k-1);
        }
    }

    //recover X
    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        exchange(PX,IPX[u],--pl,IPX);
    }

    if(R.size()>=kval-1){
        //update size of fans
        fans.updateSize(cliques.size());
        //link cliques
        connectCliques(tree,f,fans,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,xl,originalPl,pr,later,tempAdjList,R);
    }

    xTreeNodesStack.resize(oriXTreeStackSize);
    return curTreeNode;
}

void Graph::listConnectMaximalCliques(int kval,int nopivotRatio,int nopivotPSize,bool savePivot,vector<vector<int>>& cliques,unf& fans){
    int adjListSize=adjList.size();

    vector<vector<int> > tempAdjList;
    vector<int> PX,IPX,R;
    PX.resize(adjListSize);
    IPX.resize(adjListSize);
    R.reserve(adjListSize);

    //initialize PX and IPX
    for(int i=0;i<adjListSize;++i){
        PX[i]=IPX[i]=i;
    }

    cliqueTree tree;
    tree.root=tree.getNewNode();
    tree.treeNodePool[tree.root].inNode=-1;
    tree.treeNodePool[tree.root].leafMark=-1;

    vector<vector<int> > later;
    vector<int> order;
    vector<int> orderIndex;
    int degenaracy=getDegeneracyOrder(order,later);

    cerr<<"degeneracy: "<<degenaracy<<endl;
    orderIndex.resize(adjListSize);
    for(int i=0;i<order.size();++i){
        orderIndex[order[i]]=i;
    }

    //initialize tempAdjList
    tempAdjList.resize(adjListSize);
    for(int i=0;i<adjListSize;++i) tempAdjList[i].reserve(degenaracy);

    int pl=0;
    int firstPart=order.size()/100*nopivotRatio;
    vector<int> firstLayerSons,xTreeNodesStack;
    // firstLayerSons.reserve(adjListSize);
    firstLayerSons.resize(adjListSize,-1);
    xTreeNodesStack.reserve(adjListSize);
    unf f;
    f.init(adjListSize);

    #ifdef nopivotStep
    maximumClique=0;
    #endif

    //k应大于等于3，所以第一层不需要处理
    for(int i=0;i<order.size();++i){
        #ifdef connectCliqueBar
        // if(i%(order.size()/100)==0) cout<<i<<endl;
        if(i>=8887) cout<<i<<endl;
        #endif

        int u=order[i];

        // obtain new P and X
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]<pl) exchange(PX,IPX[v],nxl--,IPX);
            else exchange(PX,IPX[v],npr++,IPX);
        }

        nxl++;
        npr--;
        //shrink later
        #ifdef fasterconnect
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int nsize=0;
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                if(IPX[nv]>=nxl&&IPX[nv]<=npr){
                    exchange(later[v],k,nsize++);
                }
            }
        }
        #endif

        //obtain new tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                #ifdef fasterconnect
                if(IPX[nv]<nxl||IPX[nv]>npr) break;
                #endif
                //nv is in new P
                if(IPX[nv]>=pl&&IPX[nv]<=npr){
                    tempAdjList[v].push_back(nv);
                    if(j>=pl){
                        tempAdjList[nv].push_back(v);
                    }
                }
            }
        }

        R.push_back(u);
        // bkPivot(PX,IPX,tempAdjList,nxl,pl,npr,R,cliques);

        #ifdef nopivotStep
        //choose nopivotPSize
        // if(maximumClique>20){
        //     nopivotPSize=10;
        // }else{
        //     nopivotPSize=45-(maximumClique/5)*10;
        // }
        nopivotPSize=50-maximumClique*2+1;
        if(nopivotPSize<10) nopivotPSize=10;

        #endif

        int node=bkConnect(i>firstPart&&(npr-pl+1)>nopivotPSize,nopivotPSize,savePivot,false,false,tree,f,fans,kval,orderIndex,firstLayerSons,xTreeNodesStack,PX,IPX,tempAdjList,later,nxl,pl,npr,R,cliques);
        R.pop_back();
        if(node!=-1){
            tree.treeNodePool[tree.root].sons.push_back(node);
            firstLayerSons[u]=tree.treeNodePool[tree.root].sons.size()-1;
        }

        //clear tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            tempAdjList[v].clear();
        }
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
    }
}

void Graph::bkNoPivot(vector<int>& PX,vector<int>& IPX,int xbegin,int pbegin,int pend,vector<int>& R,vector<vector<int> >& cliques){
    if(pbegin>pend){
        if(xbegin>=pbegin) cliques.push_back(vector<int>(R.begin(),R.begin()+R.size()));
        return;
    }

    vector<int> tempP;
    tempP.assign(PX.begin()+pbegin,PX.begin()+pend+1);
    for(int i=0;i<tempP.size();++i){
        int u=tempP[i];
        
    }
}

void Graph::listMaximalCliqueNoPivot(vector<vector<int> >& cliques){
    vector<int> order;
    vector<vector<int> > later;
    getDegeneracyOrder(order,later);

    int adjListSize=adjList.size();
    vector<int> PX,R,IPX;
    PX.resize(adjListSize);
    IPX.resize(adjListSize);
    R.reserve(adjListSize);

    for(int i=0;i<adjListSize;++i){
        PX[i]=IPX[i]=i;
    }

    int xbegin,pbegin,pend;
    xbegin=-1;
    pbegin=0;
    pend=adjListSize-1;

    for(int i=0;i<order.size();++i){
        int u=order[i];
        R.push_back(u);
        int tempxbegin=pbegin-1;
        int temppend=pbegin;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];

            if(IPX[v]<pbegin) exchange(PX,tempxbegin--,IPX[v],IPX);
            else exchange(PX,temppend++,IPX[v],IPX);
        }

        bkNoPivot(PX,IPX,tempxbegin+1,pbegin,temppend-1,R,cliques);
    }
}

void Graph::buildGraphViaEdges(vector<pair<int,int> >& edges){
    int bigNode=-1;
    for(int i=0;i<edges.size();++i){
        bigNode=max(edges[i].first,bigNode);
        bigNode=max(edges[i].second,bigNode);
    }

    adjList.resize(bigNode+1);
    for(int i=0;i<edges.size();++i){
        int u=edges[i].first;
        int v=edges[i].second;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

bool Graph::dfs(int from,int u,vector<bool>& vis){
    for(int i=0;i<adjList[u].size();++i){
        int v=adjList[u][i];
        if(v==from) continue;
        if(vis[v]) return false;
        bool res=dfs(u,v,vis);
        if(res==false) return false;
    }
    return true;
}

bool Graph::isTrees(){
    vector<bool> vis;
    vis.resize(adjList.size(),false);
    for(int i=0;i<adjList.size();++i){
        if(vis[i]==false){
            bool res=dfs(-1,i,vis);
            if(res==false) return false;
        }
    }
    return true;
}

void Graph::reportByte(){
    ll totalElement=0;
    for(int i=0;i<adjList.size();++i){
        totalElement+=adjList[i].size();
    }
    cout<<"total size in byte: "<<totalElement*4<<endl;
}

void Graph::buildCliqueGraph(vector<vector<int>>& clique2node,vector<vector<int>>& node2clique){
    int totalClique=clique2node.size();
    int totalNode=node2clique.size();

    adjList.resize(totalClique);
    vector<int> neighbors,ineighbors;
    neighbors.resize(totalClique);
    ineighbors.resize(totalClique);
    for(int i=0;i<totalClique;++i){
        neighbors[i]=i;
        ineighbors[i]=i;
    }
    for(int i=0;i<totalClique;++i){
        int neighborr=-1;
        for(int j=0;j<clique2node[i].size();++j){
            int node=clique2node[i][j];
            for(int k=0;k<node2clique[node].size();++k){
                int nei=node2clique[node][k];
                if(nei==i) continue;
                if(ineighbors[nei]<=neighborr) continue;
                exchange(neighbors,ineighbors[nei],++neighborr,ineighbors);
            }
        }
        // if(ineighbors[i]<=neighborr) exchange(neighbors,ineighbors[i],neighborr--,ineighbors);
        adjList[i].assign(neighbors.begin(),neighbors.begin()+neighborr+1);
    }
}

void Graph::bkPivotRegular(unordered_set<int> cand,vector<int> curclique,unordered_set<int> X,vector<vector<int>>& holdcliques){
    if(cand.size()==0&&X.size()==0){//汇报答案
        holdcliques.push_back(curclique);
        return;
    }

    //在cand和X中选择pivot
    int bigsize=-1;
    int bigsizeNode=-1;
    unordered_set<int>::iterator it=cand.begin();
    while(it!=cand.end()){
        vector<int>& neighbors=adjList[*it];
        int tempcnt=0;
        for(int i=0;i<neighbors.size();++i){
            if(cand.find(neighbors[i])!=cand.end()) tempcnt++;
        }
        if(tempcnt>bigsize){
            bigsize=tempcnt;
            bigsizeNode=*it;
        }
        it++;
    }
    it=X.begin();
    while(it!=X.end()){
        vector<int>& neighbors=adjList[*it];
        int tempcnt=0;
        for(int i=0;i<neighbors.size();++i){
            if(cand.find(neighbors[i])!=cand.end()) tempcnt++;
        }
        if(tempcnt>bigsize){
            bigsize=tempcnt;
            bigsizeNode=*it;
        }
        it++;
    }

    unordered_set<int> tempInter;
    if(bigsize>0){
        for(int i=0;i<adjList[bigsizeNode].size();++i){
            if(cand.find(adjList[bigsizeNode][i])!=cand.end()) tempInter.insert(adjList[bigsizeNode][i]);
        }
    }
    unordered_set<int> candcp=cand;
    it=candcp.begin();
    while(it!=candcp.end()){
        if(tempInter.find(*it)!=tempInter.end()){
            it++;
            continue;
        }
        unordered_set<int> newcand,newX;
        for(int i=0;i<adjList[*it].size();++i){
            if(cand.find(adjList[*it][i])!=cand.end()) newcand.insert(adjList[*it][i]);
            if(X.find(adjList[*it][i])!=X.end()) newX.insert(adjList[*it][i]);
        }
        vector<int> newcur=curclique;
        newcur.push_back(*it);
        bkPivotRegular(newcand,newcur,newX,holdcliques);
        cand.erase(*it);X.insert(*it);
        it++;
    }
}

void Graph::listMaximalCliquesRegularDegeneracy(vector<vector<int>>& cliques){
    vector<int> order;
    vector<vector<int> > later;
    getDegeneracyOrder(order,later);

    unordered_set<int> X;
    vector<int> curclique;
    int adjListSize=adjList.size();

    for(int i=0;i<order.size();++i){
        int u=order[i];
        unordered_set<int> cand;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(X.find(v)!=X.end()) continue;
            cand.insert(v);
        }

        X.insert(u);
    }
}

void Graph::listMaximalCliquesRegular(vector<vector<int>>& cliques){
    unordered_set<int> nodeset;
    int adjListSize=adjList.size();
    for(int i=0;i<adjListSize;++i){
        nodeset.insert(i);
    }
    bkPivotRegular(nodeset,vector<int>(),unordered_set<int>(),cliques);
}

void Graph::bkPivot(int kval,vector<int>& PX,vector<int>& IPX,vector<vector<int> >& tempAdjList,int xl,int pl,int pr,vector<int>& R,vector<vector<int>>& cliques){
    if(pr<pl){
        if(xl>=pl&&R.size()>=kval) cliques.emplace_back(vector<int>(R.begin(),R.begin()+R.size()));
        return;
    }
    int psize=pr-pl+1;
    int xsize=pl-xl;

    if(R.size()+psize<kval) return;

    #ifndef nopivot
    //select pivot
    int big=-1;
    int pivotIndex=-1;
    int pivot=-1;
    for(int i=xl;i<=pr;++i){
        int u=PX[i];
        int j;
        for(j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
        }
        if(j>big){
            big=j;
            pivotIndex=i;
            pivot=u;
        }
    }

    //generate real candidate
    vector<int> tempCand;
    tempCand.reserve(psize);
    int neil=pr;
    for(int i=0;i<tempAdjList[pivot].size();++i){
        int v=tempAdjList[pivot][i];
        if(IPX[v]<pl||IPX[v]>pr) break;
        exchange(PX,IPX[v],neil--,IPX);
    }

    // for(int i=pl;i<=neil;++i){
    //     tempCand.push_back(PX[i]);
    // }
    tempCand.assign(PX.begin()+pl,PX.begin()+neil+1);

    #endif

    #ifdef nopivot
    //generate real candidate
    vector<int> tempCand;
    tempCand.assign(PX.begin()+pl,PX.begin()+pr+1);
    if(xl>=pl){
        bool isSubClique=true;
        for(int i=pl;i<=pr;++i){
            int j;
            int u=PX[i];
            for(j=0;j<tempAdjList[u].size();++j){
                int v=tempAdjList[u][j];
                if(IPX[v]<pl||IPX[v]>pr) break;
            }
            if(j!=psize-1){
                isSubClique=false;
                break;
            }
        }
        if(isSubClique){
            tempCand.clear();
            tempCand.push_back(PX[pl]);
        }
    }
    #endif

    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        
        vector<int> tempNewX;
        tempNewX.reserve(xsize);
        //searching in X
        for(int j=xl;j<pl;++j){
            int v=PX[j];
            for(int k=0;k<tempAdjList[v].size();++k){
                int possibleU=tempAdjList[v][k];
                if(IPX[possibleU]<pl||IPX[possibleU]>pr) break;
                if(possibleU==u){
                    tempNewX.push_back(v);
                    break;
                }
            }
        }
        //no need for searching in P

        //prepare new X and P
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<tempNewX.size();++j){
            exchange(PX,IPX[tempNewX[j]],nxl--,IPX);
        }
        for(int j=0;j<tempAdjList[u].size();++j){
            int v=tempAdjList[u][j];
            if(IPX[v]<pl||IPX[v]>pr) break;
            exchange(PX,IPX[v],npr++,IPX);
        }
        nxl++;
        npr--;

        //shrink tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            int numNeighborInNewP=0;
            for(int k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl||IPX[nv]>pr) break;
                if(IPX[nv]<=npr){
                    exchange(tempAdjList[v],k,numNeighborInNewP++);
                }
            }
        }

        R.push_back(u);
        bkPivot(kval,PX,IPX,tempAdjList,nxl,pl,npr,R,cliques);
        R.pop_back();
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}
        
        //update tempAdjList
        for(int j=xl;j<=pr;++j){
            int v=PX[j];
            int uindex=-1;
            int k;
            for(k=0;k<tempAdjList[v].size();++k){
                int nv=tempAdjList[v][k];
                if(IPX[nv]<pl-1||IPX[nv]>pr) break;
                if(nv==u) uindex=k;
            }
            if(uindex==-1) continue;
            exchange(tempAdjList[v],uindex,k-1);
        }
    }

    //recover X
    for(int i=0;i<tempCand.size();++i){
        int u=tempCand[i];
        exchange(PX,IPX[u],--pl,IPX);
    }
    
}

// void Graph::bkPivot(vector<int>& P,vector<int>& IP,vector<int>& X,vector<int>& IX,int candIndex,int xIndex,vector<int>& R,vector<vector<int>>& cliques){
//     // int newCandIndex=candIndex;
//     // int newXIndex=xIndex;
//     if(candIndex<0){
//         if(xIndex<0&&R.size()>=3) cliques.push_back(vector<int>(R.begin(),R.begin()+R.size()));
//         return;
//     }

//     //select pivot
//     int big=-1;
//     int pivot;
//     for(int i=0;i<=candIndex;++i){
//         int u=P[i];
//         int validNeighbor=0;
//         for(int j=0;j<adjList[u].size();++j){
//             int v=adjList[u][j];
//             if(IP[v]<=candIndex) validNeighbor++;
//         }
//         if(big<validNeighbor){
//             big=validNeighbor;
//             pivot=u;
//         }
//     }
//     for(int i=0;i<=xIndex;++i){
//         int u=X[i];
//         int validNeighbor=0;
//         for(int j=0;j<adjList[u].size();++j){
//             int v=adjList[u][j];
//             if(IP[v]<=candIndex) validNeighbor++;
//         }
//         if(big<validNeighbor){
//             big=validNeighbor;
//             pivot=u;
//         }
//     }

//     //generate new temp candidate
//     vector<int> tempCand;
//     tempCand.reserve(candIndex+1);

//     int noncandl=candIndex;
//     if(IP[pivot]<=candIndex) exchange(P,0,IP[pivot],IP);
//     for(int i=0;i<adjList[pivot].size();++i){
//         int v=adjList[pivot][i];
//         if(IP[v]<=candIndex) exchange(P,noncandl--,IP[v],IP);
//     }
//     for(int i=0;i<=noncandl;++i) tempCand.push_back(P[i]); //new temp candidate

//     for(int i=0;i<tempCand.size();++i){
//         //prepare new P, X
//         int u=tempCand[i];
//         int candr=0;
//         int xr=0;
//         for(int j=0;j<adjList[u].size();++j){
//             int v=adjList[u][j];
//             if(IP[v]<=candIndex) exchange(P,candr++,IP[v],IP);
//             else if(IX[v]<=xIndex) exchange(X,xr++,IX[v],IX);
//         }

//         R.push_back(u);
//         bkPivot(P,IP,X,IX,candr-1,xr-1,R,cliques);
//         R.pop_back();
//         exchange(P,IP[u],candIndex--,IP); // P=P-{u}
//         exchange(X,IX[u],++xIndex,IX); // X=X+{u}
//     }
    
//     //recover X
//     for(int i=0;i<tempCand.size();++i){
//         int u=tempCand[i];
//         exchange(X,IX[u],xIndex--,IX);
//     }

// }

int Graph::getDegeneracyOrder(vector<int>& nodeslist,vector<int>& order,vector<vector<int> >& later,vector<int>& IPX,int pr){
    int bigd=0;
    int adjListSize=adjList.size();
    int nodeslistSize=nodeslist.size();

    vector<int> tmpDegree;
    tmpDegree.resize(adjListSize);
    for(int i=0;i<nodeslist.size();++i){
        int u=nodeslist[i];
        int td=0;
        for(td=0;td<adjList[u].size();++td){
            int v=adjList[u][td];
            if(IPX[v]>pr) break;
        }
        tmpDegree[u]=td;
        if(bigd<td) bigd=td;
    }

    vector<int> bin,verts,pos;
    bin.resize(bigd+1,0);
    verts.resize(nodeslistSize);
    pos.resize(adjListSize);

    order.resize(nodeslistSize);
    later.resize(adjListSize);

    for(int i=0;i<nodeslistSize;++i){
        int u=nodeslist[i];
        int d=tmpDegree[u];
        bin[d]++;
    }
    for(int i=1;i<=bigd;++i) bin[i]+=bin[i-1];
    // bin[bigd+1]
    for(int i=0;i<nodeslistSize;++i){
        int u=nodeslist[i];
        pos[u]=bin[tmpDegree[u]]-1;
        verts[--bin[tmpDegree[u]]]=u;
    }
    for(int i=0;i<nodeslistSize;++i){
        int vid=verts[i];
        order[i]=vid;

        later[vid].reserve(tmpDegree[vid]);
        for(int j=0;j<adjList[vid].size();++j){
            int nid=adjList[vid][j];
            if(IPX[nid]>pr) break;

            //getLaterNeighbor
            if(pos[nid]>pos[vid]) later[vid].push_back(nid);

            if(tmpDegree[nid]>tmpDegree[vid]){
                int binFront=verts[bin[tmpDegree[nid]]];
                if(binFront!=nid){
                    pos[binFront]=pos[nid];
                    pos[nid]=bin[tmpDegree[nid]];
                    verts[bin[tmpDegree[nid]]]=nid;
                    verts[pos[binFront]]=binFront;
                }
                bin[tmpDegree[nid]]++;
                tmpDegree[nid]--;
            }
        }
    }

    return tmpDegree[verts[nodeslistSize-1]];
}

int Graph::getDegeneracyOrder(vector<int>& order,vector<int>& coreNumber,vector<vector<int> >& later){
    int bigd=0;
    int adjListSize=adjList.size();
    for(int i=0;i<adjListSize;++i){
        if(bigd<adjList[i].size()) bigd=adjList[i].size();
    }

    vector<int> bin,verts,pos,tmpDegree;
    bin.resize(bigd+1,0);
    verts.resize(adjListSize);
    pos.resize(adjListSize);
    tmpDegree.resize(adjListSize);
    order.resize(adjListSize);
    later.resize(adjListSize);

    for(int i=0;i<adjListSize;++i){
        int d=adjList[i].size();
        bin[d]++;
        tmpDegree[i]=d;
    }
    for(int i=1;i<=bigd;++i) bin[i]+=bin[i-1];
    // bin[bigd+1]
    for(int i=0;i<adjListSize;++i){
        pos[i]=bin[tmpDegree[i]]-1;
        verts[--bin[tmpDegree[i]]]=i;
    }
    for(int i=0;i<adjListSize;++i){
        int vid=verts[i];
        order[i]=vid;

        later[vid].reserve(tmpDegree[vid]);
        for(int j=0;j<adjList[vid].size();++j){
            int nid=adjList[vid][j];

            //getLaterNeighbor
            if(pos[nid]>pos[vid]) later[vid].push_back(nid);

            if(tmpDegree[nid]>tmpDegree[vid]){
                int binFront=verts[bin[tmpDegree[nid]]];
                if(binFront!=nid){
                    pos[binFront]=pos[nid];
                    pos[nid]=bin[tmpDegree[nid]];
                    verts[bin[tmpDegree[nid]]]=nid;
                    verts[pos[binFront]]=binFront;
                }
                bin[tmpDegree[nid]]++;
                tmpDegree[nid]--;
            }
        }
    }

    coreNumber=tmpDegree;
    return tmpDegree[verts[adjListSize-1]];
}

int Graph::getDegeneracyOrder(vector<int>& order,vector<int>& coreNumber){
    int bigd=0;
    int adjListSize=adjList.size();
    for(int i=0;i<adjListSize;++i){
        if(bigd<adjList[i].size()) bigd=adjList[i].size();
    }

    vector<int> bin,verts,pos,tmpDegree;
    bin.resize(bigd+1,0);
    verts.resize(adjListSize);
    pos.resize(adjListSize);
    tmpDegree.resize(adjListSize);
    order.resize(adjListSize);

    for(int i=0;i<adjListSize;++i){
        int d=adjList[i].size();
        bin[d]++;
        tmpDegree[i]=d;
    }
    for(int i=1;i<=bigd;++i) bin[i]+=bin[i-1];
    // bin[bigd+1]
    for(int i=0;i<adjListSize;++i){
        pos[i]=bin[tmpDegree[i]]-1;
        verts[--bin[tmpDegree[i]]]=i;
    }
    for(int i=0;i<adjListSize;++i){
        int vid=verts[i];
        order[i]=vid;

        for(int j=0;j<adjList[vid].size();++j){
            int nid=adjList[vid][j];

            if(tmpDegree[nid]>tmpDegree[vid]){
                int binFront=verts[bin[tmpDegree[nid]]];
                if(binFront!=nid){
                    pos[binFront]=pos[nid];
                    pos[nid]=bin[tmpDegree[nid]];
                    verts[bin[tmpDegree[nid]]]=nid;
                    verts[pos[binFront]]=binFront;
                }
                bin[tmpDegree[nid]]++;
                tmpDegree[nid]--;
            }
        }
    }

    coreNumber=tmpDegree;
    return tmpDegree[verts[adjListSize-1]];

}

int Graph::getDegeneracyOrder(vector<int>& order,vector<vector<int> >& later){
    int bigd=0;
    int adjListSize=adjList.size();
    for(int i=0;i<adjListSize;++i){
        if(bigd<adjList[i].size()) bigd=adjList[i].size();
    }

    vector<int> bin,verts,pos,tmpDegree;
    bin.resize(bigd+1,0);
    verts.resize(adjListSize);
    pos.resize(adjListSize);
    tmpDegree.resize(adjListSize);
    order.resize(adjListSize);
    later.resize(adjListSize);

    for(int i=0;i<adjListSize;++i){
        int d=adjList[i].size();
        bin[d]++;
        tmpDegree[i]=d;
    }
    for(int i=1;i<=bigd;++i) bin[i]+=bin[i-1];
    // bin[bigd+1]
    for(int i=0;i<adjListSize;++i){
        pos[i]=bin[tmpDegree[i]]-1;
        verts[--bin[tmpDegree[i]]]=i;
    }
    for(int i=0;i<adjListSize;++i){
        int vid=verts[i];
        order[i]=vid;

        later[vid].reserve(tmpDegree[vid]);
        for(int j=0;j<adjList[vid].size();++j){
            int nid=adjList[vid][j];

            //getLaterNeighbor
            if(pos[nid]>pos[vid]) later[vid].push_back(nid);

            if(tmpDegree[nid]>tmpDegree[vid]){
                int binFront=verts[bin[tmpDegree[nid]]];
                if(binFront!=nid){
                    pos[binFront]=pos[nid];
                    pos[nid]=bin[tmpDegree[nid]];
                    verts[bin[tmpDegree[nid]]]=nid;
                    verts[pos[binFront]]=binFront;
                }
                bin[tmpDegree[nid]]++;
                tmpDegree[nid]--;
            }
        }
    }

    return tmpDegree[verts[adjListSize-1]];

}

void Graph::listMaximalCliques(vector<vector<int> >& cliques,int kval){
    int adjListSize=adjList.size();

    vector<vector<int> > tempAdjList;
    vector<int> PX,IPX,R;
    PX.resize(adjListSize);
    IPX.resize(adjListSize);
    R.reserve(adjListSize);

    //initialize PX and IPX
    for(int i=0;i<adjListSize;++i){
        PX[i]=IPX[i]=i;
    }

    vector<int> order;
    vector<vector<int> > later;
    int degenaracy=getDegeneracyOrder(order,later);

    #ifdef overallexample6
    order={0,16,15,13,14,12,11,10,1,8,7,2,4,5,9,6,3};
    vector<int> temppos;
    temppos.resize(17,-1);
    for(int i=0;i<order.size();++i) temppos[order[i]]=i;
    later=vector<vector<int> >();
    later.resize(17);
    for(int i=0;i<adjListSize;++i){
        for(int j=0;j<adjList[i].size();++j){
            int u=i,v=adjList[i][j];
            if(temppos[u]<temppos[v]) later[u].push_back(v);
        }
    }
    #endif

    // cerr<<"degeneracy: "<<degenaracy<<endl;

    //initialize tempAdjList
    tempAdjList.resize(adjListSize);
    for(int i=0;i<adjListSize;++i) tempAdjList[i].reserve(degenaracy);

    int pl=0;

    for(int i=0;i<order.size();++i){
        int u=order[i];

        #ifdef bkbar
        if(i%(order.size()/100)==0){
            cout<<i<<endl;
            cout<<"clique num: "<<cliques.size()<<endl;
        }
        #endif

        // obtain new P and X
        int nxl=pl-1;
        int npr=pl;
        for(int j=0;j<adjList[u].size();++j){
            int v=adjList[u][j];
            if(IPX[v]<pl) exchange(PX,IPX[v],nxl--,IPX);
            else exchange(PX,IPX[v],npr++,IPX);
        }

        
        nxl++;
        npr--;
        //obtain new tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            for(int k=0;k<later[v].size();++k){
                int nv=later[v][k];
                //nv is in new P
                if(IPX[nv]>=pl&&IPX[nv]<=npr){
                    tempAdjList[v].push_back(nv);
                    if(j>=pl){
                        tempAdjList[nv].push_back(v);
                    }
                }
            }
        }

        R.push_back(u);
        bkPivot(kval,PX,IPX,tempAdjList,nxl,pl,npr,R,cliques);
        R.pop_back();

        //clear tempAdjList
        for(int j=nxl;j<=npr;++j){
            int v=PX[j];
            tempAdjList[v].clear();
        }
        exchange(PX,IPX[u],pl++,IPX);//P=P-{u},X=X+{u}

    }

}

// void Graph::listMaximalCliques(vector<vector<int>>& cliques){
//     vector<int> order;
//     getDegeneracyOrder(order);

//     int adjListSize=adjList.size();
//     vector<int> P,X;
//     vector<int> IP,IX;
//     vector<int> R;
//     P.resize(adjListSize);
//     X.resize(adjListSize);
//     IP.resize(adjListSize);
//     IX.resize(adjListSize);
//     R.reserve(adjListSize);

//     for(int i=0;i<adjListSize;++i){
//         P[i]=i;X[i]=i;
//         IP[i]=i;IX[i]=i;
//     }
//     int candr=adjListSize-1;
//     int xr=-1;
//     for(int i=0;i<order.size();++i){
//         int u=order[i];
//         R.push_back(u);
//         int tempCandr=0;
//         int tempXr=0;
//         for(int j=0;j<adjList[u].size();++j){
//             int v=adjList[u][j];
//             if(IP[v]<=candr) exchange(P,tempCandr++,IP[v],IP); // add v into new P
//             else if(IX[v]<=xr) exchange(X,tempXr++,IX[v],IX); // add v into new X
//         }

//         bkPivot(P,IP,X,IX,tempCandr-1,tempXr-1,R,cliques);
//         R.pop_back();
//         exchange(P,IP[u],candr--,IP); // P=P-{u}
//         exchange(X,++xr,IX[u],IX); // X=X+{u}
//     }
// }

void Graph::readGraph(string filename){
    vector<vector<int> > holdLines;
    bool res=readFile(filename,holdLines);
    if(!res) exit(0);

    int bigval=0;
    for(int i=0;i<holdLines.size();++i){
        for(int j=0;j<holdLines[i].size();++j){
            if(bigval<holdLines[i][j]) bigval=holdLines[i][j];
        }
    }

    adjList.resize(bigval+1);

    unordered_map<int,unordered_set<int>> tmpAdjMatrix;
    for(int i=0;i<holdLines.size();++i){
        int a=holdLines[i][0];
        int b=holdLines[i][1];

        if(tmpAdjMatrix.find(a)==tmpAdjMatrix.end()||tmpAdjMatrix[a].find(b)==tmpAdjMatrix[a].end()){
            tmpAdjMatrix[a].insert(b);tmpAdjMatrix[b].insert(a);
            adjList[a].push_back(b);
            adjList[b].push_back(a);
        }
    }

    for(int i=0;i<adjList.size();++i) adjList[i].shrink_to_fit();

}

#endif