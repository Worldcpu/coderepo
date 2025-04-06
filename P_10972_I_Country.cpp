#include<bits/stdc++.h>
using namespace std;
const int MN=16;
struct previous{
    int i,j,l,r,x,y;
}pre[MN][MN*MN][MN][MN][2][2];
int n,m,k,pi,pj,pl,pr,px,py;
int a[MN][MN],f[MN][MN*MN][MN][MN][2][2]{};

void print(previous p){
    if(p.j==0) return;
    print(pre[p.i][p.j][p.l][p.r][p.x][p.y]);
    for(int i=p.l;i<=p.r;i++){
        cout<<p.i<<" "<<i<<'\n';
    }
}

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            for(int l=1;l<=m;l++){
                for(int r=l;r<=m;r++){
                    int sum=0,tmp;
                    for(int p=l;p<=r;p++){
                        sum+=a[i][p];
                    }
                    if(j<r-l+1) continue;

                    f[i][j][l][r][0][0]+=sum;
                    f[i][j][l][r][1][0]+=sum;
                    f[i][j][l][r][0][1]+=sum;
                    f[i][j][l][r][1][1]+=sum;

                    //双边界拓展 1 0
                        tmp=0;
                        for(int p=l;p<=r;p++){
                            for(int q=p;q<=r;q++){
                                if(f[i-1][j-(r-l+1)][p][q][1][0]>tmp){
                                    tmp=f[i-1][j-(r-l+1)][p][q][1][0];
                                    pre[i][j][l][r][1][0]={i-1,j-(r-l+1),p,q,1,0};
                                }
                            }
                        }
                        f[i][j][l][r][1][0]+=tmp;

                    //左扩右收 1 1
                    tmp=0;
                    for(int p=l;p<=r;p++){
                        for(int q=r;q<=m;q++){
                            for(int y=0;y<=1;y++){
                                if(tmp<f[i-1][j-(r-l+1)][p][q][1][y]){
                                    tmp=f[i-1][j-(r-l+1)][p][q][1][y];
                                    pre[i][j][l][r][1][1]={i-1,j-(r-l+1),p,q,1,y};
                                }
                            }
                        }
                    }
                    f[i][j][l][r][1][1]+=tmp;
                    //左收右涨
                    tmp=-1e9;
                    for(int p=1;p<=l;p++){
                        for(int q=l;q<=r;q++){
                            for(int x=0;x<=1;x++){
                                if(tmp<f[i-1][j-(r-l+1)][p][q][x][0]){
                                    tmp=f[i-1][j-(r-l+1)][p][q][x][0];
                                    pre[i][j][l][r][0][0]={i-1,j-(r-l+1),p,q,x,0};
                                }
                            }
                        }
                    }
                    f[i][j][l][r][0][0]+=tmp;
                    //双收
                    tmp=-1e9;
                    for(int p=1;p<=l;p++){
                        for(int q=r;q<=m;q++){
                            for(int x=0;x<=1;x++){
                                for(int y=0;y<=1;y++){
                                    if(f[i-1][j-(r-l+1)][p][q][x][y]>tmp){
                                        //f[i][j][l][r][0][1]
                                        tmp=f[i-1][j-(r-l+1)][p][q][x][y];
                                        pre[i][j][l][r][0][1]={i-1,j-(r-l+1),p,q,x,y};
                                    }
                                }
                            }
                        }
                    }
                    f[i][j][l][r][0][1]+=tmp;

                }
            }
        }
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            for(int l=1;l<=m;l++){
                for(int r=l;r<=m;r++){
                    for(int x=0;x<=1;x++){
                        for(int y=0;y<=1;y++){
                            // ans=max(ans,f[i][j][l][r][x][y]);
                            if(ans<f[i][j][l][r][x][y]){
                                ans=f[i][j][l][r][x][y];
                                pi=i,pj=j,pl=l,pr=r,px=x,py=y;
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<"Oil : "<<ans<<'\n';
    print({pi,pj,pl,pr,px,py});
    return 0;
}