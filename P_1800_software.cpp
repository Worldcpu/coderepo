#include<bits/stdc++.h>
using namespace std;
const int MN=101;
int n,m;
int f[MN][MN],d1[MN],d2[MN];

bool check(int d){
    memset(f,128,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=j;k++){
                int last=d-d1[i]*(j-k);
                if(last<0) continue;
                f[i][j]=max(f[i][j],f[i-1][k]+(last/d2[i]));
            }
        }
    }
    return f[n][m]>=m;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>d1[i]>>d2[i];
    }
    int l=0,r=1e5+15;
    while (l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    cout<<l;
    
    return 0;
}