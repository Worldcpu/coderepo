#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,tot,f[MN][MN][MN],a[MN][8],mx[MN],cnt[MN],p[4],c[4];


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i][0];
        if(a[i][0]%1111111==0){
            i--,n--;
            continue;
        }
        for(int j=1;j<=6;j++){
            a[i][j]=(a[i][j-1]%1000000)*10+a[i][j-1]/1000000;
            if(a[i][mx[i]]<a[i][j]) mx[i]=j;
        }
    }
    for(int i=1;i<=n;i++){
        cnt[(mx[i]-mx[i-1]+7)%7]++;
    }
    p[1]=abs(cnt[1]-cnt[6]),p[2]=abs(cnt[2]-cnt[5]),p[3]=abs(cnt[3]-cnt[4]);
    c[1]=cnt[1]>cnt[6]?1:6,c[2]=cnt[2]>cnt[5]?2:5,c[3]=cnt[3]>cnt[4]?3:4;
    tot=max(cnt[1],cnt[6])+max(cnt[2],cnt[5])+max(cnt[3],cnt[4]);
    for(int i=0;i<=p[1];i++){
        for(int j=0;j<=p[2];j++){
            for(int k=0;k<=p[3];k++){
                if((i*c[1]+j*c[2]+k*c[3])%7==0) f[i][j][k]++;
                f[i+1][j][k]=max(f[i+1][j][k],f[i][j][k]);
                f[i][j+1][k]=max(f[i][j+1][k],f[i][j][k]);
                f[i][j][k+1]=max(f[i][j][k+1],f[i][j][k]);
            }
        }
    }
    cout<<tot+1-f[p[1]][p[2]][p[3]]<<'\n';
    return 0;
}

