#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=16;
const int fx[4]={0,0,1,-1},fy[4]={1,-1,0,0};
int n,m,lims,mp[MN][MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

bool check(int st){
    int r=1,c=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            mp[i][j]=0;
        }
    }
    while(st){
        int x=st%3;
        st/=3;
        mp[r][c++]=x;
        if(c==m+1){
            r++;
            c=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int cnt=0;
            for(int k=0;k<4;k++){
                int nx=i+fx[k],ny=j+fy[k];
                if(nx>=1&&nx<=n&&ny>=1&&ny<=m){
                    if(mp[nx][ny]==mp[i][j]) cnt++;
                }
            }
            if(cnt!=mp[i][j]) return 0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<mp[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 1;
}

signed main(){
    cin>>n>>m;
    lims=ksm(3,n*m);
    for(int i=0;i<lims;i++){
        if(check(i)){
            break;
        }
    }
    return 0;
}