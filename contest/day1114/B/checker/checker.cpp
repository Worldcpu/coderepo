#include "../../../testlib.h"
#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e3+15;
int n,mp1[MN][MN],mp2[MN][MN];

pir checkans(InStream &it){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            mp1[i][j]=it.readInt(1,n);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            mp2[i][j]=it.readInt(1,n);
        }
    }
    if(!it.seekEof()){
        return pir(1,0);
    }

    for(int i=1;i<=n;i++){
        unordered_map<int,int> mp;
        for(int j=1;j<=n;j++){
            int k=mp1[i][j];
            if(mp[k]){
                return pir(2,i);
            }
            mp[k]=1;
        }
    }
}

int main(int argc,char *argv[]){
    registerTestlibCmd(argc,argv);

    n=inf.readInt(1,1e3,"n");

    return 0;
}