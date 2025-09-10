#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=50;
int n,m,cnt[MN][MN],num[MN],id[MN];
bool vis[MN];
vector<pir> ans;

bool check(){
    for(int s=1;s<(1<<m)-1;s++){
        int cnta=0,cntb=0;
        for(int i=1;i<=m;i++){
            if(s&(1<<(i-1))){
                cnta+=num[i];
            }
        }
        for(int i=1;i<=m;i++){
            for(int j=i;j<=m;j++){
                if((s&(1<<(i-1)))||(s&(1<<(j-1)))){
                    cntb+=cnt[i][j];
                }
            }
        }
        if(cnta>cntb) return 0;
    }
    return 1;
}


signed main(){
    cin>>n;
    int tmp=n;
    while(tmp){
        tmp/=10;
        m++;
    }
    id[1]=1;
    for(int i=2;i<=m;i++) id[i]=id[i-1]*10;
    for(int i=1;i<=m;i++){
        num[i]=id[i+1]-id[i];
    }
    num[m]=n-id[m]+1;
    for(int i=1;i<n;i++){
        string x,y;
        cin>>x>>y;
        int u=x.length(),v=y.length();
        cnt[u][v]++;
        if(u!=v){
            cnt[v][u]++;
        }
    }
    if(!check()) cout<<-1;
    else{
        int tot=0;
        vis[1]=1;
        id[1]+=1;
        num[1]-=1;
        while(tot<n-1){
            for(int i=1;i<=m;i++){
                if(!vis[i]) continue;
                for(int j=1;j<=m;j++){
                    if(!cnt[i][j]||!num[j]) continue;
                    cnt[i][j]--;
                    num[j]--;
                    if(i!=j) cnt[j][i]--;
                    if(check()){
                        ans.push_back(pir(id[i]-1,id[j]));
                        id[j]++;
                        vis[j]=1;
                        tot++;
                    }else{
                        cnt[i][j]++;
                        num[j]++;
                        if(i!=j) cnt[j][i]++;
                    }
                }
            }
        }
    }
    for(auto p:ans) cout<<p.first<<' '<<p.second<<'\n';
    return 0;
}