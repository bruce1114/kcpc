#ifndef UTILSCPP
#define UTILSCPP

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#define ll long long
using namespace std;

bool readFile(string filename,vector<vector<int>>& dataLines){
    ifstream fin;
    fin.open(filename,ios::binary);
    if(!fin.is_open()){
        cerr<<"can not open file"<<endl;
        return false;
    }


    ll totalSize=fin.seekg(0,ios::end).tellg();
    char *buf=new char[totalSize+5];

    fin.seekg(0,ios::beg).read(buf,totalSize);
    fin.close();

    bool isWin=false;
    vector<int> holdLine;
    int val=0;
    bool hasVal=false;
    for(ll i=0;i<totalSize;++i){
        switch (buf[i])
        {
        case 9:
        case 32:
            {
                if(hasVal){
                    holdLine.push_back(val);
                    hasVal=false;
                }
                val=0;
            }
        break;
        case 10:
            {
                if(!isWin){
                    if(hasVal){
                        holdLine.push_back(val);
                        hasVal=false;
                    }
                    val=0;
                    dataLines.push_back(holdLine);
                    holdLine.clear();
                }
            }
        break;
        case 13:
            {
                if(hasVal){
                    holdLine.push_back(val);
                    hasVal=false;
                }
                val=0;
                dataLines.push_back(holdLine);
                holdLine.clear();
                isWin=true;
            }
        break;
        default:
            {
                int tval=buf[i]-'0';
                val=val*10+tval;
                hasVal=true;
            }
        break;
        }
    }
    //最后一条边，当不以新行结尾时
    if(holdLine.size()>0){
        if(hasVal){
            holdLine.push_back(val);
            hasVal=false;
        }
        dataLines.push_back(holdLine);
    }

    delete buf;
    // cerr<<(isWin?"win read":"linux read")<<endl;

    for(int i=0;i<dataLines.size();++i){
        dataLines[i].shrink_to_fit();
    }
    return true;
}

inline void exchange(vector<int>& arr,int aIndex,int bIndex){
    int va=arr[aIndex];
    int vb=arr[bIndex];
    arr[aIndex]=vb;
    arr[bIndex]=va;
}

inline void exchange(vector<int>& arr,int aIndex,int bIndex,vector<int>& arrIndex){
    int va=arr[aIndex];
    int vb=arr[bIndex];
    arr[aIndex]=vb;
    arr[bIndex]=va;
    arrIndex[va]=bIndex;
    arrIndex[vb]=aIndex;
}

void output(vector<vector<int> >& v2){
    for(int i=0;i<v2.size();++i){
        for(int j=0;j<v2[i].size();++j){
            cout<<v2[i][j];
            if(j!=v2[i].size()-1) cout<<" ";
        }
        cout<<endl;
    }
}

struct clique{
    vector<int> theNodes;
    
    bool operator == (const clique& b)const{
        if(theNodes.size()==b.theNodes.size()){
            for(int i=0;i<theNodes.size();++i){
                if(theNodes[i]!=b.theNodes[i]) return false;
            }
            return true;
        }
        return false;
    }

    bool operator < (const clique& b)const{
        for(int i=0;i<theNodes.size()&&i<b.theNodes.size();++i){
            if(theNodes[i]!=b.theNodes[i]) return theNodes[i]<b.theNodes[i];
        }
        return theNodes.size()<b.theNodes.size();
    }

    void selfsort(){
        sort(theNodes.begin(),theNodes.end());
    }

    void addsort(int val){
        theNodes.push_back(val);
        for(int i=theNodes.size()-1;i>=1;--i){
            if(theNodes[i]<theNodes[i-1]){
                int temp=theNodes[i];
                theNodes[i]=theNodes[i-1];
                theNodes[i-1]=temp;
            }else{
                break;
            }
        }
    }
};

struct hashClique{
    size_t operator ()(const clique& theclique)const{
        size_t res=0;
        hash<int> hasher=hash<int>();
        for(int i=0;i<theclique.theNodes.size();++i){
            res=res^hasher(theclique.theNodes[i]);
        }
        return res;
    }
};

#endif