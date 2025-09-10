#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,dg[MN],ans[MN];
string st[MN];
vector<int> adj[MN];

int getch(char x){
    if(x>='A'&&x<='Z'){
        return x-'A';
    }
    else return x-'a'+26;
}

int gethsh(int x,int y,int z){
    return getch(x)*52*52+getch(y)*52+getch(z);
}

void toposort(){
    queue<int> q;
    for(int i=0;i<MN;i++){
        if(!dg[i]){
            ans[i]=0;
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(ans[v]==-1){
                dg[v]--;
                if(ans[u]==0){
                    ans[v]=1;
                    q.push(v);
                }else if(dg[v]==0){
                    ans[v]=0;
                    q.push(v);
                }
            }
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>st[i];
        int len=st[i].length();
        int u=gethsh(st[i][len-3],st[i][len-2],st[i][len-1]),v=gethsh(st[i][0],st[i][1],st[i][2]);
        adj[u].push_back(v);
        dg[v]++;
    }
    memset(ans,-1,sizeof(ans));
    toposort();
    for(int i=1;i<=n;i++){
        int len=st[i].length();
        if(ans[gethsh(st[i][len-3],st[i][len-2],st[i][len-1])]==-1){
            cout<<"Draw\n";
        }else if(ans[gethsh(st[i][len-3],st[i][len-2],st[i][len-1])]==0){
            cout<<"Takahashi\n";
        }else cout<<"Aoki\n";
    }

    return 0;
}