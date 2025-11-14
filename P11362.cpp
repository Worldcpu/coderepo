#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MT=2,MOD=1e9+7;
int n,m,v;
bool flag;
map<int,int> mp;

struct Matrix{
    int mat[MT][MT];

    Matrix(int x=0){
        clear(x);
    }

    void clear(int x=0){
        memset(mat,0,sizeof(mat));
        for(int i=0;i<MT;i++) mat[i][i]=x;
    }

    friend Matrix operator*(const Matrix &x,const Matrix &y){
        Matrix ret;
        for(int i=0;i<MT;i++){
            for(int j=0;j<MT;j++){
                for(int k=0;k<MT;k++){
                    ret.mat[i][j]=(ret.mat[i][j]+x.mat[i][k]*y.mat[k][j]%MOD)%MOD;
                }
            }
        }
        return ret;
    }
}A,t1,t2;

Matrix ksm(Matrix a,int b){
    Matrix ret(1);
    while(b>0){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

void init(){
    A.clear();
    t1.clear();
    t2.clear();
    mp.clear();
    flag=1;
}

void solve(){
    cin>>n>>m>>v;
    init();
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        if(mp.count(x)&&mp[x]!=y){
            flag=0;
        }
        mp[x]=y;
    }
    if(!flag){
        cout<<0<<'\n';
        return;
    }

    if(mp[1]) A.mat[0][1]=1;
    else A.mat[0][0]=1;
    t1.mat[0][0]=v*v%MOD,t1.mat[1][0]=v*(v-1)%MOD,t1.mat[1][1]=v;
    t2.mat[0][1]=v*v%MOD,t2.mat[1][1]=v*(v-1)%MOD+1;

    int lst=1;
    for(auto p:mp){
        if(p.first==1) continue;
        A=A*ksm(t1,p.first-lst-1);
        A=A*t2;
        lst=p.first;
    }
    A=A*ksm(t1,n-lst);
    cout<<(A.mat[0][0]+A.mat[0][1])%MOD<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}