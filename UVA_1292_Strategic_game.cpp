#include<bits/stdc++.h>
using namespace std;
const int MN=2000;
string s;
int n,f[MN][2];
vector<int> adj[MN];
int getson(){
    int lpos,rpos;
    for(int i=1;i<s.length();i++){
        if(s[i]=='('){
            lpos=i;
        }
        if(s[i]==')'){
            rpos=i;
            break;
        }
    }
    // cout<<"GETSON:"<<lpos<<" "<<rpos-lpos-1<<'\n';
    // cout<<s.substr(lpos+1,rpos-lpos-1)<<'\n';
    // cout<<what
    return stoi(s.substr(lpos+1,rpos-lpos-1));
}

void dfs(int u,int fa){
    f[u][1]=1;
    f[u][0]=0;
    for(auto v:adj[u]){
        if(v==fa) continue;
        dfs(v,u);
        f[u][0]+=f[v][1];
        f[u][1]+=min(f[v][1],f[v][0]);
    }
}

int main(){
    while (cin>>n)
    {
        memset(f,0,sizeof(f));
        for(int i=0;i<=n;i++){
            adj[i].clear();
        }
        for(int i=1;i<=n;i++){
            cin>>s;
            int v,u=s[0]-'0',sontot=getson();
            // cout<<"U:"<<sontot<<'\n';
            for(int i=1;i<=sontot;i++){
                cin>>v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
        dfs(0,-1);
        cout<<min(f[0][0],f[0][1])<<'\n';
    }
    
    return 0;
}