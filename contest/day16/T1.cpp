#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e5+15,BL=500;
int n,q,B,T,p[MN],pos[MN];
ll a[MN],lastans;

struct BL1{
    int L,R;
    ll sum;
    vector<int> vct;

    void build(){
        vct.clear();
        sum=0;
        for(int i=L;i<=R;i++) vct.push_back(p[i]);
        sort(vct.begin(),vct.end());
    }

    void add(int l,int r,ll x){
        auto it1=lower_bound(vct.begin(),vct.end(),l);
        auto it2=upper_bound(vct.begin(),vct.end(),r);
        if(it1==vct.end()||it1==it2) return;
        ll cnt=it2-it1;
        sum+=cnt*x;
    }
}b1[BL];

struct BL2{
    ll add;
    int L,R;  
}b2[BL];



void add(int fl,int fr,ll x){
    if(pos[fl]==pos[fr]){
        for(int i=fl;i<=fr;i++) a[i]+=x;
        return;
    }
    for(int i=fl;i<=b2[pos[fl]].R;i++) a[i]+=x;
    for(int i=b2[pos[fr]].L;i<=fr;i++) a[i]+=x;
    for(int i=pos[fl]+1;i<=pos[fr]-1;i++) b2[i].add+=x;
}

ll query_one(int x){
    return a[x]+b2[pos[x]].add;
}

void initbl(){
    B=max(1,(int)sqrt(n*log(max(2.0,(double)n)))); 
    T=(n+B-1)/B; 
    for(int i=1;i<=T;i++){
        b1[i].L=(i-1)*B+1;
        b1[i].R=min(n,i*B);
        b2[i].L=b1[i].L;
        b2[i].R=b1[i].R;
        b1[i].vct.clear();
        b1[i].sum=0;
        b2[i].add=0;
    }
    for(int i=1;i<=n;i++) pos[i]=(i-1)/B+1;
    for(int i=1;i<=T;i++) b1[i].build();
}

ll query_range(int fl,int fr){
    ll ret=0;
    if(pos[fl]==pos[fr]){
        for(int i=fl;i<=fr;i++) ret+=query_one(p[i]);
        return ret;
    }
    for(int i=fl;i<=b1[pos[fl]].R;i++) ret+=query_one(p[i]);
    for(int i=b1[pos[fr]].L;i<=fr;i++) ret+=query_one(p[i]);
    for(int i=pos[fl]+1;i<=pos[fr]-1;i++) ret+=b1[i].sum;
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>p[i];
    initbl();
    ll ans=0;
    while(q--){
        int op; ll l,r,x;
        cin>>op;
        if(op==1){
            cin>>l>>r>>x;
            l^=ans;
            r^=ans;
            x^=ans;
            add(l,r,x);
            for(int i=1;i<=T;i++) b1[i].add(l,r,x);
        }else{
            cin>>l>>r;
            l^=ans;
            r^=ans;
            cout<<(ans=query_range(l,r))<<'\n';
        }
    }
    return 0;
}
