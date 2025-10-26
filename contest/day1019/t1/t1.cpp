#include<bits/stdc++.h>
using namespace std;
constexpr int MN=220;
int n,m,st;
int res[MN][MN];

void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            res[i][j]=0;
        }
    }
}


void solvem(){
    int stn=m%3;
    if(stn==0){
        for(int i=1;i<=m/3;i++){
            res[1][(i-1)*3+1]=1,res[1][(i-1)*3+2]=1,res[1][i*3]=0;
        }
    }else if(stn==1){
        res[1][1]=0;
        for(int i=1;i<=(m-1)/3;i++){
            res[1][(i-1)*3+2]=1,res[1][(i-1)*3+3]=1,res[1][i*3+1]=0;
        }
    }else{
        for(int i=1;i<=(m-1)/3;i++){
            res[1][(i-1)*3+1]=1,res[1][(i-1)*3+2]=1,res[1][i*3]=0;
        }
        res[1][m]=res[1][m-1]=1;
        return;
    }
}


    // m=2 stpos+py 是左上角
    void solvem2(int stpos){
        int st=n%3,py=0;
        if(n==2){
            res[1][stpos]=res[2][stpos+1]=res[1][stpos+1]=res[2][stpos]=2;
            return;
        }
        if(st==0){
           for(int i=1;i<=n/3;i++){
                res[(i-1)*3+1+py][stpos]=2;
                res[(i-1)*3+1+py][stpos+1]=2;
                res[(i-1)*3+2+py][stpos]=2;
                res[(i-1)*3+2+py][stpos+1]=2;
                res[i*3+py][stpos]=1;
                res[i*3+py][stpos+1]=1;
           }
        }else if(st==1){
            res[1][stpos]=res[1][stpos+1]=1;
           py=1;
           for(int i=1;i<=(n-1)/3;i++){
                res[(i-1)*3+1+py][stpos]=2;
                res[(i-1)*3+1+py][stpos+1]=2;
                res[(i-1)*3+2+py][stpos]=2;
                res[(i-1)*3+2+py][stpos+1]=2;
                res[i*3+py][stpos]=1;
                res[i*3+py][stpos+1]=1;
           }
        }else{
           for(int i=1;i<=(n-1)/3;i++){
                res[(i-1)*3+1+py][stpos]=2;
                res[(i-1)*3+1+py][stpos+1]=2;
                res[(i-1)*3+2+py][stpos]=2;
                res[(i-1)*3+2+py][stpos+1]=2;
                res[i*3+py][stpos]=1;
                res[i*3+py][stpos+1]=1;
           }
           res[n-1][stpos]=res[n-1][stpos+1]=res[n][stpos]=res[n][stpos+1]=2;
        }
    }

void solven(int stpos){
    int stn=n%3;
    if(stn==0){
        for(int i=1;i<=n/3;i++){
            res[(i-1)*3+1][stpos]=1,res[(i-1)*3+2][stpos]=1,res[i*3][stpos]=0;
        }
    }else if(stn==1){
        res[1][stpos]=0;
        for(int i=1;i<=(n-1)/3;i++){
            res[(i-1)*3+2][stpos]=1,res[(i-1)*3+3][stpos]=1,res[i*3+1][stpos]=0;
        }
    }else{
        for(int i=1;i<=(n-1)/3;i++){
            res[(i-1)*3+1][stpos]=1,res[(i-1)*3+2][stpos]=1,res[i*3][stpos]=0;
        }
        res[n][stpos]=res[n-1][stpos]=1;
    }
}

void solvenm(){
    int stm=m%3,stn=n%3;
    cerr<<stn<<' '<<stm<<'\n';

    if(stm==0){
        for(int i=1;i<=m/3;i++){
            solvem2((i-1)*3+1);
            solven((i)*3);
        }   
    }else if(stm==1){
        solven(1);
        for(int i=1;i<=(m-1)/3;i++){
            solvem2((i-1)*3+1+1);
            solven((i)*3+1);
        }

    }else{
        for(int i=1;i<=(m-1)/3;i++){
            solvem2((i-1)*3+1);
            solven((i)*3);
        }
        solvem2(m-1);
    }
  
}


void solve(){
    cin>>n>>m;
    init();
    if(n==1&&m==1){
        cout<<0<<'\n';
        return;
    }
    if(m==1){
        solven(1);
    }
    else if(n==1){
        solvem();
    }else{
        solvenm();
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<res[i][j]<<' ';
        }
        cout<<'\n';
    }
}

int main(){
    freopen("gift.in","r",stdin);
    freopen("gift.out","w",stdout);
    
    int T=1;
    while(T--){
        solve();
    }

    return 0;
}