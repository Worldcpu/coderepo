#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,t,s,e,tot;
struct Matrix{
    int mt[MN][MN];
    Matrix operator*(const Matrix &x)const{
        Matrix ans;
        memset(ans.mt,0x3f,sizeof(ans.mt));
        for(int k=1;k<=tot;k++){
            for(int i=1;i<=tot;i++){
                for(int j=1;j<=tot;j++){
                    ans.mt[i][j]=min(ans.mt[i][j],mt[i][k]+x.mt[k][j]);
                }
            }
        }
        return ans;
    }
}dis,ans;
unordered_map<int,int> ump;

Matrix ksm(){
    n--;
    ans=dis;
    while(n){
        if(n&1){
            ans=ans*dis;
        }
        dis=dis*dis;
        n>>=1;
    }
    return ans;
}

int main(){
    cin>>n>>t>>s>>e;
    memset(dis.mt,0x3f,sizeof(dis.mt));
    for(int i=1;i<=t;i++){
        int u,v,w;
        cin>>w>>u>>v;
        if(!ump[u]) ump[u]=++tot;
        if(!ump[v]) ump[v]=++tot;
        dis.mt[ump[u]][ump[v]]=dis.mt[ump[v]][ump[u]]=w;
    }
    cout<<ksm().mt[ump[s]][ump[e]];
    
    return 0;
}