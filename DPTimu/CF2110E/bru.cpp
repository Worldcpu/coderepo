/*
 * @Author: jianhe
 * @Date: 2025-09-14 19:39:09
 * @LastEditTime: 2025-09-14 21:06:33
 */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lb(x) lower_bound(tmp+1,tmp+tot+1,x)-tmp
#define pb push_back
#define fi first
#define se second
const ll N=8e5+10;
ll T,n,v[N],p[N],fa[N],tmp[N],tot,nxt[N];
vector<pair<ll,ll> > e[N];stack<ll> ans;bool vis[N],vis2[N];
ll getfa(ll x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
void hb(ll x,ll y){x=getfa(x),y=getfa(y);if(x!=y) fa[x]=y;}
void dfs(ll x){
    for(int i=nxt[x];i<e[x].size();i=nxt[x]){
        nxt[x]=i+1;
        if(!vis[e[x][i].se]) vis[e[x][i].se]=1,dfs(e[x][i].fi),ans.push(e[x][i].se);// 欧拉路径中点会遍历多次，而答案中只要记录一次边的编号就行
    }
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=tot*2;i++) e[i].clear(),nxt[i]=vis2[i]=0;tot=0;
        for(int i=1;i<=n;i++) cin>>v[i]>>p[i],tmp[++tot]=v[i],tmp[++tot]=p[i],vis[i]=0;// 离散化，其实分开写就不用判下面的 vis2 了
        sort(tmp+1,tmp+tot+1);tot=unique(tmp+1,tmp+tot+1)-tmp-1;
        for(int i=1;i<=n;i++) v[i]=lb(v[i]),p[i]=lb(p[i])+tot,vis2[v[i]]=vis2[p[i]]=1;
        for(int i=1;i<=tot*2;i++) fa[i]=i;bool ok=1;ll pp=0;
        for(int i=1;i<=n;i++) hb(v[i],p[i]),e[v[i]].pb({p[i],i}),e[p[i]].pb({v[i],i});
        for(int i=1;i<=tot*2;i++) if(vis2[i]) pp=i;
        for(int i=1;i<=tot*2;i++) if(vis2[i]&&getfa(i)!=getfa(pp)){cout<<"No\n";ok=0;break;}// 图不连通
        if(!ok) continue;ll ct=0;
        for(int i=1;i<=tot*2;i++) if(e[i].size()&1) ct++,pp=i;// 奇度点
        if(ct>2){cout<<"No\n";continue;}
        dfs(pp);cout<<"Yes\n";
        while(ans.size()) cout<<ans.top()<<" ",ans.pop();cout<<"\n";
    }
    return 0;
}
