#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=3;
struct Node{
    int stp;
    string st;
}zro;
int mp[MN][MN][MN],mnans=1e9;
int fx[6]={1,-1,0,0,0,0};
int fy[6]={0,0,1,-1,0,0};
int fz[6]={0,0,0,0,1,-1};
string srt;
string to="01234567";
unordered_map<string,bool> vis;

string getmp(){
    string ret;
    for(int i=1;i<=2;i++){
        for(int j=1;j<=2;j++){
            for(int k=1;k<=2;k++){
               ret.push_back((char)(mp[i][j][k]+'0')); 
            }
        }
    }
    return ret;
}

void bfs(){
    queue<Node> q;
    q.push({0,srt});
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        if(u.st==to){
            mnans=min(mnans,u.stp);
            break;
        }
        if(vis[u.st]) continue;
        vis[u.st]=1;
        int posx=-1,posy=-1,posz=-1;       
        for(int i=1,cnt=-1;i<=2;i++){
            
            for(int j=1;j<=2;j++){
                for(int k=1;k<=2;k++){
                    mp[i][j][k]=u.st[++cnt]-'0';
                    if(u.st[cnt]=='0'){
                        posx=i;
                        posy=j;
                        posz=k;
                    }
                }
            }
        }
for(int d=0;d<6;d++){
    int nx=posx+fx[d],ny=posy+fy[d],nz=posz+fz[d];
    if(nx>=1&&nx<=2&&ny>=1&&ny<=2&&nz>=1&&nz<=2){
        swap(mp[posx][posy][posz],mp[nx][ny][nz]);
        q.push({u.stp+1,getmp()});
        swap(mp[posx][posy][posz],mp[nx][ny][nz]);
    } 
}


    }

}

int main(){
    freopen("t1.in","r",stdin);
    freopen("t1.out","w",stdout);
    for(int i=1;i<=8;i++){
        char ch;
        cin>>ch;
        srt.push_back(ch);
    }
    bfs();
    cout<<mnans;
    return 0;
}