#include<iostream>
#include<cstring>
using namespace std;
const int MN=450,MF=(1<<16)+15;
int w,n;
int t[MN],wei[MN],ml,f[MF],mt[MF],mw[MF];
int main(){
    cin>>w>>n;
    ml=(1<<n);
    for(int i=1;i<=n;i++){
        cin>>t[i]>>wei[i];
    }
    for(int i=0;i<ml;i++){
        for(int j=1;j<=n;j++){
            if(i&(1<<(j-1))){
                mt[i]=max(mt[i],t[j]);
                mw[i]+=wei[j];
            }
        }
    }
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=0;i<ml;i++){
        for(int j=i;;j=(j-1)&i){
            if(mw[i^j]<=w){
                f[i]=min(f[i],f[j]+mt[i^j]);
            }
            if(!j) break;
        }
    }
    cout<<f[ml-1];
    return 0;
}