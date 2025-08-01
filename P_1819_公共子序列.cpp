#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=200+15,MOD=1e8;
int n,K,top,cnt;
bool vis[MN][MN][MN];
ll f[MN][MN][MN];
int st[MN];
string st1,st2,st3;

struct Seq{
    vector<int> nxt[59];

    int gnxt(int i,int c){
        auto ret=lower_bound(nxt[c].begin(),nxt[c].end(),i+1);
        if(ret==nxt[c].end()) return 0;
        return *ret;
    }

}sq[3];


void solve(int x,int y,int z){
    if(vis[x][y][z]) return;
    vis[x][y][z]=1;
    f[x][y][z]=1;
    for(int i=0;i<26;i++){
        if(sq[0].gnxt(x,i)&&sq[1].gnxt(y,i)&&sq[2].gnxt(z,i)){
            solve(sq[0].gnxt(x,i),sq[1].gnxt(y,i),sq[2].gnxt(z,i));
            f[x][y][z]=(f[x][y][z]+f[sq[0].gnxt(x,i)][sq[1].gnxt(y,i)][sq[2].gnxt(z,i)])%MOD;
        }
    }
}

int main(){
    cin>>n>>st1>>st2>>st3;
    st1=" "+st1;
    st2=" "+st2;
    st3=" "+st3;
    for(int i=1;i<=n;i++){
        int k=st1[i]-'a';
        sq[0].nxt[k].push_back(i);
    }
    for(int i=1;i<=n;i++){
        int k=st2[i]-'a';
        sq[1].nxt[k].push_back(i);
    }
    for(int i=1;i<=n;i++){
        int k=st3[i]-'a';
        sq[2].nxt[k].push_back(i);
    }
    solve(0,0,0);
    f[0][0][0]=(f[0][0][0]-1+MOD)%MOD;
    cout<<f[0][0][0];
    return 0;
}