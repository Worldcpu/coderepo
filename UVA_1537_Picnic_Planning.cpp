#include<bits/stdc++.h>
#define getid(x) (!ump[x]?ump[x]=++umptot:ump[x])
#define pir pair<int,int>
using namespace std;
constexpr int MN=1314;
struct Edge{
    int u,v,w;
}e[MN];
int pre[MN],n,k,T,umptot,s;
unordered_map<string,int> ump;

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void initpre(){
    for(int i=1;i<=umptot;i++){
        pre[i]=i;
    }
}

bool cmp(Edge x,Edge y){
    if(x.w+k*(x.u==1)==y.w+k*(y.u==1)) return x.u!=1;
    return x.w+k*(x.u==1)<y.w+k*(y.u==1);
}

pir kru(){
    int ans=0,cnt=0;
    initpre();
    sort(e+1,e+1+n,cmp);
    for(int i=1;i<=n;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru==rv) continue;
        pre[rv]=ru;
        ans+=e[i].w;
        if(e[i].u==1){
            cnt++;
            ans+=k;
        }
    }
    //cout<<"K:"<<k<<" "<<ans<<" "<<cnt<<'\n';
    return pir(ans,cnt);
}

void solve(){
    ump.clear();
    umptot=1;
    ump["Park"]=1;
    cin>>n;
    for(int i=1;i<=n;i++){
        string u,v;
        int w;
        cin>>u>>v>>w;
        e[i].u=getid(u);
        e[i].v=getid(v);
        e[i].w=w;
        
        if(e[i].u>e[i].v) swap(e[i].u,e[i].v);
        //cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].w<<'\n';
    }
    cin>>s;
    int l=0,r=1000;
    k=0;
    if(kru().second<=s){
        cout<<"Total miles driven: "<<kru().first<<'\n';
        if(T) cout<<'\n';
        return;
    }
    //cout<<umptot<<'\n';
    while(l+1<r){
        int mid=(l+r)>>1;
        k=mid;
        if(kru().second>s) l=mid;
        else r=mid;
    }
    k=r;
    cout<<"Total miles driven: "<<kru().first-s*k<<'\n';
    if(T) cout<<'\n';
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}