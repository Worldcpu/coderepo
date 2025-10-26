#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],mxl,mxr,suf[MN],pre[MN],ret,npos,ans;
vector<pir> vct;


void init(){
    for(int i=1;i<=n;i++){
        suf[i]=pre[i]=a[i]=0;
    }
    mxl=mxr=npos=ret=ans=0;
    vct.clear();
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        char x;
        cin>>x;
        a[i]=x-'0';
        ans+=a[i];
    }
    ans=min(ans,n-ans);
    for(int r=1,l=1,flag=0;r<=n+1;r++){
        if(a[r]==1){
            if(!flag){
                flag=1;
                l=r;
            }
        }else{
            if(flag){
                flag=0;
                if((!mxr&&!mxl)||mxr-mxl+1<(r-1)-l+1){
                    mxr=r-1;
                    mxl=l;
                }
                vct.push_back(pir(l,r-1));
            }
        }
    }
    for(int i=mxr+1;i<=n;i++){
        pre[i]=pre[i-1]+(!a[i]);
    }
    for(int i=mxl-1;i>=1;i--){
        suf[i]=suf[i+1]+(!a[i]);
    }
    for(int i=0;i<vct.size();i++){
        auto p=vct[i];
        if(p.first==mxl&&p.second==mxr){
            npos=i;
            break;
        }
    }
    int sufans=0,preans=0;
    for(int i=npos-1;i>=0;i--){
        auto p=vct[i];
        if(p.second-p.first+1>suf[p.second]){
            sufans=suf[p.second];
        }else{
            ret+=p.second-p.first+1;
        }
    }
    for(int i=npos+1;i<vct.size();i++){
        auto p=vct[i];
        if(p.second-p.first+1>pre[p.second]){
            preans=pre[p.second];
        }else{
            ret+=p.second-p.first+1;
        }
    }
    ans=min(ret+sufans+preans,ans);
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}