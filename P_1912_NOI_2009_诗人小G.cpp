#include<bits/stdc++.h>
#define ld long double
#define ll long long
using namespace std;
const int MN=1e5+15;
struct node{
    int c,l,r;
}q[MN];
int T;
int n,ql,qr,L,P,a[MN],pre[MN];
ld f[MN],s[MN];
string st[MN];
vector<int> ans;

ld qpow(ld a,ll b){
    ld ans=1;
    while (b)
    {
        if(b&1){
            ans*=a;
        }
        b>>=1;
        a*=a;
    }
    return ans;
}

ld clac(int x,int y){
    return f[x]+qpow(fabs(s[y]-s[x]-L-1),P);
}

void insert(int x){
    int pos=n+1;
    while(ql<=qr&&clac(x,q[qr].l)<=clac(q[qr].c,q[qr].l)){
        pos=q[qr--].l;
    }
    if(ql<=qr&&clac(x,q[qr].r)<=clac(q[qr].c,q[qr].r)){
        int l=q[qr].l,r=q[qr].r;
        while(l+1<r){
            int mid=l+r>>1;
            if(clac(x,mid)<=clac(q[qr].c,mid)) r=mid;
            else l=mid;
        }
        q[qr].r=r-1;
        pos=r;
    }
    if(pos!=n+1){
        q[++qr]={x,pos,n};
    }
}

void solve(){
    ans.clear();
    memset(f,0,sizeof(f));
    memset(s,0,sizeof(s));
    memset(pre,0,sizeof(pre));
    cin>>n>>L>>P;
    for(int i=1;i<=n;i++){
        cin>>st[i];
        s[i]=s[i-1]+st[i].length()+1;
    }
    ql=1,qr=0;
    q[++qr]={0,1,n};
    for(int i=1;i<=n;i++){
        while(ql<=qr&&q[ql].r<i) ql++;
        f[i]=clac(q[ql].c,i);
        pre[i]=q[ql].c;
        insert(i);
    }
    if(f[n]>1e18){
        cout<<"Too hard to arrange\n";
    }else{
        cout<<(ll)f[n]<<'\n';
        for(int i=n;i;i=pre[i]){
            ans.push_back(i);
        }
        int cur=ans.size()-1,tmp=0;
        for(int i=1;i<=n;i++){
            if(tmp) cout<<" ";
            cout<<st[i];
            if(i==ans[cur]) cout<<'\n',cur--,tmp=0;
            else tmp++;
        }
    }
    cout<<"--------------------\n";
}

int main(){
    cin>>T;
    while (T--)
    {
        solve();
    }
    
    return 0;
}