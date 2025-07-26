#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
struct DPNode{
    int ret,cnt;

    DPNode(int rett=0,int cntt=0){
        ret=rett,cnt=cntt;
    }

    friend bool operator<(DPNode x,DPNode y){
        if(x.ret==-1) return 0;
        if(y.ret==-1) return 1;
        return x.ret==y.ret?x.cnt<y.cnt:x.ret<y.ret;
    }

    friend DPNode operator+(DPNode x,DPNode y){
        return (DPNode){x.ret+y.ret,x.cnt+y.cnt};
    }

}f[MN],g[MN];
int n,K,rt,top,dtot,cmid,s[MN],st[MN],q[MN],pre1[MN],pre2[MN],arcpre[MN],ql,qr,ed[MN];
vector<int> adj[MN];

int c2(int x){
    return x*(x-1)/2;
}

int geted(int x,int y,int len){
    int dx=pre1[y]-pre1[x];
    int bx=g[x].ret-pre2[x],by=g[y].ret-pre2[y];
    if(bx>=by) return 0;
    int ret,up=2*(by-bx)-dx*dx+dx,dw=2*dx;
    if(up%dw==0&&g[x].cnt>g[y].cnt){
        ret=up/dw;
    }else ret=up/dw+1;
    ret=max(ret,0ll);
    if(ret>pre1[len]-pre1[y]) return MN;
    else return arcpre[ret+pre1[y]];
}

namespace Tree{
    int sum[MN];

    void dfs(int u,int pre){
        sum[u]=0;
        int cnt=0;
        for(auto v:adj[u]){
            if(v==pre) continue;
            if(v<=n) cnt++;
            else{
                dfs(v,u);
                sum[u]+=sum[v];
            }
        }
        sum[u]+=c2(cnt);
    }

    void check(int u){
        for(auto v:adj[u]){
            if(v>n) check(v);
        }
        int len=adj[u].size()*2;
        pre1[0]=pre2[0]=0;
        f[u]=DPNode(-1,0);
        for(int i=0;i<adj[u].size();i++){
            if(adj[u][i]<=n){
                pre1[i*2+1]=pre1[i*2+2]=pre1[i*2]+1;
                pre2[i*2+1]=pre2[i*2+2]=pre2[i*2];
                arcpre[pre1[i*2+1]]=i*2+1;
            }else{
                pre1[i*2+1]=pre1[i*2+2]=pre1[i*2];
                pre2[i*2+1]=pre2[i*2+2]=pre2[i*2]+sum[adj[u][i]];
            }
        }
        g[0]=DPNode(0,0);
        ql=qr=0;
        q[0]=0;
        for(int i=1;i<len;i++){
            while(ql<qr&&ed[ql]<=i) ql++;
            DPNode now;
            if(!(i&1)){
                now=DPNode(cmid,1);
            }else{
                int pos=(i-1)>>1;
                if(adj[u][pos]<=n) continue;
                if(f[adj[u][pos]].ret==-1) continue;
                now=f[adj[u][pos]];
            }
            g[i]=DPNode(-1,0);
            g[i]=g[q[ql]]+now+(DPNode){pre2[i-1]-pre2[q[ql]]+c2(pre1[i-1]-pre1[q[ql]]),0};
            f[u]=min(f[u],g[i]+DPNode(pre2[len]-pre2[i]+c2(pre1[len]-pre1[i]),0));
if(pre1[q[qr]]==pre1[i]){
    int cur=g[i].ret-pre2[i],lst=g[q[qr]].ret-pre2[q[qr]];
    if(cur<lst||(lst==cur&&g[i].cnt<=g[q[qr]].cnt)) {
        qr--;
    } else {
        continue;
    }
}
            while(ql<qr){
                int x=q[qr-1],y=q[qr],now=i;
                if(geted(x,now,len)<=ed[qr-1]){
                    qr--;
                    continue;
                }
                if(geted(y,now,len)<=ed[qr-1]){
                    qr--;
                    continue;
                }
                break;
            }
            q[++qr]=i;
            if(ql<qr) ed[qr-1]=geted(q[qr-1],q[qr],len);
        }
        if(u==rt){
            f[u]=min(f[u],DPNode(sum[u],0));
        }
    }
}using namespace Tree;

signed main(){
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    cin>>n>>K;
    K--;
    n++;
    dtot=n;
    for(int i=2;i<=n;i++){
        char qwq;
        cin>>qwq;
        s[i]=s[i-1]+(qwq=='('?1:-1);
    }
    for(int i=1;i<=n;i++){
        int tmp=top;
        while(tmp&&s[st[tmp]]>s[i]) tmp--;
        if(!tmp){
            s[++dtot]=s[i];
            for(int j=1;j<top;j++){
                adj[st[j]].push_back(st[j+1]);
            }
            if(top) adj[dtot].push_back(st[1]);
            adj[dtot].push_back(i);
            st[top=1]=dtot;
        }else{
            for(int j=tmp+1;j<top;j++){
                adj[st[j]].push_back(st[j+1]);
            }
            if(s[i]==s[st[tmp]]){
                if(tmp+1<=top){
                    adj[st[tmp]].push_back(st[tmp+1]);
                }
                adj[st[tmp]].push_back(i);
                top=tmp;
            }else{
                s[++dtot]=s[i];
                if(tmp+1<=top){
                    adj[dtot].push_back(st[tmp+1]);
                }
                adj[dtot].push_back(i);
                top=tmp;
                st[++top]=dtot;
            }
        }
    }
    while(top>1){
        adj[st[top-1]].push_back(st[top]);
        top--;
    }
    rt=st[1];
    dfs(rt,0);
    int l=0,r=sum[rt];
    while(l<r){
        cmid=(l+r)>>1;
        check(rt);
        if(f[rt].cnt<=K){
            r=cmid;
        } else l=cmid+1;  
    }
    
    cmid=l;
    check(rt);
    cout<<f[rt].ret-cmid*K;
    return 0;
}