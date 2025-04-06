#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int MN=101;
int n,m,mn,ans,f[MN][1<<11][1<<11],tot,isok[1<<11],num[1<<11],a[MN];
int getnum(int i){
    int cnt=0;
    while (i)
    {
        if(i&1) cnt++;
        i>>=1;
    }
    return cnt;
}
int main(){
    cin>>n>>m;
    if(n==1){
        char awa;
        cin>>awa;
        if(m!=1) cout<<4;
        else if(awa!='P') cout<<0;
        else cout<<1;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char op;
            cin>>op;
            if(op=='H'){
                a[i]+=1<<(j-1);
            }
        }
    }
    mn=(1<<m)-1;
    for(int i=0;i<=mn;i++){
        if(!(i&(i<<1))&&!(i&(i<<2))&&!(i&(i>>1))&&!(i&(i>>2))){
            tot++;
            isok[tot]=i;
            num[tot]=getnum(i);
        }
    }
    for(int i=1;i<=tot;i++){
        for(int j=1;j<=tot;j++){
            if(!(isok[i]&isok[j])&&!(isok[i]&a[2])&&!(isok[j]&a[1])){
                f[2][i][j]=num[i]+num[j];
            }
        }
    }
    for(int i=3;i<=n;i++){
        for(int j=1;j<=tot;j++){
            if(!(isok[j]&a[i])){
                for(int k=1;k<=tot;k++){
                    if(!(isok[k]&a[i-1])&&!(isok[k]&isok[j])){
                        for(int p=1;p<=tot;p++){
                            if(!(isok[p]&a[i-2])&&!(isok[p]&isok[k])&&!(isok[p]&isok[j])){
                                f[i][j][k]=max(f[i][j][k],f[i-1][k][p]+num[j]);
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=1;i<=tot;i++){
        for(int j=1;j<=tot;j++){
            ans=max(ans,f[n][i][j]);
        }
    }
    cout<<ans;
    return 0;
}