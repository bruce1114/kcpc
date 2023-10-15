// #define fasterx
#define directleaf
#define fasterconnect
#define fasterformer
// #define connectCliqueBar
#include"../src/graph.cpp"
#include"../src/utils.cpp"
#include<sys/time.h>

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

int main(int argc, char *argv[]){
    string filename;
    int kval,wait,nopivotPSize,degeneracyPercent;

    filename=argv[1];
    kval=stoi(argv[2]);
    nopivotPSize=stoi(argv[3]);
    degeneracyPercent=stoi(argv[4]);
    wait=stoi(argv[5]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<nopivotPSize<<" "<<degeneracyPercent<<endl;

    Graph graph;
    graph.readGraph(filename);

    unf fans;
    vector<vector<int> > cliques;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    graph.kcpc_combine_temp_nox(kval,nopivotPSize,degeneracyPercent,cliques,fans);
    gettimeofday(&end,NULL);
    cerr<<"all time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;

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
    cerr<<"kcpc num: "<<results.size()<<endl;
    if(wait==0) return 0;
    output_kcpc_purenodes(results,cliques);
    return 0;
}