#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e6+15,INF=1e9;
int n,K,ans,a[MN];

struct Trie{
    int t[MN][2],dtot,end[MN];

    void init(){
        for(int i=0;i<=dtot;i++){
            memset(t[i],0,sizeof(t[i]));
            end[i]=0;
        }
        dtot=1;
    }

    void insert(int x,int pos){
        int p=1;
        for(int i=29;i>=0;i--){
            int k=(x>>i)&1;
            if(!t[p][k]) t[p][k]=++dtot;
            assert(dtot<MN);
            p=t[p][k];
            end[p]=max(end[p],pos); 
        }
    }

    int query(int x){
        int p=1,ret=-1,sum=0;
        for(int i=29;i>=0;i--){
            int kx=(x>>i)&1;
            if(t[p][kx^1]){
                if(sum+(1ll<<i)>=K){
                    ret=max(ret,end[t[p][kx^1]]);
                    p=t[p][kx];
                }else{
                    p=t[p][kx^1];
                    sum+=(1ll<<i);
                }
            }else if(t[p][kx]) p=t[p][kx];
            else break;
        }
        return ret;
    }
}t;

void init(){
    t.init();
    ans=1e9;
}

void solve(){
    cin>>n>>K;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    if(!K){
        cout<<1<<'\n';
        return;
    }
    for(int i=1;i<=n;i++){
        t.insert(a[i],i);
        int ret=t.query(a[i]);
        if(ret==-1) continue;
        ans=min(ans,i-ret+1);
    }    
    if(ans==INF){
        cout<<-1<<'\n';
    }else cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    
    return 0;
}