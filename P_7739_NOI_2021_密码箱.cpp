#include <algorithm>
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353;
int n,q;
string s;

struct Matrix{
    int mat[2][2];

    Matrix(){
        mat[0][0]=mat[0][1]=mat[1][0]=mat[1][1]=0;
    }

    inline friend Matrix operator*(const Matrix &x,const Matrix &y){
        Matrix ans;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    ans.mat[i][j]=(1ll*ans.mat[i][j]+x.mat[i][k]*y.mat[k][j])%MOD;
                }
            }
        }
        return ans;
    }

}A,E,W;

struct FHQTreap{
    #define ls t[p].lson
    #define rs t[p].rson
    
    struct Node{
        int lson,rson,dat,siz,typ;
        Matrix val[2][2];
        bool rev,flip;
    }t[MN];
    int tot,rt;

    int newnode(int type){
        int p=++tot;
        t[p].dat=rand();
        t[p].typ=type;
        t[p].val[0][0]=t[p].val[0][1]=(type)?E:W;
        t[p].val[1][0]=t[p].val[1][1]=(type)?W:E;
        t[p].siz=1;
        return p;
    }

    void doreverse(int p){
        if(!t[p].rev) return;
        swap(t[p].val[0][0],t[p].val[0][1]);
        swap(t[p].val[1][0],t[p].val[1][1]);
        swap(ls,rs);
        t[ls].rev^=1;
        t[rs].rev^=1;
        t[p].rev^=1;
    }

    void doflip(int p){
        if(!t[p].flip) return;
        swap(t[p].val[0][0],t[p].val[1][0]);
        swap(t[p].val[0][1],t[p].val[1][1]);
        t[ls].flip^=1;
        t[rs].flip^=1;
        t[p].flip^=1;
        t[p].typ^=1;
    } 
    
    void pushup(int p){
        t[p].siz=t[ls].siz+t[rs].siz+1;
        t[p].val[0][0]=t[ls].val[0][0]*(t[p].typ?E:W)*t[rs].val[0][0];
        t[p].val[0][1]=t[rs].val[0][1]*(t[p].typ?E:W)*t[ls].val[0][1];
        t[p].val[1][0]=t[ls].val[1][0]*(t[p].typ?W:E)*t[rs].val[1][0];
        t[p].val[1][1]=t[rs].val[1][1]*(t[p].typ?W:E)*t[ls].val[1][1];
    }

    void pushdown(int p){
        if(!p) return;
        doreverse(p);
        doflip(p);
        if(ls){
            doreverse(ls);
            doflip(ls);
        }
        if(rs){
            doreverse(rs);
            doflip(rs);
        }
    }

    void split(int p,int k,int &x,int &y){
        if(!p){
            x=y=0;
            return;
        }
        pushdown((p));
        if(k>t[ls].siz){
            x=p;
            k-=t[ls].siz+1;
            split(rs, k, rs, y);
        }
        else{
            y=p;
            split(ls,k,x,ls);
        }
        pushup(p);
    }

    int merge(int x,int y){
        if(!x||!y){
            return x+y;
        }
        if(t[x].dat<t[y].dat){
            pushdown(x);
            t[x].rson=merge(t[x].rson,y);
            pushup(x);
            return x;
        }else{
            pushdown(y);
            t[y].lson=merge(x,t[y].lson);
            pushup(y);
            return y;
        }
    }

    // GETQJ FROM [l,r] while the Y is the output subtree
    void getqj(int l,int r,int &x,int &y,int &z){
        split(rt,r,x,z);
        split(x,l-1,x,y);
    }

    void reverse(int fl,int fr){
        int x,y,z;
        getqj(fl,fr,x,y,z);
        t[y].rev^=1;
        doreverse(y);
        rt=merge(merge(x,y),z);
    }

    void flip(int fl,int fr){
        int x,y,z;
        getqj(fl,fr,x,y,z);
        t[y].flip^=1;
        doflip(y);
        rt=merge(merge(x,y),z);
    }

    void pushback(int k){
        rt=merge(newnode(k),rt);
    }

    void solve(){
        int x=t[rt].val[0][0].mat[0][0],y=t[rt].val[0][0].mat[0][1];
        cout<<x<<" "<<(1ll*x+y)%MOD<<'\n';
    }

    void initrt(){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                t[rt].val[i][j]=A;
            }
        }
    }

}fhq;

void initmat(){
    E.mat[0][0]=2,E.mat[0][1]=MOD-1,E.mat[1][0]=1,E.mat[1][1]=0;
    W.mat[0][0]=1,W.mat[0][1]=1,W.mat[1][0]=0,W.mat[1][1]=1;
    A.mat[0][0]=A.mat[1][1]=1;
    fhq.initrt();
}

signed main(){
    srand(time(0));
    cin>>n>>q>>s;
    s=" "+s;
    initmat();
    for(int i=1;i<=n;i++){
        fhq.pushback(s[i]=='E');
    }
    fhq.solve();
    while(q--){
        string op;
        int l,r;
        cin>>op;
        if(op[0]=='A'){
            char x;
            cin>>x;
            ++n;
            fhq.pushback((x=='E'));
        }else if(op[0]=='F'){
            cin>>l>>r;
            swap(l,r);
            l=n-l+1,r=n-r+1;
            fhq.flip(l,r);
        }else{
            cin>>l>>r;
            swap(l,r);
            l=n-l+1,r=n-r+1;
            fhq.reverse(l, r);
        }
        fhq.solve();
    }
    

    return 0;
}