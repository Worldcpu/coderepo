#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=20;
struct Node{
    int x,y;
}q[520];
int tot,ans,cnth[MN],cntl[MN],cntb[MN],h[MN][MN],l[MN][MN],b[MN][MN],a[MN][MN];
int color[MN][MN] = {
        {6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 7, 7, 7, 7, 7, 7, 7, 6},
        {6, 7, 8, 8, 8, 8, 8, 7, 6},
        {6, 7, 8, 9, 9, 9, 8, 7, 6},
        {6, 7, 8, 9, 10, 9, 8, 7, 6},
        {6, 7, 8, 9, 9, 9, 8, 7, 6},
        {6, 7, 8, 8, 8, 8, 8, 7, 6},
        {6, 7, 7, 7, 7, 7, 7, 7, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6}
};
int blk[MN][MN] = {
        {1, 1, 1, 2, 2, 2, 3, 3, 3},
        {1, 1, 1, 2, 2, 2, 3, 3, 3},
        {1, 1, 1, 2, 2, 2, 3, 3, 3},
        {4, 4, 4, 5, 5, 5, 6, 6, 6},
        {4, 4, 4, 5, 5, 5, 6, 6, 6},
        {4, 4, 4, 5, 5, 5, 6, 6, 6},
        {7, 7, 7, 8, 8, 8, 9, 9, 9},
        {7, 7, 7, 8, 8, 8, 9, 9, 9},
        {7, 7, 7, 8, 8, 8, 9, 9, 9}
};

bool cmp(Node x,Node y){
    if(cnth[x.x]!=cnth[y.x]) return cnth[x.x]<cnth[y.x];
    if(cntl[x.y]!=cntl[y.y]) return cntl[x.y]<cntl[y.y];
    return cntb[blk[x.x][x.y]]<cntb[blk[y.x][y.y]];
}

void dfs(int p){
    if(p>tot){
        int ret=0;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                ret+=a[i][j]*color[i][j];
            }
        }
        ans=max(ans,ret);
        return;
    }
    int x=q[p].x,y=q[p].y;
    for(int i=1;i<=9;i++){
        if(!b[blk[x][y]][i]&&!h[x][i]&&!l[y][i]){
            b[blk[x][y]][i]=1;
            h[x][i]=1;
            l[y][i]=1;
            a[x][y]=i;
            dfs(p+1);
            b[blk[x][y]][i]=0;
            h[x][i]=0;
            l[y][i]=0;
            a[x][y]=0;
        }
    }
}

signed main(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin>>a[i][j];
            int x=a[i][j];
            if(a[i][j]){
                h[i][x]=1;
                l[j][x]=1;
                b[blk[i][j]][x]=1;
            }else{
                q[++tot]={i,j};
                cnth[i]++;
                cntl[j]++;
                cntb[blk[i][j]]++;
            }
        }
    }
    stable_sort(q+1,q+1+tot,cmp);
    dfs(1);
    if(ans==0) cout<<-1;
    else cout<<ans;
    return 0;
}
