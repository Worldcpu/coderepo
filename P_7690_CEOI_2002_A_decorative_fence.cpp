#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MK=120,MN=35;
ll T,f[MN][MN][2];
ll n,c;
bool vis[MN];

void init(){
    f[1][1][0]=f[1][1][1]=1;
    for(int i=2;i<=20;i++){
        for(int j=1;j<=i;j++){
            for(int p=1;p<j;p++){
                f[i][j][1]+=f[i-1][p][0];
            }
            for(int p=j;p<i;p++){
                f[i][j][0]+=f[i-1][p][1];
            }
        }
    }
}

void solve(){
    ll lst,k;
    cin>>n>>c;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        if(f[n][i][1]>=c){
            lst=i;
            k=1;
            break;
        }else c-=f[n][i][1];
        if(f[n][i][0]>=c){
            lst=i;
            k=0;
            break;
        }else c-=f[n][i][0];
    }
    cout<<lst<<" ";
    vis[lst]=1;
    for(int i=2;i<=n;i++){
        k^=1;
        int rnk=0;
        for(int j=1;j<=n;j++){
            if(vis[j]) continue;
            rnk++;
            if(k==0&&j<lst||k==1&&j>lst){
                if(f[n-i+1][rnk][k]>=c){
                    lst=j;
                    break;
                }else c-=f[n-i+1][rnk][k];
            }
        }
        vis[lst]=1;
        cout<<lst<<" ";
    }
    cout<<'\n';
}

int main(){
    init();
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}