#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2200;
const int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
int n,m,K,q,stx,sty;

namespace Sub1{

struct Node{
    int x,y,f,stp;
};
int f[MN][MN][4];
bitset<MN+2> mp[MN+2];

void dobfs(){
    queue<Node> q;
    q.push({stx,sty,0,0});    
    q.push({stx,sty,1,0});    
    q.push({stx,sty,2,0});    
    q.push({stx,sty,3,0});    
    memset(f,0x3f,sizeof(f));
    memset(f[stx][sty],0,sizeof(f[stx][sty]));
    while(!q.empty()){
        auto tp=q.front();
        q.pop();
        if(f[tp.x][tp.y][tp.f]<tp.stp) continue;
        if(f[tp.x][tp.y][(tp.f+1)%4]>tp.stp+1){
            f[tp.x][tp.y][(tp.f+1)%4]=tp.stp+1;
            q.push({tp.x,tp.y,(tp.f+1)%4,tp.stp+1});
        }
        if(f[tp.x][tp.y][(tp.f-1+4)%4]>tp.stp+1){
            f[tp.x][tp.y][(tp.f-1+4)%4]=tp.stp+1;
            q.push({tp.x,tp.y,(tp.f-1+4)%4,tp.stp+1});
        }
        int nx=tp.x+dx[tp.f],ny=tp.y+dy[tp.f];
        if(nx<1||nx>n||ny<1||ny>m||mp[nx][ny]) continue;
        if(f[tp.x+dx[tp.f]][tp.y+dy[tp.f]][tp.f]>tp.stp){
            f[tp.x+dx[tp.f]][tp.y+dy[tp.f]][tp.f]=tp.stp;
            q.push({tp.x+dx[tp.f],tp.y+dy[tp.f],tp.f,tp.stp});
        }
    }
}

void solve(){
    for(int i=1;i<=K;i++){
        int x,y;
        cin>>x>>y;
        mp[x][y]=1;
    }
    cin>>stx>>sty;
    dobfs();
    while(q--){
        int x,y;
        cin>>x>>y;
        int ret=min({f[x][y][0],f[x][y][1],f[x][y][2],f[x][y][3]});
        if(ret==0x3f3f3f3f){
            cout<<-1<<'\n';
        }else cout<<ret<<'\n';
    }
}
}

namespace Sub2{
    int kx,ky,st=-1;

    int calc(int x,int y){
        if(x==kx&&y==ky) return -1;
        if(st==0){
            if(ky<sty){
                if(x==stx&&y<ky) return 2;
                else return 0;
            }else{
                if(x==stx&&y>ky) return 2;
                else return 0;
            }
        }else if(st==1){
            if(kx<stx){
                if(y==sty&&x<kx) return 2;
                else return 0;
            }else{
                if(y==sty&&x>kx) return 2;
                else return 0;
            }
        }
        return 0;
    }

    void solve(){
        for(int i=1;i<=K;i++){
            cin>>kx>>ky;
        }
        cin>>stx>>sty;
        if(kx==stx) st=0;
        else if(ky==sty) st=1;
        if(K==0){
            while(q--){
                int x,y;
                cin>>x>>y;
                if(x==stx||y==sty) cout<<0<<'\n';
                else cout<<1<<'\n';
            }
        }else{
            while(q--){
                int x,y;
                cin>>x>>y;
                if(x==stx||y==sty) cout<<calc(x,y)<<'\n';
                else if(x==kx&&y==ky) cout<<-1<<'\n';
                else cout<<1<<'\n';
            }
        }
    }

}

int main(){
    cin>>n>>m>>K>>q;
    if(n<=2e3&&m<=2e3) Sub1::solve();
    else if(K<=1) Sub2::solve();
    return 0;
}
