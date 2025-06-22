#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7;
int f[MN],tmp[MN],a[MN],id[MN],pw[MN],val[MN],n,ans,m,cur,cnt;

void init(){
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*3;
}

int getS(int x,int pos){
    for(int i=1;i<=pos;i++) x/=3;
    return x%3;
}

signed main(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        cin>>a[i];
        a[i]--;
        id[a[i]]=i-1;
    }
    for(int i=1;i<m;i++){
        if(a[i]>a[i+1]){
            cout<<0;
            return 0;
        }
    }
    f[0]=1;
    for(int i=0;i<pw[n];i++){
        if(!f[i]) continue;
        cur=cnt=0;
        for(int j=0;j<n;j++){
            val[j]=getS(i,j);
            if(val[j]) cnt++;
            if(val[j]==1){
                tmp[cur++]=j;
            }
        }
        if(cnt==n){
            ans+=f[i];
            continue;
        }
        for(int j=0;j<n;j++){
            if(val[j]) continue;
            if(id[j]&&!val[a[id[j]]]) continue;
            int pos=0;
            while(tmp[pos]<j&&pos<cur) pos++;
            if(pos==m) continue;
            int to=i+pw[j];
            if(pos<cur){
                to+=pw[tmp[pos]];
            }
            f[to]+=f[i];
        }
    }
    cout<<ans;
    return 0;
}
