#include<bits/stdc++.h>
using namespace std;
constexpr int MN=20;
int n,tot,a[MN],b[MN],c[MN];

int h(){
    int ret=0;
    for(int i=1;i<=n;i++){
        if(abs(a[i]-a[i+1])!=1) ret++;
    }
    return ret;
}

bool dfs(int pre,int dep,int mxdep){
    if(dep==mxdep){
        if(!h()) return 1;
    }
    bool flag=0;
    for(int i=1;i<=n;i++){
        if(i==pre) continue;
        for(int j=1;j<=n;j++) c[i]=a[i];
        int l=1,r=i;
        while(l!=r){
            swap(a[l],a[r]);
            l++,r--;
        }
        if(dep+h()<=mxdep) flag|=dfs(i,dep+1,mxdep);
        for(int j=1;j<=n;j++) a[i]=c[i];
    }
    return flag;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
    }
    a[n+1]=n+1;
    for(int i=0;;i++){
        if(dfs(0,0,i)){
            cout<<i;
            break;
        }
    }
    return 0;
}
