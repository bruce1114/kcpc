// #define fasterx
#define fasterconnect
// #define connectCliqueBar
#define testOverlap
#define testOverlapNotop
// #define pivotLike
#define newfinal
#define checkcommongroup
// #define counttree
// #define nooverlap
// #define scalability
#define noscalability
// #define scalabilitye
// #define nocolor

// #define onlyP
#define oriNew


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


int kval,wait,nopivotPSize,pivotIterate;

vector<vector<int> > cliques;
vector<vector<int>> node2cliques;
vector<int> nonmaximalList;
vector<int> neighbor;
vector<int> overlap;
vector<int> disabledCliques;
vector<int> disabledMark;
vector<int> deletedCliques;
vector<int> deletedMark;
int totalDeletedNum;

vector<int> cliqueCommonMark;
vector<bool> vis;
vector<int> que;
// vector<int> commonClique;

void followCliqueSize(){
    overlap.resize(cliques.size(),0);
    deletedMark.resize(cliques.size(),0);
}

int outputKCPCnum(unf& fans){
    int num=0;
    for(int i=0;i<fans.fa.size();++i){
        if(deletedMark[i]==1) continue;
        int father=fans.find(i);
        if(i==father) num++;
    }
    return num;
}

void delNodeClique(int node){
    deletedMark.resize(cliques.size(),0);
    deletedCliques.clear();
    
    for(int i=0;i<node2cliques[node].size();++i){
        int c=node2cliques[node][i];
        if(deletedMark[c]==1) continue;
        deletedCliques.push_back(c);
    }

    for(int i=0;i<deletedCliques.size();++i){
        int c=deletedCliques[i];
        deletedMark[c]=1;
    }

    totalDeletedNum+=deletedCliques.size();
}

void delEdgeClique(int a,int b){
    cliqueCommonMark.resize(cliques.size(),0);
    deletedMark.resize(cliques.size(),0);
    deletedCliques.clear();

    int smalllistid=a;
    int largelistid=b;
    if(node2cliques[b].size()<node2cliques[a].size()){
        smalllistid=b;
        largelistid=a;
    }
    //find common
    for(int i=0;i<node2cliques[smalllistid].size();++i){
        int c=node2cliques[smalllistid][i];
        if(deletedMark[c]==1) continue;

        cliqueCommonMark[c]=1;
    }
    for(int i=0;i<node2cliques[largelistid].size();++i){
        int c=node2cliques[largelistid][i];
        if(deletedMark[c]==1) continue;
        if(cliqueCommonMark[c]==1) deletedCliques.push_back(c);
    }

    //clear cliqueCommonMark
    for(int i=0;i<node2cliques[smalllistid].size();++i){
        int c=node2cliques[smalllistid][i];
        if(deletedMark[c]==1) continue;

        cliqueCommonMark[c]=0;
    }

    //delete common
    for(int i=0;i<deletedCliques.size();++i){
        int c=deletedCliques[i];
        deletedMark[c]=1;
    }

    totalDeletedNum+=deletedCliques.size();

}

void resignConnect(unf& fans,vector<int>& newcomponent){
    if(newcomponent.size()==0) return;

    fans.fa[newcomponent[0]]=newcomponent[0];
    if(newcomponent.size()==1) return;

    for(int i=1;i<newcomponent.size();++i){
        fans.fa[newcomponent[i]]=newcomponent[0];
    }
}

vector<int> neighborMark;
bool checkOnlyNeighbor(vector<int>& neiCliqueList){
    if(neiCliqueList.size()<=1) return true;

    overlap.resize(cliques.size(),0);
    que.resize(cliques.size());
    vis.resize(cliques.size(),false);
    for(int i=0;i<neiCliqueList.size();++i) vis[neiCliqueList[i]]=false;

    int startc=neiCliqueList[0];
    que[0]=startc;
    int quesize=1;
    vis[startc]=true;

    for(int l=0;l<quesize;++l){
        int c1=que[l];

        for(int j=0;j<cliques[c1].size();++j){
            int node=cliques[c1][j];
            for(int k=0;k<node2cliques[node].size();++k){
                int c2=node2cliques[node][k];
                if(deletedMark[c2]==1||neighborMark[c2]==0||c2==c1||vis[c2]==true||cliques[c2].size()<kval) continue;
                overlap[c2]++;
                if(overlap[c2]>1) continue;
                neighbor.push_back(c2);
            }
        }

        for(int j=0;j<neighbor.size();++j){
            int nei=neighbor[j];
            if(overlap[nei]>=kval-1){
                // que.push_back(nei);
                que[quesize++]=nei;
                // singleRes.push_back(nei);
                vis[nei]=true;
            }
            overlap[nei]=0;
        }

        neighbor.clear();
    }

    return (quesize==neiCliqueList.size());
}

bool checkNeighborAndMore(vector<int>& neiCliqueList){
    if(neiCliqueList.size()<=1) return true;

    overlap.resize(cliques.size(),0);
    que.resize(cliques.size());
    vis.resize(cliques.size(),false);
    for(int i=0;i<neiCliqueList.size();++i) vis[neiCliqueList[i]]=false;

    int startc=neiCliqueList[0];
    que[0]=startc;
    int quesize=1;
    vis[startc]=true;

    for(int l=0;l<quesize;++l){
        int c1=que[l];

        for(int j=0;j<cliques[c1].size();++j){
            int node=cliques[c1][j];
            for(int k=0;k<node2cliques[node].size();++k){
                int c2=node2cliques[node][k];
                if(deletedMark[c2]==1||neighborMark[c2]==0||c2==c1||vis[c2]==true||cliques[c2].size()<kval) continue;
                overlap[c2]++;
                if(overlap[c2]>1) continue;
                neighbor.push_back(c2);
            }
        }

        for(int j=0;j<neighbor.size();++j){
            int nei=neighbor[j];
            if(overlap[nei]>=kval-1){
                // que.push_back(nei);
                que[quesize++]=nei;
                // singleRes.push_back(nei);
                vis[nei]=true;
            }
            overlap[nei]=0;
        }

        neighbor.clear();
    }

    return (quesize==neiCliqueList.size());
}

vector<int> relatedCliqueMark;

void updateKCPC(unf& fans,vector<vector<int> >& cliques,int da,int db,int nodeSize){
    vector<int> neiCliqueList;
    // vector<int> tempneiCliqueList;
    

    //handle deleted cliques
    overlap.resize(cliques.size(),0);
    que.resize(cliques.size());
    vis.resize(cliques.size(),false);
    neighborMark.resize(cliques.size(),0);
    for(int i=0;i<cliques.size();++i) vis[i]=false;
    for(int i=0;i<deletedCliques.size();++i){
        int c=deletedCliques[i];
        // int kcpcNo=fans.find(c);

        for(int j=0;j<cliques[c].size();++j){
            int node=cliques[c][j];
            for(int k=0;k<node2cliques[node].size();++k){
                int c2=node2cliques[node][k];
                if(deletedMark[c2]==1) continue;

                if(c2==c||cliques[c2].size()<kval) continue;
                overlap[c2]++;
                if(overlap[c2]>1) continue;
                neighbor.push_back(c2);
            }
        }
        for(int j=0;j<neighbor.size();++j){
            int nei=neighbor[j];
            if(overlap[nei]>=kval-1){
                neiCliqueList.push_back(nei);
                // tempneiCliqueList.push_back(nei);
            }
            overlap[nei]=0;
        }
        neighbor.clear();

        // for(int i=0;i<tempneiCliqueList.size();++i) neighborMark[tempneiCliqueList[i]]=1;
        // cout<<"neighbor of single clique: "<<tempneiCliqueList.size()<<" "<<checkOnlyNeighbor(tempneiCliqueList)<<endl;
        // for(int i=0;i<tempneiCliqueList.size();++i) neighborMark[tempneiCliqueList[i]]=0;
        // tempneiCliqueList.clear();
    }
    // cout<<"neighbor of delete: "<<neiCliqueList.size()<<endl;

    int trueNeighborNum=0;
    for(int i=0;i<neiCliqueList.size();++i){
        int nc=neiCliqueList[i];
        if(neighborMark[nc]==0){
            trueNeighborNum++;
            neighborMark[nc]=1;
        }
    }

    int visitedNum=0;
    bool faststop=false;
    bool localcompute=false;
    int neiFront=0;

    if(neiCliqueList.size()>0){
        int c=neiCliqueList[0];
        que[0]=c;
        int quesize=1;
        vis[c]=true;
        trueNeighborNum--;
        neiFront=0;
        for(int l=0;l<quesize;++l){
            int c1=que[l];

            for(int j=0;j<cliques[c1].size();++j){
                int node=cliques[c1][j];
                for(int k=0;k<node2cliques[node].size();++k){
                    int c2=node2cliques[node][k];
                    if(deletedMark[c2]==1||c2==c1||vis[c2]==true||cliques[c2].size()<kval) continue;
                    overlap[c2]++;
                    if(overlap[c2]>1) continue;
                    neighbor.push_back(c2);
                }
            }

            for(int j=0;j<neighbor.size();++j){
                int nei=neighbor[j];
                if(overlap[nei]>=kval-1){
                    // que.push_back(nei);
                    que[quesize++]=nei;
                    if(neighborMark[nei]==1){
                        trueNeighborNum--;
                        if(neiFront<=l) neiFront=l;
                        int temp=que[neiFront+1];
                        que[neiFront+1]=nei;
                        que[quesize-1]=temp;
                        neiFront++;
                    }
                    // singleRes.push_back(nei);
                    vis[nei]=true;
                }
                overlap[nei]=0;
            }

            neighbor.clear();
            if(trueNeighborNum==0){
                faststop=true;
                break;
            }
            if(quesize>=22000){
                break;
            }
        }

        if(faststop==true){
            for(int i=0;i<deletedCliques.size();++i){
                int dc=deletedCliques[i];
                if(fans.find(dc)==dc){
                    if(neiCliqueList.size()>0){
                        int nc=neiCliqueList[0];
                        fans.fa[nc]=nc;
                        fans.fa[dc]=nc;
                    }
                    break;
                }
            }
        }else{
            vector<int> relatedCliques;
            // relatedCliqueMark.resize(cliques.size(),0);
            for(int i=0;i<cliques.size();++i){
                if(deletedMark[i]==1) continue;
                for(int j=0;j<deletedCliques.size();++j){
                    if(fans.find(i)==fans.find(deletedCliques[j])){
                        relatedCliques.push_back(i);
                        break;
                    }
                }
            }

            //make subgraph
            Graph sgraph;
            sgraph.localCliqueMark.resize(cliques.size(),0);
            sgraph.adjList.resize(nodeSize);
            for(int i=0;i<relatedCliques.size();++i){
                int rc=relatedCliques[i];
                fans.fa[rc]=rc;//clear fans
                // relatedCliqueMark[rc]=1;
                sgraph.localCliqueMark[rc]=1;
                for(int j=0;j<cliques[rc].size()-1;++j){
                    for(int k=j+1;k<cliques[rc].size();++k){
                        sgraph.addEdge(cliques[rc][j],cliques[rc][k]);
                    }
                }
            }

            sgraph.localKCLMCL(kval,cliques,fans);

            cout<<"local"<<endl;

            for(int i=0;i<relatedCliques.size();++i){
                int rc=relatedCliques[i];
                // relatedCliqueMark[rc]=0;
                sgraph.localCliqueMark[rc]=0;
            }
        }
    }


    // for(int i=0;i<neiCliqueList.size();++i){
    //     int c=neiCliqueList[i];
        
    //     if(vis[c]==true||cliques[c].size()<kval) continue;

    //     que[0]=c;
    //     int quesize=1;
    //     vis[c]=true;
    //     if(i==0){
    //         trueNeighborNum--;
    //         neiFront=0;
    //     }
    //     vector<int> singleRes;

    //     for(int l=0;l<quesize;++l){
    //         int c1=que[l];

    //         for(int j=0;j<cliques[c1].size();++j){
    //             int node=cliques[c1][j];
    //             for(int k=0;k<node2cliques[node].size();++k){
    //                 int c2=node2cliques[node][k];
    //                 if(deletedMark[c2]==1||c2==c1||vis[c2]==true||cliques[c2].size()<kval) continue;
    //                 overlap[c2]++;
    //                 if(overlap[c2]>1) continue;
    //                 neighbor.push_back(c2);
    //             }
    //         }

    //         for(int j=0;j<neighbor.size();++j){
    //             int nei=neighbor[j];
    //             if(overlap[nei]>=kval-1){
    //                 // que.push_back(nei);
    //                 que[quesize++]=nei;
    //                 if(i==0&&neighborMark[nei]==1){
    //                     trueNeighborNum--;
    //                     if(neiFront<=l) neiFront=l;
    //                     int temp=que[neiFront+1];
    //                     que[neiFront+1]=nei;
    //                     que[quesize-1]=temp;
    //                     neiFront++;
    //                 }
    //                 // singleRes.push_back(nei);
    //                 vis[nei]=true;
    //             }
    //             overlap[nei]=0;
    //         }

    //         neighbor.clear();
    //         if(i==0&&trueNeighborNum==0){
    //             faststop=true;
    //             break;
    //         }
    //     }
    //     visitedNum+=quesize;
    //     if(faststop==true) break;
    //     singleRes.assign(que.begin(),que.begin()+quesize);
    //     resignConnect(fans,singleRes);
    // }
    // if(faststop==true){
    //     cout<<"fast"<<endl;
    //     for(int i=0;i<deletedCliques.size();++i){
    //         int dc=deletedCliques[i];
    //         if(fans.find(dc)==dc){
    //             if(neiCliqueList.size()>0){
    //                 int nc=neiCliqueList[0];
    //                 fans.fa[nc]=nc;
    //                 fans.fa[dc]=nc;
    //             }
    //             break;
    //         }
    //     }
    // }
    // cout<<"visited num: "<<visitedNum<<endl;

    //clear
    for(int i=0;i<neiCliqueList.size();++i){
        int nc=neiCliqueList[i];
        neighborMark[nc]=0;
    }

    //check neighbors
    // vector<int> fatherSet;
    // if(neiCliqueList.size()>0){
    //     int egfather=fans.find(neiCliqueList[0]);
    //     for(int i=1;i<neiCliqueList.size();++i){
    //         int c=neiCliqueList[i];
    //         if(fans.find(c)!=egfather){
    //             cout<<"here"<<endl;
    //             break;
    //         }
    //     }
    // }

    //handle new, small cliques
    vector<vector<int>> candNewClique;
    for(int i=0;i<deletedCliques.size();++i){
        int c=deletedCliques[i];
        vector<int> subc;
        for(int j=0;j<cliques[c].size();++j){
            int node=cliques[c][j];
            if(node!=da){
                subc.push_back(node);
            }
        }
        if(subc.size()>=kval) candNewClique.push_back(subc);
    }

    for(int i=0;i<candNewClique.size();++i){
        bool ismaximal=true;
        for(int j=0;j<candNewClique[i].size();++j){
            int node=candNewClique[i][j];
            for(int k=0;k<node2cliques[node].size();++k){
                int c2=node2cliques[node][k];
                if(deletedMark[c2]==1||cliques[c2].size()<kval) continue;
                overlap[c2]++;
                if(overlap[c2]==candNewClique[i].size()){//not maximal
                    ismaximal=false;
                    break;
                }
                if(overlap[c2]>1) continue;
                neighbor.push_back(c2);
            }
            if(ismaximal==false) break;
        }
        if(ismaximal==false){
            for(int j=0;j<neighbor.size();++j){
                int nei=neighbor[j];
                overlap[nei]=0;
            }
        }else{
            cliques.push_back(candNewClique[i]);//new maximal clique
            fans.updateSize(cliques.size());//update union-find set size
            followCliqueSize();
            for(int j=0;j<neighbor.size();++j){
                int nei=neighbor[j];
                if(overlap[nei]>=kval-1){
                    fans.merge(nei,cliques.size()-1);
                }
                overlap[nei]=0;
            }
            //prepare node2cliques
            for(int j=0;j<candNewClique[i].size();++j){
                int node=candNewClique[i][j];
                node2cliques[node].push_back(cliques.size()-1);
            }
        }

        neighbor.clear();
    }
}

int outputCliquenum(vector<vector<int> >& cliques){
    return cliques.size()-disabledCliques.size();
}


// void updateKCPC(unf& fans,vector<vector<int>>& newCliques,vector<vector<int>>& cliques,int adjSize){
//     int oldcliquesize=cliques.size();
//     for(int i=0;i<newCliques.size();++i){
//         cliques.push_back(newCliques[i]);
//     }
//     node2cliques.resize(adjSize);
//     for(int i=oldcliquesize;i<cliques.size();++i){
//         for(int j=0;j<cliques[i].size();++j){
//             int u=cliques[i][j];
//             node2cliques[u].push_back(i);
//         }
//     }

//     fans.updateSize(cliques.size());
//     disabledMark.resize(cliques.size());
//     for(int i=oldcliquesize;i<cliques.size();++i){
//         disabledMark[i]=0;
//     }
//     overlap.resize(cliques.size(),0);
//     neighbor.clear();

//     for(int i=oldcliquesize;i<cliques.size();++i){
//         for(int j=0;j<cliques[i].size();++j){
//             int node=cliques[i][j];
//             for(int k=0;k<node2cliques[node].size();++k){
//                 int c2=node2cliques[node][k];
//                 if(c2>=i||cliques[c2].size()<kval) continue;
//                 overlap[c2]++;
//                 if(overlap[c2]>1) continue;
//                 neighbor.push_back(c2);
//             }
//         }

//         for(int j=0;j<neighbor.size();++j){
//             int nei=neighbor[j];
//             if(overlap[nei]>=kval-1){
//                 fans.merge(nei,i);
//             }
//             if(overlap[nei]==cliques[nei].size()&&disabledMark[nei]!=1){
//                 disabledCliques.push_back(nei);
//                 disabledMark[nei]=1;
//             }

//             overlap[nei]=0;
//         }

//         neighbor.clear();
//     }
// }


int main(int argc, char *argv[]){
    string filename;
    

    filename=argv[1];
    kval=stoi(argv[2]);
    nopivotPSize=stoi(argv[3]);
    int delvertexnum=stoi(argv[4]);
    pivotIterate=0;
    wait=stoi(argv[5]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<nopivotPSize<<" "<<delvertexnum<<"%"<<endl;

    Graph graph;
    // vector<vector<int> > delLines;
    unordered_set<int> delNodes;
    // graph.readGraphAllReturnPart(filename,delLines,postsize);
    graph.readGraphDelVertex(filename,delNodes,delvertexnum);



    unf fans;
    

    struct timeval allstart,allend;
    struct timeval start,end;
    gettimeofday(&allstart,NULL);
    gettimeofday(&start,NULL);

    int nopivotRatio=0;
    int savePivot=0;
    graph.listConnectMaximalCliques(kval,nopivotRatio,nopivotPSize,savePivot==1,cliques,fans);

    gettimeofday(&end,NULL);
    cerr<<"list and connect time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

    #ifdef testOverlap
    #ifdef checkcommongroup
    graph.visGroup.resize(cliques.size(),false);
    graph.visGroups.reserve(cliques.size());
    #endif

    int groupNum=0;
    for(int i=0;i<fans.fa.size();++i){
        if(fans.find(i)==i) groupNum++;
    }
    cerr<<"group num: "<<groupNum<<endl;
    graph.testGroupOverlap(kval,cliques,fans);


    #endif

    gettimeofday(&allend,NULL);
    cerr<<"clique num: "<<cliques.size()<<endl;
    cerr<<"all time: "<<(allend.tv_sec-allstart.tv_sec)*1000+(allend.tv_usec-allstart.tv_usec)/1000<<endl;
    followCliqueSize();
    cerr<<"kcpc num: "<<outputKCPCnum(fans)<<endl;
    
    node2cliques.resize(graph.adjList.size());
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2cliques[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }


    // Graph sgraph;
    // graph.initUpdate();
    // vector<vector<int> > newcliques;
    totalDeletedNum=0;
    gettimeofday(&start,NULL);
    unordered_set<int>::iterator it=delNodes.begin();
    cerr<<"delNodes size: "<<delNodes.size()<<endl;

    // vector<int> delNodeslist;
    // while(it!=delNodes.end()){
    //     int node=*it;
    //     delNodeslist.push_back(node);
    //     it++;
    // }
    // sort(delNodeslist.begin(),delNodeslist.end());

    int itnum=0;
    // for(int i=delNodeslist.size()-1;i>=0;--i){
    //     int node=delNodeslist[i];
    //     delNodeClique(node);
    //     updateKCPC(fans,cliques,node,node,graph.adjList.size());
    //     itnum++;
    //     if(wait>0&&itnum%wait==0){
    //         gettimeofday(&end,NULL);
    //         cout<<"clique num: "<<cliques.size()-totalDeletedNum<<" deleted clique num: "<<totalDeletedNum<<" kcpc num: "<<outputKCPCnum(fans)<<endl;
    //         cout<<"ave time: "<<((end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000)*1.0/(itnum)<<endl;
    //     }
    // }
    while(it!=delNodes.end()){
        int node=*it;
        delNodeClique(node);
        updateKCPC(fans,cliques,node,node,graph.adjList.size());
        //report
        itnum++;
        if(wait>0&&itnum%wait==0){
            gettimeofday(&end,NULL);
            cout<<"clique num: "<<cliques.size()-totalDeletedNum<<" deleted clique num: "<<totalDeletedNum<<" kcpc num: "<<outputKCPCnum(fans)<<endl;
            cout<<"ave time: "<<((end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000)*1.0/(itnum)<<endl;
        }
        it++;
    }
    gettimeofday(&end,NULL);
    cerr<<"clique num: "<<cliques.size()-totalDeletedNum<<" deleted clique num: "<<totalDeletedNum<<" kcpc num: "<<outputKCPCnum(fans)<<endl;
    cerr<<"ave time: "<<((end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000)*1.0/(itnum)<<endl;
    cerr<<"deletedNum: "<<itnum<<endl;

    // unordered_map<int,vector<int> > cliqueGroup;
    
    // for(int i=0;i<fans.fa.size();++i){
    //     int father=fans.find(i);
    //     cliqueGroup[father].push_back(i);
    // }

    // vector<vector<int> > results;
    // unordered_map<int,vector<int> >::iterator it=cliqueGroup.begin();
    // while(it!=cliqueGroup.end()){
    //     results.push_back(it->second);
    //     it++;
    // }
    // gettimeofday(&allend,NULL);
    // cerr<<"clique num: "<<cliques.size()<<endl;
    // cerr<<"all time: "<<(allend.tv_sec-allstart.tv_sec)*1000+(allend.tv_usec-allstart.tv_usec)/1000<<endl;
    // cerr<<"kcpc num: "<<results.size()<<endl;

    // if(wait==0) return 0;
    // else if(wait==1) outputKcpc(results,cliques);
    // else output_kcpc_purenodes(results,cliques);


}