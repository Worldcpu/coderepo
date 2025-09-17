#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=2.8e5+15;
int n,pre[MN],cnt[MN],mxa,lim,a[MN];
ll ans;

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void initpre(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
    }
}

void merge(int u,int v,ll w){
    if(cnt[u]&&cnt[v]){
        int ru=root(u),rv=root(v);
        if(ru!=rv){
            ans+=w*(cnt[ru]+cnt[rv]-1);
            pre[ru]=rv;
            cnt[rv]+=cnt[ru];
        }
    }
}

signed main(){
    initpre();
    cin>>n;
    cnt[0]=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mxa=max(mxa,a[i]);
        cnt[a[i]]++;
        ans-=a[i];
    }
    int lim=1<<32-__builtin_clz(mxa);
    for(int i=lim-1;i>=0;i--){
        for(int j=i;j;j=(j-1)&i){
            if(cnt[j]&&cnt[i^j]){
                merge(j,i^j,i);
            }
        }
        merge(i,0,i);
    }
    cout<<ans;

    return 0;
}