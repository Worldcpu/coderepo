#include<iostream>
#include<cstring>
#include<algorithm>
#define ull unsigned long long
using namespace std;
int n,l,s;
const int MN=3e4+15,ML=256;
const ull mod=11451419191,base=131;
ull h1[MN][ML],h2[MN],pw[MN];
string ss[MN];
void initpw(){
    pw[0]=1;
    for(int i=1;i<=l;i++){
        pw[i]=pw[i-1]*base;
    }
}
int main(){
    int ans=0;
    cin>>n>>l>>s;
    initpw();
    for(int i=1;i<=n;i++){
        cin>>ss[i];
        for(int j=1;j<=ss[i].length();j++){
            h1[i][j]=(h1[i][j-1]*base+ss[i][j-1])%mod;
        }
    }
    for(int i=1;i<=l;i++){
        for(int j=1;j<=n;j++){
            h2[j]=h1[j][i-1]*pw[l-i]+h1[j][l]-h1[j][i]*pw[l-i];
        }
        int ret=1;
        sort(h2+1,h2+1+n);
        for(int j=1;j<=n;j++){
            if(h2[j]!=h2[j-1]){
                ret=1;
            }else{
                ans+=ret;
                ret++;
            }
        }
    }
    cout<<ans;
    return 0;
}