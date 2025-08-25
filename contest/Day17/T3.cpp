#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e4+15,INF=1e18;
int m,q,k,t,n,it;
int fixp[MN][4], fixintern;
int p[MN][4], fix[MN];
int f[2][1<<(16)];
vector<int> ss[5], snormal[5][5], sfull[5];

int getpos(int S,int x,int y){
    return (S>>(x*m+y))&1;
}

int cost(int x){
    return 2*x-m+1;
}

int dis(int a[],int b[]){
    return abs(a[0]-b[0])+abs(a[1]-b[1]);
}

void dfs(int x,int pc,int S,int col){
    if(x>=k){
        if(col<k){
            if(col==0) sfull[pc].push_back(S);
            else snormal[pc][col].push_back(S);
        }
        return;
    }
    for(auto s:ss[col?pc-1:pc]){
        dfs(x+1,pc,S|(s<<(x*m)),col);
        if(col==0 && pc>0) dfs(x+1,pc,S|(s<<(x*m)),x+1);
    }
}

void clearf(int a[]){
    for(int i=0;i<=m;i++)
        for(auto s:sfull[i]) a[s]=-INF;
    for(int c=1;c<k;c++)
        for(int i=1;i<=m;i++)
            for(auto s:snormal[i][c]) a[s]=-INF;
}

int fwork(){
    int now=0,lst=1;
    for(int it=0;it<n;it++,now^=1,lst^=1){
        clearf(f[now]);

        for(int i=0;i<=m;i++){
            for(auto s:sfull[i]) 
                if(f[lst][s]>-INF){
                for(int j=0;j<m;j++) 
                    if(getpos(s,0,j)==0){
                        f[now][s|(1<<j)]=max(f[now][s|(1<<j)],f[lst][s]+cost(j)*p[it][0]+fix[it]);
                    }
            }
        }

        for(int c=1;c<k;c++){
            for(int i=1;i<=m;i++){
                for(auto s:snormal[i][c]) 
                    if(f[lst][s]>-INF){
                        for(int j=0;j<m;j++) 
                            if(getpos(s,c,j)==0){
                                f[now][s|(1<<(c*m+j))]=max(f[now][s|(1<<(c*m+j))],f[now][s]+cost(j)*p[it][c]);
                            }
                    }
            }
        }

        for(int i=0;i<=m;i++)
            for(auto s:sfull[i]) if(f[lst][s]>-INF){
                f[now][s]=max(f[now][s],f[lst][s]);
            }
    }
    return f[now][(1<<(k*m))-1]+fixintern;
}

void init(){
    cin>>m>>q>>k>>t;
    for(int i=0;i<t;i++)
        for(int j=0;j<k;j++)
            cin>>fixp[i][j];

    fixintern=0;
    for(int i=0;i<t;i++)
        for(int j=i+1;j<t;j++)
            fixintern+=dis(fixp[i],fixp[j]);

    for(int i=0;i<m;i++)
        for(int j=0;j<k;j++)
            cin>>p[i][j];

    for(int i=0;i<m;i++){
        fix[i]=0;
        for(int j=0;j<t;j++)
            fix[i]+=dis(p[i],fixp[j]);
    }

    for(int i=0;i<(1<<m);i++)
        ss[__builtin_popcountll(i)].push_back(i);
    for(int i=0;i<=m;i++)
        dfs(0,i,0,0);

    n=m,it=0;
    clearf(f[1]);
    f[1][0]=0;
    fwork();
}

signed main(){
    freopen("net.in","r",stdin);
    freopen("net.out","w",stdout);
    init();
    for(int i=0;i<q;i++){
        for(int j=0;j<k;j++) cin>>p[n][j];
        fix[n]=0;
        for(int j=0;j<t;j++) fix[n]+=dis(p[n],fixp[j]);
        n++;
    }
    cout<<fwork()<<endl;
    return 0;
}
