#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MQ=520;
int n,m,c,len,a[MN],L[MN],R[MN],pos[MN],cntk[MQ][MN],sum[MQ][MN],ans[MQ][MQ],cnt[MN];
bool vis[MN];

void init(){
    len=sqrt(n);
    for(int i=1;i<=len;i++){
        L[i]=R[i-1]+1;
        R[i]=i*len;
    }
    if(R[len]<n){
        R[++len]=n;
        L[len]=R[len-1]+1;
    }
    for(int i=1;i<=len;i++){
        for(int j=i;j<=len;j++){
            if(i!=j) ans[i][j]+=ans[i][j-1];
            for(int k=L[j];k<=R[j];k++){
                if(!(++cnt[a[k]]&1)) ans[i][j]++;
                else if(cnt[a[k]]>1) ans[i][j]--;
            }
        }
        for(int j=1;j<=c;j++) cnt[j]=0;
    }
    for(int i=1;i<=len;i++){
        for(int j=1;j<=c;j++) sum[i][j]=sum[i-1][j];
        for(int j=L[i];j<=R[i];j++){
            sum[i][a[j]]++;
            pos[j]=i;
        }
    }
}

int query(int fl,int fr){
    int ql=pos[fl],qr=pos[fr],ret=0;
    if(qr-ql<=1){
        for(int i=fl;i<=fr;i++){
            if(!(++cnt[a[i]]&1)) ret++;
            else if(cnt[a[i]]>1) ret--;
        }
        for(int i=fl;i<=fr;i++) cnt[a[i]]=0;
        return ret;
    }
    ret+=ans[ql+1][qr-1];
    for(int i=fl;i<=R[ql];i++){
        if(!cnt[a[i]]) cnt[a[i]]+=sum[qr-1][a[i]]-sum[ql][a[i]];
        if(!(++cnt[a[i]]&1)) ret++;
        else if(cnt[a[i]]>1) ret--;
    }
    for(int i=L[qr];i<=fr;i++){
        if(!cnt[a[i]]) cnt[a[i]]+=sum[qr-1][a[i]]-sum[ql][a[i]];
        if(!(++cnt[a[i]]&1)) ret++;
        else if(cnt[a[i]]>1) ret--;
    }
    for(int i=fl;i<=R[ql];i++){
        cnt[a[i]]=0;
    }
    for(int i=L[qr];i<=fr;i++){
        cnt[a[i]]=0;
    }
    return ret;
}

int main(){
    cin>>n>>c>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    init();

    // cerr<<cntk[3][1]<<'\n';
    // for(int i=1;i<=len;i++){
    //     for(int j=i+1;j<=len;j++){
    //         cerr<<"I: "<<i<<" "<<L[i]<<" "<<R[i]<<'\n';
    //         cerr<<"j: "<<j<<" "<<L[j]<<" "<<R[j]<<'\n';
    //         cerr<<i<<" "<<j<<" "<<ans[i][j]<<'\n';
    //     }
    // }
    int l,r,awa=0;
    while(m--){
        cin>>l>>r;
        l=(l+awa)%n+1;
        r=(r+awa)%n+1;
        if(l>r) swap(l,r);
        awa=query(l,r);
        cout<<awa<<'\n';
    }
    return 0;
}