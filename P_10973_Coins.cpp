#include<bits/stdc++.h>
using namespace std;
const int MN=2e5+15;
int n,m,ans;
int f[MN],w[MN],tot,num[MN],val[MN],used[MN];
int main(){
    while (1)
    {
        cin>>n>>m;
        if(n==0&&m==0) break;
        memset(f,0,sizeof(f));
        ans=tot=0;
        for(int i=1;i<=n;i++){
            cin>>val[i];
        }
        for(int i=1;i<=n;i++){
            cin>>num[i];
        }
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=num[i];j<<=1){
        //         tot++;
        //         w[tot]=j*val[i];
        //         num[i]-=j;
        //     }
        //     if(num[i]){
        //         tot++;
        //         w[tot]=num[i]*val[i];
        //     }
        // }
        // f[0]=1;
        // for(int i=1;i<=tot;i++){
        //     for(int j=m;j>=w[i];j--){
        //         f[j]|=f[j-w[i]];
        //     }
        // }
        f[0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                used[j]=0;
            }
            for(int j=val[i];j<=m;j++){
                if(!f[j]&&f[j-val[i]]&&used[j-val[i]]<num[i]){
                    f[j]=1;
                    used[j]=used[j-val[i]]+1;
                }
            }
        }
        for(int i=1;i<=m;i++){
            ans+=f[i];
        }
        cout<<ans<<'\n';
    }
    
    return 0;
}