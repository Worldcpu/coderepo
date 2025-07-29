#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,m,topa,topb,ans,a[MN],b[MN],sta[MN],stb[MN];

bool checkslopea(int x,int y,int z){
    int awa=(a[z]-a[y])*(y-x),qwq=(a[y]-a[x])*(z-y);
    return qwq>=awa;
}

bool checkslopeb(int x,int y,int z){
    int awa=(b[z]-b[y])*(y-x),qwq=(b[y]-b[x])*(z-y);
    return qwq>=awa;
}

bool checkslopeab(int l,int r,int x,int y){
    int awa=(a[y]-a[x])*(r-l),qwq=(b[r]-b[l])*(y-x);
    return awa<qwq;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    sta[++topa]=1;
    for(int i=2;i<=n;i++){
        while(topa>1&&checkslopea(sta[topa-1],sta[topa],i)) topa--;
        sta[++topa]=i;
    }
    stb[++topb]=1;
    for(int i=2;i<=m;i++){
        while(topb>1&&checkslopeb(stb[topb-1],stb[topb],i)) topb--;
        stb[++topb]=i;
    }
    int x=1,y=1;
    while(x!=topa||y!=topb){
        if(x==topa){
            ans+=(stb[y+1]-stb[y])*a[sta[x]];
            y++;
        }else if(y==topb){
            ans+=(sta[x+1]-sta[x])*b[stb[y]];
            x++;
        }
        else{
            if(checkslopeab(stb[y],stb[y+1],sta[x],sta[x+1])){
                ans+=(sta[x+1]-sta[x])*b[stb[y]];
                x++;
            }else{
                ans+=(stb[y+1]-stb[y])*a[sta[x]];
                y++;
            }
        }
    }
    cout<<ans;

    return 0;
}