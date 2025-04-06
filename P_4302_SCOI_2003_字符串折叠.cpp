#include<bits/stdc++.h>
using namespace std;
const int MN=520;
int f[MN][MN],len,num[MN];
string s;
bool check(int l,int r,int lenn){
    for(int i=l;i<l+lenn;i++){
        for(int j=i;j<=r;j+=lenn){
            if(s[i]!=s[j]) return 0;
        }
    }
    return 1;
}
int main(){
    cin>>s;
    len=s.length();
    s=' '+s;
    for(int i=1;i<=9;i++)num[i]=1;
    for(int i=10;i<=99;i++)num[i]=2;
    num[100]=3;
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=len;i++){
        f[i][i]=1;
    }
    for(int l=2;l<=len;l++){
        for(int i=1,j=i+l-1;j<=len;j++,i++){
            for(int k=i;k<j;k++){
                f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
                int kl=k-i+1;
                if(l%kl) continue;
                if(check(i,j,kl))f[i][j]=min(f[i][j],num[l/kl]+2+f[i][k]);
            }
        }
    }
    cout<<f[1][len];
    return 0;
}