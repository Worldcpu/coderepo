#include<bits/stdc++.h>
using namespace std;
const int MN=150,MM=1e5+15;
int n,m;
int v[MN],w[MN],c[MN];
int q[MM],f[MM];
int clac(int i,int u,int k){
    return f[u+k*v[i]]-k*w[i];
}
int main(){
    memset(f,128,sizeof(f));
    f[0]=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i]>>c[i];
        for(int u=0;u<v[i];u++){
            int l=1,r=0;
            int maxp=(m-u)/v[i];
            for(int k=maxp-1;k>=max(maxp-c[i],0);k--){
                while(l<=r&&clac(i,u,q[r])<=clac(i,u,k)) r--;
                q[++r]=k;
            }
            for(int k=maxp;k>=0;k--){
                while(l<=r&&q[l]>k-1)l++;
                if(l<=r) f[u+k*v[i]]=max(f[u+k*v[i]],clac(i,u,q[l])+k*w[i]);
                if(k-c[i]-1>=0){
                    while(l<=r&&clac(i,u,q[r])<=clac(i,u,k-c[i]-1))r--;
                    q[++r]=k-c[i]-1;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        ans=max(ans,f[i]);
    }
    cout<<ans;
    return 0;
}