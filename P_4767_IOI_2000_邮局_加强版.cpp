#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3012;
int v,p;
int pos[MN],f[MN][312],dis[MN][MN];

template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

int main(){
    memset(f,0x3f,sizeof(f));
    read(v);
    read(p);
    for(int i=1;i<=v;i++){
        read(pos[i]);
    }
    stable_sort(pos+1,pos+1+v);
    for(int i=1;i<=v;i++){
        dis[i][i]=0;
        for(int j=i+1;j<=v;j++){
            dis[i][j]=dis[i][j-1]+pos[j]-pos[(i+j)>>1];
        }
    }
    f[0][0]=0;
    for(int i=0;i<=v;i++) f[i][1]=dis[1][i];
    for(int i=1;i<=v;i++){
        for(int j=1;j<=min(p,i);j++){
            for(int k=j-1;k<i;k++){
                f[i][j]=min(f[i][j],f[k][j-1]+dis[k+1][i]);
            }
        }
    }
    cout<<f[v][p];
    return 0;
}