#define directleaf
#define fasterformer

// #define mcliquefirst
#define checkcommongroup
// #define counttree
// #define nooverlap
#define noscalability
// #define scalabilitye
// #define scalability
// #define lesscliqueforoverlapnodes
// #define couttree

#include"../src/graph.cpp"
#include"../src/utils.cpp"
#include<sys/time.h>

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

int main(int argc, char *argv[]){

    string filename;
    #ifdef noscalability
    int kval,wait;

    filename=argv[1];
    kval=stoi(argv[2]);
    wait=stoi(argv[3]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<endl;

    Graph graph;
    graph.readGraph(filename);
    #endif

    #ifdef scalability
    filename=argv[1];
    int kval,wait,percent;
    kval=stoi(argv[2]);
    percent=stoi(argv[3]);
    wait=stoi(argv[4]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<percent<<endl;


    Graph graph;
    graph.readGraph(filename);
    graph.reduceGraph(percent);
    #endif

    #ifdef scalabilitye
    filename=argv[1];
    int kval,wait,percent;
    kval=stoi(argv[2]);
    percent=stoi(argv[3]);
    wait=stoi(argv[4]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<" "<<percent<<endl;


    Graph graph;
    graph.readGraphE(filename,percent);
    #endif

    unf fans;
    vector<vector<int> > cliques;

    #ifdef mcliquefirst
    struct timeval start,end;
    gettimeofday(&start,NULL);

    graph.listMaximalCliques(cliques,kval);
    fans.init(cliques.size());

    cerr<<"mclique num: "<<cliques.size()<<endl;

    // vector<vector<int> > node2mclique;
    // node2mclique.resize(graph.adjList.size());
    // for(int i=0;i<cliques.size();++i){
    //     for(int j=0;j<cliques[i].size();++j){
    //         int u=cliques[i][j];
    //         node2mclique[u].push_back(i);
    //         // node2cliquesCount[u]++;
    //     }
    // }

    graph.visGroup.resize(cliques.size(),false);
    graph.visGroups.reserve(cliques.size());

    graph.testGroupOverlap(kval,cliques,fans);

    gettimeofday(&end,NULL);
    cerr<<"all time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;
    

    #else

    struct timeval start,end;
    gettimeofday(&start,NULL);
    graph.listConnectCliques(kval,cliques,fans);
    gettimeofday(&end,NULL);
    cerr<<"all time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;
    cerr<<"kclique num: "<<cliques.size()<<endl;
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
    cerr<<"kcpc num: "<<results.size()<<endl;

    if(wait==0) return 0;

    output_kcpc_purenodes(results,cliques);
    return 0;
}