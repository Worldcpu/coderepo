#include "../../testlib.h"
#include <bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
struct Edge{int u,v;}e[MN];
int n,vis[MN],K,ret[MN],q;

namespace DSU{
    int pree[MN];
    void initpre(){for(int i=1;i<=n;i++) pree[i]=i;}
    int root(int x){return pree[x]==x?x:pree[x]=root(pree[x]);}
    void unite(int x,int y){x=root(x),y=root(y);if(x!=y)pree[x]=y;}
} using namespace DSU;

bool check(int x,int y){return abs(x-y)==1;}

bool getans(InStream &in,bool isans){
    bool flag=0;
    string st=in.readToken();

    if(st=="Yes") flag=1;
    else if(st=="No") flag=0;
    else{
        if(isans) quitf(_fail,"Jury's answer format incorrect: expected 'Yes' or 'No', got '%s'",st.c_str());
        else quitf(_wa,"Participant's answer format incorrect: expected 'Yes' or 'No', got '%s'",st.c_str());
    }
    if(!flag) return 0;

    for(int i=1;i<=n;i++){
        ret[i]=in.readInt(-1000000000,1000000000);
        if(vis[i]!=-1 && ret[i]!=vis[i]){
            if(isans)
                quitf(_fail,"Jury's answer disagrees with fixed constraint: node %d expected %d but got %d",i,vis[i],ret[i]);
            else
                quitf(_wa,"Participant's answer disagrees with fixed constraint: node %d expected %d but got %d",i,vis[i],ret[i]);
        }
    }

    for(int i=1;i<n;i++){
        if(!check(ret[e[i].u],ret[e[i].v])){
            if(isans)
                quitf(_fail,"Jury's answer invalid: edge (%d,%d) violates adjacency constraint",e[i].u,e[i].v);
            else
                quitf(_wa,"Participant's answer invalid: edge (%d,%d) violates adjacency constraint",e[i].u,e[i].v);
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
    registerValidation(argc,argv);
    n=inf.readInt(1,1e5,"n");
    inf.readSpace();
    q=inf.readInt(1,1e5)
    initpre();
    for(int i=1;i<=n;i++) vis[i]=-1;

    return 0;
}
