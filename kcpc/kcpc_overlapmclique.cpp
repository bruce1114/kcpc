// #define fasterx
#define fasterconnect
// #define connectCliqueBar
#define testOverlap
#define testOverlapNotop
#define bar
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
    for(int i=0;i<results.size();++i){
        cout<<"kcpc nodes-------"<<endl;
        unordered_set<int> tset;
        for(int j=0;j<results[i].size();++j){
            int c=results[i][j];
            for(int k=0;k<cliques[c].size();++k){
                tset.insert(cliques[c][k]);
            }
        }

        unordered_set<int>::iterator it=tset.begin();
        while(it!=tset.end()){
            cout<<*it<<" ";
            it++;
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

int main(int argc, char *argv[]){
    string filename;
    int kval,wait,nopivotPSize;

    filename=argv[1];
    kval=stoi(argv[2]);
    nopivotPSize=stoi(argv[3]);
    wait=stoi(argv[4]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<nopivotPSize<<endl;

    Graph graph;
    graph.readGraph(filename);

    unf fans;
    vector<vector<int> > cliques;

    struct timeval allstart,allend;
    struct timeval start,end;
    gettimeofday(&allstart,NULL);
    gettimeofday(&start,NULL);
    graph.listConnectMaximalCliques(kval,0,nopivotPSize,false,cliques,fans);
    gettimeofday(&end,NULL);
    cerr<<"list and connect time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    int groupNum=0;
    for(int i=0;i<fans.fa.size();++i){
        if(fans.find(i)==i) groupNum++;
    }
    cerr<<"group num: "<<groupNum<<endl;
    // graph.testGroupOverlap(kval,leastK,cliques,fans);

    gettimeofday(&start,NULL);
    graph.listConnectMcliquesOverlap(kval,nopivotPSize,fans,cliques);
    gettimeofday(&end,NULL);
    cerr<<"overlap time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    groupNum=0;
    for(int i=0;i<fans.fa.size();++i){
        if(fans.find(i)==i) groupNum++;
    }
    cerr<<"group num after overlap: "<<groupNum<<endl;

    gettimeofday(&start,NULL);
    // fans.updateSize(cliques.size());
    finalKcpc(cliques,kval,fans);
    gettimeofday(&end,NULL);
    cerr<<"final kcpc time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

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