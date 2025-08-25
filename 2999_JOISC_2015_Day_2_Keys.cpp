#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e4+15;
struct Node{
    int t,id;
    bool st;
}a[MN];
int f[2][MN][2],n,m,K,tot,ret,nxt[MN],c[MN],b[MN];

bool cmp(Node x,Node y){
    return x.t<y.t;
}

int main(){
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        a[++tot]={l,i,0};
        a[++tot]={r,i,1};
    }
    sort(a+1,a+1+tot,cmp);
    ret=a[1].t-a[tot].t+m;
    for(int i=1;i<tot;i++){
        int w=a[i+1].t-a[i].t;
        if(!a[i].st&&!a[i+1].st){
            c[a[i].id]+=w;   
        }else if(!a[i].st&&a[i+1].st){
            if(a[i].id==a[i+1].id) c[a[i].id]+=w;
            else nxt[a[i+1].id]=a[i].id,b[a[i].id]+=w;
        }else if(a[i].st&&!a[i+1].st){
            ret+=w;
        }else if(a[i].st&&a[i+1].st){
            c[a[i+1].id]+=w;
        }
    }
    int cur=0;
    for(int i=1;i<=n;i++){
        if(!b[i]){
            nxt[cur]=i;
            for(;nxt[cur];cur=nxt[cur]);
        }
    }
    f[0][0][0]=ret;
    int now=0,lst=1;
    for(int cur=nxt[0];cur;cur=nxt[cur]){
        now^=1;
        lst^=1;
        for(int j=0;j<=K;j++){
            for(int k=0;k<2;k++){
                if(!f[lst][j][k]) continue;
                f[now][j][0]=max(f[now][j][0],f[lst][j][k]);
                f[now][j+1][1]=max(f[now][j+1][1],f[lst][j][k]+k*b[cur]+c[cur]);
                f[lst][j][k]=0;
            }
        }
    }
    cout<<max(f[now][K][0],f[now][K][1]);
    return 0;
}