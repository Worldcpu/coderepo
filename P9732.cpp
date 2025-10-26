#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15,MV=1e9,INF=1e18;
int n,K,c[MN],s[MN],rt[MN],sumc[MN],ans,p[MN];
vector<pir> pos[MN];
multiset<int> st;

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson,cnt,sum;
    }t[MN*50];
    int tot;

    void pushup(int p){
        t[p].cnt=t[ls].cnt+t[rs].cnt;
        t[p].sum=t[ls].sum+t[rs].sum;
    }

    void modify(int &p,int lst,int l,int r,int pos){
        p=++tot;
        t[p]=t[lst];
        if(l==r){
            t[p].cnt++;
            t[p].sum+=pos;
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) modify(t[p].lson,t[lst].lson,l,mid,pos);
        else modify(t[p].rson,t[lst].rson,mid+1,r,pos);
        pushup(p);
    }

    int querykthmx(int x,int y,int l,int r,int k){
        if(l==r){
            return l;
        }
        int mid=(l+r)>>1;
        if(k<=t[t[y].rson].cnt-t[t[x].rson].cnt) return querykthmx(t[x].rson,t[y].rson,mid+1,r,k);
        else return querykthmx(t[x].lson,t[y].lson,l,mid,k-(t[t[y].rson].cnt-t[t[x].rson].cnt));
    }

    int querykth(int x,int y,int l,int r,int k){
        if(l==r){
            return k*l;
        }
        int mid=(l+r)>>1;
        if(k<=t[t[y].rson].cnt-t[t[x].rson].cnt) return querykth(t[x].rson,t[y].rson,mid+1,r,k);
        else return querykth(t[x].lson,t[y].lson,l,mid,k-(t[t[y].rson].cnt-t[t[x].rson].cnt))+(t[t[y].rson].sum-t[t[x].rson].sum);
    }
}sg; 

namespace FZ{
    int f[MN];

    int calc(int l,int r){
        if(r-l+1<K) return -INF;
        int ret=sg.querykth(rt[l-1],rt[r],1,MV,K);
        return ret-sumc[r]+sumc[l-1];
    }

    void solve(int l,int r,int kl,int kr){
        if(l>r) return;
        int mid=(l+r)>>1,k=kl,w=-INF;
        for(int i=min(kr,mid-K+1);i>=kl;i--){
            if(calc(i,mid)>w){
                w=calc(i,mid);
                k=i;
            }
            f[mid]=k;
        }
        if(l<mid) solve(l,mid-1,kl,k);
        if(r>mid) solve(mid+1,r,k,kr);
    }

}

void add(int l,int r){
    int ret=sg.querykthmx(rt[l-1],rt[r],1,MV,K);
    pos[l].push_back(pir(ret,1));
    pos[r+1].push_back(pir(ret,-1));
}

signed main(){
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        sumc[i]=sumc[i-1]+c[i];
    }
    for(int i=1;i<=n;i++){
        cin>>s[i];
        sg.modify(rt[i],rt[i-1],1,MV,s[i]);
    }
    FZ::solve(K,n,1,n);   
    ans=-INF;
    for(int i=K;i<=n;i++){
        ans=max(ans,FZ::calc(FZ::f[i],i));
    }
    cout<<ans<<'\n';

    FZ::f[0]=1;   
    for(int i=K,lst=0;i<=n;i++){
        if(FZ::calc(FZ::f[i],i)==ans){
            add(FZ::f[i],i);
            for(int j=FZ::f[lst];j<FZ::f[i];j++){
                if(FZ::calc(j,i)==ans) add(j,i);
            }
            lst=i;
        }       
    }
    for(int i=1;i<=n;i++){
        for(auto p:pos[i]){
            if(p.second==1){
                st.insert(p.first);
            }else st.erase(st.lower_bound(p.first));
        }
        if(st.size()&&s[i]>=(*st.begin())){
            cout<<1;
        }else cout<<0;
    }
    
    return 0;
}