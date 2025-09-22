#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
int n,m,x[20005],y[20005],z[20005],w[20005],used[20005];
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    string pans = ouf.readString();
    string jans = ans.readString();
    if(pans!=jans)quitf(_wa, "The answer is wrong A!");
    if(pans=="NIE")quitf(_ok, "The answer is correct!");
    int pp=atoi(pans.c_str());
    n=inf.readInt(),m=inf.readInt();
    for(int i=1;i<=m;i++){
        x[i]=inf.readInt(),y[i]=inf.readInt(),z[i]=inf.readInt(),w[i]=inf.readInt();
    }
    int cans=0,now=1;
    while(1){
        int bh=ouf.readInt(),flag=0;
        if(used[bh]||!(x[bh]==now||y[bh]==now))quitf(_wa, "The answer is wrong B!");
        if(x[bh]==now)now=y[bh],used[bh]=1,cans=max(cans,z[bh]);
        else now=x[bh],used[bh]=1,cans=max(cans,w[bh]);
        m--;
        if(!m){
            if(cans!=pp)quitf(_wa, "The answer is wrong C!");
            quitf(_ok, "The answer is correct!");
        }
    }
}
