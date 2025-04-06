#include<bits/stdc++.h>
using namespace std;
const int MN=5125,INF=1e9;
int f[MN][MN],p[MN][MN],n,s[MN];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        s[i]+=s[i-1];
        p[i][i]=i;
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            f[l][r]=INF;
            for(int k=p[l][r-1];k<=p[l+1][r];k++){
                int t=f[l][k]+f[k+1][r]+s[r]-s[l-1];
                if(f[l][r]>t){
                    f[l][r]=t;
                    p[l][r]=k;
                }
            }
        }

    }
    cout<<f[1][n];
    return 0;
}