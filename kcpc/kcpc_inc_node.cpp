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

int outputKCPCnum(unf& fans){
    int num=0;
    for(int i=0;i<fans.fa.size();++i){
        int father=fans.find(i);
        if(i==father) num++;
    }
    return num;
}

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

vector<vector<int>> node2cliques;
vector<int> nonmaximalList;
vector<int> neighbor;
vector<int> overlap;
vector<int> disabledCliques;
vector<int> disabledMark;

int outputCliquenum(vector<vector<int> >& cliques){
    return cliques.size()-disabledCliques.size();
}


void updateKCPC(unf& fans,vector<vector<int>>& newCliques,vector<vector<int>>& cliques,int adjSize){
    int oldcliquesize=cliques.size();
    for(int i=0;i<newCliques.size();++i){
        cliques.push_back(newCliques[i]);
    }
    node2cliques.resize(adjSize);
    for(int i=oldcliquesize;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2cliques[u].push_back(i);
        }
    }

    fans.updateSize(cliques.size());
    disabledMark.resize(cliques.size());
    for(int i=oldcliquesize;i<cliques.size();++i){
        disabledMark[i]=0;
    }
    overlap.resize(cliques.size(),0);
    neighbor.clear();

    for(int i=oldcliquesize;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int node=cliques[i][j];
            for(int k=0;k<node2cliques[node].size();++k){
                int c2=node2cliques[node][k];
                if(c2>=i||cliques[c2].size()<kval) continue;
                overlap[c2]++;
                if(overlap[c2]>1) continue;
                neighbor.push_back(c2);
            }
        }

        for(int j=0;j<neighbor.size();++j){
            int nei=neighbor[j];
            if(overlap[nei]>=kval-1){
                fans.merge(nei,i);
            }
            if(overlap[nei]==cliques[nei].size()&&disabledMark[nei]!=1){
                disabledCliques.push_back(nei);
                disabledMark[nei]=1;
            }

            overlap[nei]=0;
        }

        neighbor.clear();
    }
}


int main(int argc, char *argv[]){
    string filename;
    

    filename=argv[1];
    kval=stoi(argv[2]);
    nopivotPSize=stoi(argv[3]);
    int addvertexnum=stoi(argv[4]);
    pivotIterate=0;
    wait=stoi(argv[5]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<nopivotPSize<<" "<<addvertexnum<<"%"<<endl;

    Graph graph;
    // vector<vector<int> > leftLines;
    unordered_map<int,vector<int>> leftEdges;
    // graph.readGraphPart(filename,leftLines,postsize);
    int largest;
    graph.readGraphAddVertex(filename,leftEdges,addvertexnum,largest);




    unf fans;
    vector<vector<int> > cliques;

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
    cerr<<"kcpc num: "<<outputKCPCnum(fans)<<endl;
    
    node2cliques.resize(graph.adjList.size());
    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2cliques[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }


    Graph sgraph;
    graph.initUpdate();
    vector<vector<int> > newcliques;
    gettimeofday(&start,NULL);

    int addedNode=0;
    int upperbound=largest-addvertexnum;
    for(int node=upperbound+1;node<=largest;++node){
        if(leftEdges.find(node)==leftEdges.end()||leftEdges[node].size()==0){
            continue;
        }
        addedNode++;
        graph.addNode(node,leftEdges[node]);
        graph.initUpdate();
        graph.findNewMCliqueAddNode(sgraph,node,kval,newcliques);
        updateKCPC(fans,newcliques,cliques,graph.adjList.size());
        //report
        if(wait>0&&addedNode%wait==0){
            gettimeofday(&end,NULL);
            cout<<"clique num: "<<outputCliquenum(cliques)<<" fake clique num: "<<disabledCliques.size()<<" kcpc num: "<<outputKCPCnum(fans)<<endl;
            cout<<"ave time: "<<((end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000)*1.0/(addedNode)<<endl;
        }
        sgraph.clearAdjList();
        graph.prepareNextUpdate();
        newcliques.clear();
    }
    gettimeofday(&end,NULL);

    cerr<<"clique num: "<<outputCliquenum(cliques)<<" fake clique num: "<<disabledCliques.size()<<" kcpc num: "<<outputKCPCnum(fans)<<endl;
    cerr<<"ave time: "<<((end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000)*1.0/(addedNode)<<endl;
    cerr<<"addedNode: "<<addedNode<<endl;

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