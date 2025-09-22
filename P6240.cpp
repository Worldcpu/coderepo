#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e4+15,MV=255;
int suf[MN][MV],pre[MN][MV],n,m,ql[MN],qr[MN],qt[MN],h[MN],w[MN],ans[MN];
vector<int> qry;

void solve(int l,int r,const vector<int> &qry){
    if(!qry.size()) return;
    if(l==r){
        for(auto p:qry){
            if(qt[p]>=h[l]) ans[p]=w[l];
            else ans[p]=0;
        }
        return;
    }
    int mid=(l+r)>>1;
    for(int i=l;i<=r;i++){
        memset(suf[i],0,sizeof(suf[i]));
        memset(pre[i],0,sizeof(pre[i]));
    }
    for(int i=mid;i>=l;i--){
        memcpy(suf[i],suf[i+1],sizeof(suf[i]));
        for(int j=h[i];j<MV;j++){
            suf[i][j]=max(suf[i][j],suf[i+1][j-h[i]]+w[i]);
        }
    }
    for(int i=mid+1;i<=r;i++){
        memcpy(pre[i],pre[i-1],sizeof(pre[i]));
        for(int j=h[i];j<MV;j++){
            pre[i][j]=max(pre[i][j],pre[i-1][j-h[i]]+w[i]);
        }
    }
    vector<int> qryl,qryr;
    for(auto p:qry){
        if(qr[p]<=mid) qryl.push_back(p);
        else if(ql[p]>mid) qryr.push_back(p);
        else{
            for(int i=0;i<=qt[p];i++){
                ans[p]=max(ans[p],suf[ql[p]][i]+pre[qr[p]][qt[p]-i]);
            }
        }
    }
    solve(l,mid,qryl);
    solve(mid+1,r,qryr);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=m;i++){
        cin>>ql[i]>>qr[i]>>qt[i];
        qry.push_back(i);
    }
    solve(1,n,qry);
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
    
    
    return 0;
}