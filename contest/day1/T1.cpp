#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e5+15;
int ans,f[2][MN][2],tot,tptot,n,m,awa,s[MN],w[MN],t[MN],val[MN<<2],in[MN],nxt[MN],tpsort[MN];
pir tsk[MN<<1];

int main(){
    freopen("bot.in","r",stdin);
    freopen("bot.out","w",stdout);
    cin>>n>>m>>awa;
    for(int i=1;i<=n+m;i++){
        cin>>s[i]>>t[i];
        tsk[++tot]=pir(s[i],i<<1);
        tsk[++tot]=pir(t[i],i<<1|1);
    }
    sort(tsk+1,tsk+1+tot);
    for(int i=1;i<tot;i++){
        if((tsk[i].second&1)&&(tsk[i+1].second&1)){
            val[tsk[i+1].second>>1]+=tsk[i+1].first-tsk[i].first;
        }else if((tsk[i].second&1)){
            ans+=tsk[i+1].first-tsk[i].first;
        }else if((tsk[i+1].second&1)){
            if((tsk[i+1].second>>1)==(tsk[i].second>>1)){
                val[tsk[i+1].second>>1]+=tsk[i+1].first-tsk[i].first;
            }else{
                w[tsk[i+1].second>>1]=tsk[i+1].first-tsk[i].first;
                in[tsk[i].second>>1]++;
                nxt[tsk[i+1].second>>1]=tsk[i].second>>1;
            }
        }else{
            val[tsk[i].second>>1]+=tsk[i+1].first-tsk[i].first;
        }
    }
    for(int i=1;i<=n+m;i++){
        if(!in[i]){
            for(int j=i;j;j=nxt[j]){
                tpsort[++tptot]=j;
            }
        }
    }
    memset(f,128,sizeof(f));
    f[(n+m+1)&1][0][0]=0;
    if(n<m){
        for(int i=tptot;i>=1;i--){
            for(int j=0;j<=n;j++){
                int cur=i&1,pre=(i+1)&1;
                f[cur][j][0]=max(f[pre][j][0],f[pre][j][1]);
                if(j){
                    f[cur][j][1]=max(f[pre][j-1][0],f[pre][j-1][1])+val[tpsort[i]];
                    if(nxt[tpsort[i]])
                        f[cur][j][1]=max(f[cur][j][1],f[pre][j-1][1]+val[tpsort[i]]+w[tpsort[i]]);
                }
            }
        }
        cout<<tsk[tot].first-tsk[1].first-ans-max(f[1][n][0],f[1][n][1]);
    }else{
        for(int i=tptot;i>=1;i--){
            for(int j=0;j<=m;j++){
                int cur=i&1,pre=(i+1)&1;
                if(j) f[cur][j][0]=max(f[pre][j-1][0],f[pre][j-1][1]);
                f[cur][j][1]=max(f[pre][j][0],f[pre][j][1])+val[tpsort[i]];
                if(nxt[tpsort[i]])
                    f[cur][j][1]=max(f[cur][j][1],f[pre][j][1]+val[tpsort[i]]+w[tpsort[i]]);
            }
        }
        cout<<tsk[tot].first-tsk[1].first-ans-max(f[1][m][0],f[1][m][1]);
    }
    return 0;
}