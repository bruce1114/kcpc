// #define fasterx
#define fasterconnect
#define newfinal
// #define scalability
#define noscalability
// #define scalabilitye
#define connectnox
// #define connectCliqueBar
// #define testOverlap
// #define testOverlapNotop
// #define testOverlapNobig
#include"../src/graph.cpp"
#include"../src/utils.cpp"
#include<sys/time.h>

void outputKcpc(vector<vector<int> >& results,vector<vector<int> >& cliques){
    for(int i=0;i<results.size();++i){
        cout<<"kcpc-------:"<<endl;
        for(int j=0;j<results[i].size();++j){
            int c=results[i][j];
            for(int k=0;k<cliques[c].size();++k){
                cout<<cliques[c][k]<<" ";
            }
            cout<<endl;
        }
    }
}

void output_kcpc_purenodes(vector<vector<int> >& results,vector<vector<int> >& cliques){
    vector<vector<int> > realresults;
    for(int i=0;i<results.size();++i){
        unordered_set<int> tst;
        for(int j=0;j<results[i].size();++j){
            int c=results[i][j];
            for(int k=0;k<cliques[c].size();++k) tst.insert(cliques[c][k]);
        }

        vector<int> temp;
        unordered_set<int>::iterator it=tst.begin();
        while(it!=tst.end()){
            temp.push_back(*it);
            ++it;
        }
        sort(temp.begin(),temp.end());
        realresults.push_back(temp);
    }
    sort(realresults.begin(),realresults.end());

    for(int i=0;i<realresults.size();++i){
        for(int j=0;j<realresults[i].size();++j){
            cout<<realresults[i][j];
            if(j!=realresults[i].size()-1) cout<<" ";
        }
        cout<<endl;
    }
}

void finalKcpc(vector<vector<int> >& cliques,int kval,unf& fans){
    unordered_map<int,int> groupMap;
    vector<int> clique2group;
    vector<vector<int> > group2clique;
    clique2group.resize(cliques.size());

    int groupNum=0;
    for(int i=0;i<fans.fa.size();++i){
        if(fans.fa[i]==i){
            groupMap[i]=groupNum++;
        }
    }

    cerr<<"group num: "<<groupNum<<endl;

    group2clique.resize(groupNum);
    for(int i=0;i<cliques.size();++i){
        int father=fans.find(i);
        // if(groupMap.find(father)==groupMap.end()) cerr<<"here"<<endl;
        int groupId=groupMap[father];
        group2clique[groupId].push_back(i);
        clique2group[i]=groupId;
    }

    int bignode=-1;
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            if(bignode<u) bignode=u;
        }
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
    for(int i=0;i<node2clique.size();++i){
        int next=node2clique[i].size();
        if(next==0) continue;
        node2cliqueJump[i].resize(next);
        int curGroup=clique2group[node2clique[i][next-1]];
        for(int j=node2clique[i].size()-1;j>=0;--j){
            int c=node2clique[i][j];
            if(clique2group[c]==curGroup) node2cliqueJump[i][j]=next;
            else{
                curGroup=clique2group[c];
                next=j+1;
                node2cliqueJump[i][j]=next;
            }
        }
    }


    //不考虑group顺序
    vector<int> overlap,computed;
    overlap.resize(cliques.size(),0);
    computed.reserve(cliques.size());
    for(int i=0;i<cliques.size();++i){
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

void newFinalKcpc(vector<vector<int> >& cliques,int kval,int adjlistSize,unf& fans){

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

    vector<int> overlapNodes;
    overlapNodes.reserve(adjlistSize);
    for(int i=0;i<adjlistSize;++i){
        if(nodesoverlap[i]>1){
            overlapNodes.push_back(i);
        }
    }
    cerr<<"final overlap nodes: "<<overlapNodes.size()<<endl;

    //找出在overlapnodes中含有至少kval-1个节点的clique
    vector<int> focusCliques;
    vector<int> cliqueFocused;
    cliqueFocused.resize(cliques.size(),0);
    focusCliques.reserve(cliques.size());
    for(int i=0;i<cliques.size();++i){
        int nr=0;
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            if(nodesoverlap[u]>1){
                exchange(cliques[i],j,nr++);
            }
        }
        if(nr>=kval-1){
            focusCliques.push_back(i);
            cliqueFocused[i]=1;
        }
    }

    unordered_map<int,int> groupMap;
    vector<int> clique2group;
    vector<vector<int> > group2clique;
    clique2group.resize(cliques.size());

    int groupNum=0;
    for(int i=0;i<focusCliques.size();++i){
        int c=focusCliques[i];
        int father=fans.find(c);
        if(groupMap.find(father)==groupMap.end()){
            groupMap[father]=groupNum++;
        }
    }

    cerr<<"group num: "<<groupNum<<endl;

    group2clique.resize(groupNum);
    for(int i=0;i<focusCliques.size();++i){
        int c=focusCliques[i];
        int father=fans.find(c);
        // if(groupMap.find(father)==groupMap.end()) cerr<<"here"<<endl;
        int groupId=groupMap[father];
        group2clique[groupId].push_back(c);
        clique2group[c]=groupId;
    }

    vector<vector<int> > node2clique;
    node2clique.resize(adjlistSize);
    for(int i=0;i<groupNum;++i){
        for(int j=0;j<group2clique[i].size();++j){
            int c=group2clique[i][j];
            for(int k=0;k<cliques[c].size();++k){
                int u=cliques[c][k];
                if(nodesoverlap[u]<=1) break;
                node2clique[u].push_back(c);
            }
        }
    }

    vector<vector<int> > node2cliqueJump;
    node2cliqueJump.resize(adjlistSize);
    for(int i=0;i<overlapNodes.size();++i){
        int u=overlapNodes[i];
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

    vector<int> overlap,computed;
    overlap.resize(cliques.size(),0);
    computed.reserve(focusCliques.size());
    for(int i=0;i<focusCliques.size();++i){
        int c=focusCliques[i];
        int curGroup=clique2group[c];
        for(int j=0;j<cliques[c].size();++j){
            int u=cliques[c][j];
            if(nodesoverlap[u]<=1) break;
            for(int k=0;k<node2clique[u].size();){
                int nc=node2clique[u][k];
                if(clique2group[nc]==curGroup){
                    k=node2cliqueJump[u][k];
                }
                else if(fans.find(nc)==fans.find(c)){
                    k=node2cliqueJump[u][k];
                     
                }
                else{
                    if(overlap[nc]++ == 0){
                        computed.push_back(nc);
                    }
                    if(overlap[nc]==kval-1){
                        fans.merge(nc,c);
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

int main(int argc, char *argv[]){
    string filename;
    #ifdef noscalability
    int kval,wait,nopivotRatio,nopivotPSize,savePivot;

    filename=argv[1];
    kval=stoi(argv[2]);
    
    nopivotRatio=0;
    savePivot=0;
    nopivotPSize=stoi(argv[3]);
    wait=stoi(argv[4]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<nopivotPSize<<endl;

    Graph graph;
    graph.readGraph(filename);
    #endif

    #ifdef scalability
    filename=argv[1];
    int kval,wait,nopivotRatio,nopivotPSize,savePivot,percent;
    kval=stoi(argv[2]);
    percent=stoi(argv[3]);
    wait=stoi(argv[4]);
    nopivotPSize=stoi(argv[5]);
    savePivot=0;
    nopivotRatio=0;

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<nopivotPSize<<" "<<percent<<endl;


    Graph graph;
    graph.readGraph(filename);
    graph.reduceGraph(percent);
    #endif
    #ifdef scalabilitye
    filename=argv[1];
    int kval,wait,nopivotRatio,nopivotPSize,savePivot,percent;
    kval=stoi(argv[2]);
    percent=stoi(argv[3]);
    wait=stoi(argv[4]);
    nopivotPSize=stoi(argv[5]);
    savePivot=0;
    nopivotRatio=0;

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<nopivotPSize<<" "<<percent<<endl;


    Graph graph;
    graph.readGraphE(filename,percent);
    // graph.reduceGraph(percent);
    #endif

    unf fans;
    vector<vector<int> > cliques;

    struct timeval allstart,allend;
    struct timeval start,end;
    gettimeofday(&allstart,NULL);
    gettimeofday(&start,NULL);
    graph.listConnectMaximalCliques(kval,nopivotRatio,nopivotPSize,savePivot==1,cliques,fans);
    gettimeofday(&end,NULL);
    cerr<<"list and connect time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    #ifdef testOverlap
    graph.testGroupOverlap(kval,cliques,fans);
    #else

    gettimeofday(&start,NULL);
    fans.updateSize(cliques.size());
    #ifdef newfinal
    newFinalKcpc(cliques,kval,graph.adjList.size(),fans);
    #else
    finalKcpc(cliques,kval,fans);
    #endif
    gettimeofday(&end,NULL);
    cerr<<"final kcpc time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;
    #endif

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
    gettimeofday(&allend,NULL);
    cerr<<"clique num: "<<cliques.size()<<endl;
    cerr<<"all time: "<<(allend.tv_sec-allstart.tv_sec)*1000+(allend.tv_usec-allstart.tv_usec)/1000<<endl;
    cerr<<"kcpc num: "<<results.size()<<endl;

    if(wait==0) return 0;
    else if(wait==1) outputKcpc(results,cliques);
    else output_kcpc_purenodes(results,cliques);

}