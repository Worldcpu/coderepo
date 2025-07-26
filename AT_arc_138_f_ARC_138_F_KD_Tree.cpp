#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=35,MOD=1e9+7;
int n,p[MN],pb[MN],q[MN],qb[MN],f[MN][MN][MN][MN];

bool isin(int l,int r,int x){
    if(x>=l&&x<=r) return 1;
    return 0;
}

int dodp(int l,int r,int x,int y){ 
    if(l>r||x>y) return 0;
    if(~f[l][r][x][y]) return f[l][r][x][y];
    f[l][r][x][y]=0;
    int pb[MN]{},qb[MN]{},vx[MN]{},vy[MN]{},retx[MN]{},rety[MN]{},mpb[MN]{},mqb[MN]{},tot=0;
    for(int i=l;i<=r;i++){
        if(isin(x,y,p[i])){
            ++tot;
            vx[tot]=i;
            vy[tot]=p[i];
        }
    }
    sort(vy+1,vy+1+tot);
    for(int i=1;i<=tot;i++){
        pb[i]=lower_bound(vy+1,vy+1+tot,p[vx[i]])-vy;
        qb[pb[i]]=i;
    }
    if(tot<=1){
        f[l][r][x][y]=1;
        return f[l][r][x][y];
    }
    if(!isin(x,y,p[l])){
        f[l][r][x][y]=dodp(l+1,r,x,y);
        return f[l][r][x][y];
    }
    if(!isin(x,y,p[r])){
        f[l][r][x][y]=dodp(l,r-1,x,y);
        return f[l][r][x][y];
    }
    if(!isin(l,r,q[x])){
        f[l][r][x][y]=dodp(l,r,x+1,y);
        return f[l][r][x][y];
    }
    if(!isin(l,r,q[y])){
        f[l][r][x][y]=dodp(l,r,x,y-1);
        return f[l][r][x][y];
    }
    mpb[tot]=pb[tot],mqb[tot]=qb[tot];
    for(int i=tot-1;i>=1;i--){
        mpb[i]=min(pb[i],mpb[i+1]);
        mqb[i]=min(qb[i],mqb[i+1]);
    }
    int ret=0;
    for(int i=1;i<=tot;i++){
        retx[i]=dodp(l,vx[i]-1,x,y);
        for(int j=1;j<i;j++){
            retx[i]=(retx[i]-retx[j]*dodp(vx[j],vx[i]-1,x,y)%MOD+MOD)%MOD;
        }
        for(int j=1;j<=mpb[i];j++){
            retx[i]=(retx[i]-rety[j]*dodp(l,vx[i]-1,vy[j],y)%MOD+MOD)%MOD;
        }
        ret=(ret+retx[i]*dodp(vx[i],r,x,y)%MOD)%MOD;
        rety[i]=dodp(l,r,x,vy[i]-1);
        for(int j=1;j<i;j++){
            rety[i]=(rety[i]-rety[j]*dodp(l,r,vy[j],vy[i]-1)%MOD+MOD)%MOD;
        }
        for(int j=1;j<=mqb[i];j++){
            rety[i]=(rety[i]-retx[j]*dodp(vx[j],r,x,vy[i]-1)%MOD+MOD)%MOD;
        }
        ret=(ret+rety[i]*dodp(l,r,vy[i],y)%MOD)%MOD;
    }
    return f[l][r][x][y]=ret;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
        q[p[i]]=i;
    }
    memset(f,-1,sizeof(f));
    cout<<dodp(1,n,1,n);

    return 0;
}