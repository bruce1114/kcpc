// #define scalability
// #define noscalability
#define scalabilitye

#include"../src/utils.cpp"
#include"../src/graph.cpp"
#include<unordered_set>
#include<algorithm>
#include<sys/time.h>

// #define kcpc_bar

void kcpc(int kval,vector<vector<int> >& cliques,vector<vector<int> >& node2cliques,vector<vector<int> >& results){
    int cliqueNum=cliques.size();

    vector<bool> vis;
    vector<int> neighbor;
    vector<int> overlap;
    vector<int> que;
    neighbor.reserve(cliqueNum);
    overlap.resize(cliqueNum,0);
    que.resize(cliqueNum);

    vis.resize(cliqueNum,false);

    ll totalbyte=0;
    totalbyte+=cliqueNum;
    totalbyte+=cliqueNum*12;
    // cerr<<"kcpc mem: "<<totalbyte<<" byte"<<endl;

    #ifdef kcpc_bar
    int barseg=cliqueNum/1000;
    cerr<<"total "<<cliqueNum<<" cliques"<<endl;
    #endif

    for(int i=0;i<cliqueNum;++i){
        if(vis[i]==true||cliques[i].size()<kval) continue;

        #ifdef kcpc_bar
        cerr<<i<<endl;
        #endif

        // que.push_back(i);
        que[0]=i;
        int quesize=1;
        vis[i]=true;
        vector<int> singleRes;
        // singleRes.push_back(i);
        for(int l=0;l<quesize;++l){
            int c1=que[l];

            for(int j=0;j<cliques[c1].size();++j){
                int node=cliques[c1][j];
                for(int k=0;k<node2cliques[node].size();++k){
                    int c2=node2cliques[node][k];
                    if(c2==c1||vis[c2]==true||cliques[c2].size()<kval) continue;
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
        singleRes.assign(que.begin(),que.begin()+quesize);
        results.push_back(singleRes);
    }
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

int main(int argc, char *argv[]){
    string filename="../../dataset/linux.txt";
    int nodeArraySize=-1;

    #ifdef noscalability
    filename=argv[1];
    int kval,wait;
    kval=stoi(argv[2]);
    wait=stoi(argv[3]);

    cerr<<argv[0]<<" "<<filename<<" "<<kval<<endl;


    vector<vector<int>> cliques;
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


    vector<vector<int>> cliques;
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


    vector<vector<int>> cliques;
    Graph graph;
    graph.readGraphE(filename,percent);
    // graph.reduceGraph(percent);
    #endif

    struct timeval allstart,allend;
    struct timeval start,end;
    gettimeofday(&allstart,NULL);
    gettimeofday(&start,NULL);
    graph.listMaximalCliques(cliques,kval);
    gettimeofday(&end,NULL);
    cerr<<"list clique time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;
    
    // readFile(filename,cliques);
    gettimeofday(&start,NULL);

    for(int i=0;i<cliques.size();++i){
        for(int j=0;j<cliques[i].size();++j){
            if(nodeArraySize<cliques[i][j]) nodeArraySize=cliques[i][j];
        }
    }
    nodeArraySize++;

    vector<vector<int>> node2cliques;
    node2cliques.resize(nodeArraySize);
    int node2cliqueSize=0;
    for(int i=0;i<cliques.size();++i){
        node2cliqueSize+=cliques[i].size();
        for(int j=0;j<cliques[i].size();++j){
            int u=cliques[i][j];
            node2cliques[u].push_back(i);
            // node2cliquesCount[u]++;
        }
    }

    vector<vector<int> > results;

    kcpc(kval,cliques,node2cliques,results);
    gettimeofday(&end,NULL);
    cerr<<"kcpc time: "<<(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000<<endl;
    gettimeofday(&allend,NULL);

    // cerr<<"kcpc done"<<endl;

    cerr<<"clique num: "<<cliques.size()<<endl;
    // cerr<<"node2clique size: "<<node2cliqueSize<<endl;
    // cerr<<"node2clique: "<<node2cliqueSize*4<<" byte"<<endl;
    cerr<<"kcpc num: "<<results.size()<<endl;
    
    cerr<<"all time: "<<(allend.tv_sec-allstart.tv_sec)*1000+(allend.tv_usec-allstart.tv_usec)/1000<<endl;

    if(wait==1) outputKcpc(results,cliques);
    return 0;

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

    output(realresults);
}