#include<bits/stdc++.h>
using namespace std;
constexpr int MV=350,MP=30;
int v,p;
int pos[MV],f[MV][MP];

int val(int i,int j){
    int mid=(i+j)>>1;
    int ans=0;
    for(int p=i;p<=j;p++){
        ans+=abs(pos[mid]-pos[p]);
    }
    return ans;
}

int main(){
    memset(f,0x3f,sizeof(f));
    cin>>v>>p;
    for(int i=1;i<=v;i++){
        cin>>pos[i];
    }
    sort(pos+1,pos+1+v);
    f[0][0]=0;
    for(int i=1;i<=v;i++){
        for(int j=0;j<=p;j++){
            for(int k=0;k<i;k++){
                f[i][j]=min(f[i][j],f[k][j-1]+val(k+1,i));
            }
        }
    }
    cout<<f[v][p];
    return 0;
}