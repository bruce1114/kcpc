#ifndef LCTCPP
#define LCTCPP
#include<vector>
using namespace std;

// #define ch_cache

struct lct{
    vector<bool> rev;
    vector<int> fa;

	#ifdef ch_cache
	vector<int> ch;
	#else
    vector<int> ch[2]; //cache
	#endif

    vector<int> val,mIn;
	vector<pair<int,int> > edgeSave;
	int edgeNode;
	int regularNode;

    void init(int n){
		regularNode=n;
		edgeNode=0;
        int m=n-1;
		int arraysize=n+m+1;
        rev.resize(arraysize,false);
        fa.resize(arraysize,0);

		#ifdef ch_cache
		ch.resize(arraysize<<1,0);
		#else
        ch[0].resize(arraysize,0);
        ch[1].resize(arraysize,0);
		#endif

        val.resize(arraysize);
		mIn.resize(arraysize);
		edgeSave.resize(m+1);
        for(int i=0;i<arraysize;++i) mIn[i]=i;
    }

    inline bool dir(int x){

		#ifdef ch_cache
		return (x==ch[fa[x]<<1]);
		#else
        return (x==ch[1][fa[x]]);
		#endif
    }

    inline bool isRoot(int x){
		#ifdef ch_cache
		return (x!=ch[(fa[x]<<1)-1]&&x!=ch[fa[x]<<1]);
		#else
        return (x!=ch[0][fa[x]]&&x!=ch[1][fa[x]]);
		#endif
    }

	inline void pushUp(int x) {
		mIn[x] = x;
		#ifdef ch_cache
		if(ch[(x<<1)-1]!=0 && val[mIn[ch[(x<<1)-1]]] < val[mIn[x]]) mIn[x] = mIn[ch[(x<<1)-1]];
		if(ch[x<<1]!=0 && val[mIn[ch[x<<1]]] < val[mIn[x]]) mIn[x] = mIn[ch[x<<1]];
		#else
		if(ch[0][x]!=0 && val[mIn[ch[0][x]]] < val[mIn[x]]) mIn[x] = mIn[ch[0][x]];
		if(ch[1][x]!=0 && val[mIn[ch[1][x]]] < val[mIn[x]]) mIn[x] = mIn[ch[1][x]];
		#endif
	}

	inline void pushDown(int x) { // todo
		if(rev[x]) {
			#ifdef ch_cache
			if(ch[(x<<1)-1]!=0) swap(ch[((ch[(x<<1)-1])<<1)-1],ch[(ch[(x<<1)-1])<<1]), rev[ch[(x<<1)-1]] = rev[ch[(x<<1)-1]]^1;
			if(ch[(x<<1)]!=0) swap(ch[((ch[x<<1])<<1)-1],ch[(ch[x<<1])<<1]), rev[(ch[x<<1])] = rev[(ch[x<<1])]^1;
			#else
			if(ch[0][x]!=0) swap(ch[0][ch[0][x]],ch[1][ch[0][x]]), rev[ch[0][x]] = rev[ch[0][x]]^1;
			if(ch[1][x]!=0) swap(ch[0][ch[1][x]],ch[1][ch[1][x]]), rev[ch[1][x]] = rev[ch[1][x]]^1;
			#endif
			rev[x] = 0;
		}
	}

	void update(int x) {
		if(!isRoot(x)) update(fa[x]);
		pushDown(x);
	}

	inline void rotate(int x) {
		#ifdef ch_cache
		int y = fa[x],z = fa[y],d = dir(x),w = ch[(x<<1)-d];
		if(!isRoot(y)) ch[(z<<1)-(1-dir(y))] = x;
		ch[(y<<1)-(1-d)] = w,ch[(x<<1)-d] = y;
		fa[y] = x,fa[x] = z;
		if(w!=0) fa[w] = y;
		pushUp(y);
		#else
		int y = fa[x],z = fa[y],d = dir(x),w = ch[d^1][x];
		if(!isRoot(y)) ch[dir(y)][z] = x;
		ch[d][y] = w,ch[d^1][x] = y;
		fa[y] = x,fa[x] = z;
		if(w!=0) fa[w] = y;
		pushUp(y);
		#endif
	}

	inline void splay(int x) {
		update(x);
		while(!isRoot(x)) {
			int y = fa[x],z = fa[y];
			if(!isRoot(y))
				#ifdef ch_cache
				rotate(((ch[(y<<1)-1] == x) ^ (ch[(z<<1)-1] == y)) ? x : y);
				#else
				rotate(((ch[0][y] == x) ^ (ch[0][z] == y)) ? x : y);
				#endif
			rotate(x);
		}
		pushUp(x);
	}

	inline void access(int x) {
		for(int p = 0;x!=0;p = x,x = fa[x])
		#ifdef ch_cache
			splay(x),ch[x<<1] = p,pushUp(x);
		#else
			splay(x),ch[1][x] = p,pushUp(x);
		#endif
	}

	inline void MakeRoot(int x) {
		access(x),splay(x);
		#ifdef ch_cache
		swap(ch[(x<<1)-1],ch[x<<1]);
		#else
		swap(ch[0][x],ch[1][x]);
		#endif
		rev[x]=rev[x]^1;
	}

	inline int FindRoot(int x) {
		access(x),splay(x);
		#ifdef ch_cache
		while(ch[(x<<1)-1]!=0) pushDown(x),x = ch[(x<<1)-1];
		#else
		while(ch[0][x]!=0) pushDown(x),x = ch[0][x];
		#endif
		splay(x);
		return x;
	}

	inline void split(int x,int y) {
		MakeRoot(x),access(y),splay(y);
	}

	inline void link(int x,int y) {
		MakeRoot(x); fa[x] = y;
	}

	inline void cut(int x,int y){
		//no need
	}

	void getTreeEdges(vector<pair<int,int> >& edges){
		edges.assign(edgeSave.begin()+1,edgeSave.begin()+edgeNode+1);
		for(int i=0;i<edges.size();++i){
			edges[i].first--;
			edges[i].second--;
		}
	}

	ll getByte(){
		ll totalByte=0;
		totalByte+=rev.size();
		totalByte+=fa.size()*4;
		#ifdef ch_cache
		totalByte+=ch.size()*4;
		#else
		totalByte+=ch[0].size()*8;
		#endif
		totalByte+=val.size()*4+mIn.size()*4;
		totalByte+=edgeSave.size()*8;
		return totalByte;
	}
};

#endif