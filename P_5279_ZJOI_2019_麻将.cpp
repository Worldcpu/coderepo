#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
constexpr int MN=5520,MM=4100,MOD=998244353;
int n,tot,sum[MN],ed,mpp[MN][5];
ll f[2][MN][MM],xs[MN],pw[MN],inv[MN];
ll *pt1[MN],*pt2[MN];

struct Matrix{
    int mat[3][3];

    Matrix(){
        memset(mat,-1,sizeof(mat));
    }

    friend bool operator<(Matrix x,Matrix y){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(x.mat[i][j]!=y.mat[i][j]) return x.mat[i][j]<y.mat[i][j];
            }
        }
        return 0;
    }

    friend bool operator!=(Matrix x,Matrix y){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(x.mat[i][j]!=y.mat[i][j]) return 1;
            }
        }
        return 0;
    }

    void trans(Matrix &x,int y){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(mat[i][j]!=-1){
                    for(int k=0,rem=y-i-j;k<3&&i+j+k<=y;k++,rem--){
                        x.mat[j][k]=max(x.mat[j][k],min(i+mat[i][j]+rem/3,4ll));
                    }
                }
            }
        }
    }

    bool checkhu(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(mat[i][j]>=4) return 1;
            }
        }
        return 0;
    }

};

struct Node{
    Matrix pir[2];
    int cntpir;

    void clear(){
        pir[0]=Matrix(),pir[1]=Matrix();
        cntpir=-1e9;
    }

    void setst(){
        clear();
        cntpir=0;
        pir[0].mat[0][0]=0;
    }

    bool checkhu(){
        if(cntpir>=7){
            clear();
            return 1;
        }
        if(pir[1].checkhu()){
            clear();
            return 1;
        }
        return 0;
    }

    friend bool operator<(Node x,Node y){
        if(x.cntpir!=y.cntpir) return x.cntpir<y.cntpir;
        if(x.pir[0]!=y.pir[0]) return x.pir[0]<y.pir[0];
        if(x.pir[1]!=y.pir[1]) return x.pir[1]<y.pir[1];
        return 0;
    }

    friend Node operator+(Node x,int y){
        if(x.cntpir==-1e9) return x;
        Node ret;
        if(y>=2) x.pir[0].trans(ret.pir[1],y-2);
        x.pir[0].trans(ret.pir[0],y);
        x.pir[1].trans(ret.pir[1],y);
        ret.cntpir=x.cntpir+(y>=2);
        ret.checkhu();
        return ret;
    }

};
map<Node,int> mp;

void bfs(){
    queue<Node> q;
    Node start;
    start.setst();
    q.push(start);
    mp[start]=++tot;
    while(!q.empty()){
        Node f=q.front();
        q.pop();
        int num=mp[f];
        for(int i=0;i<=4;i++){
            Node to=f+i;
            if(mp.find(to)!=mp.end()) mpp[num][i]=mp[to];
            else{
                mpp[num][i]=mp[to]=++tot;
                q.push(to);
            }
        }
    }
    start.clear();
    ed=mp[start];
}

ll ksm(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

void clac(){
    int lim=n*4-13;
    Node st;
    st.setst();
    for(int i=0;i<=lim;i++) {pt1[i]=f[0][i];}
    for(int i=0;i<=lim;i++) {pt2[i]=f[1][i];}
    pt1[0][mp[st]]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=4-sum[i];j++){
            xs[j]=pw[4-sum[i]] * inv[j] % MOD * inv[4-sum[i]-j] % MOD;
        }
        for(int j=lim;j>=0;j--){
            for(int k=1;k<=tot;k++) pt2[j][k]=0;
            for(int k=1;k<=tot;k++){
                if(pt1[j][k]!=0){
                    for(int p=0;p<=4-sum[i]&&j+p<=lim;p++){
                        (pt2[j+p][mpp[k][p+sum[i]]] += pt1[j][k]*xs[p]) %= MOD;
                    }
                }
            }
        }
        for(int j=0;j<=lim;j++) swap(pt1[j],pt2[j]);
    }
}

signed main(){
    bfs();
    initpw();
    cin>>n;
    for(int i=1;i<=13;i++){
        int w,t;
        cin>>w>>t;
        sum[w]++;
    }
    clac();
    ll ans=0;
    for(int i=1,j=4*n-14;i<=4*n-13;i++,j--){
        for(int k=1;k<=tot;k++){
            if(k!=ed){
                (ans += pt1[i][k] * pw[i] % MOD * pw[j] % MOD) %= MOD;
            }
        }
    }
    cout<<(ans * inv[4*n-13]%MOD+1)<<endl;
    return 0;
}
