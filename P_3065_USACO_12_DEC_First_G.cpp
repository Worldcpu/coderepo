#include<bits/stdc++.h>
using namespace std;
const int MN=8e7+15,MS=8e5+15;
struct node{
    int son[26];
    int num;
    bool isend;
}t[MN];
string str[MS];
int cnt=1,in[27],n;
bool e[27][27];
void insert(string s){
    int now=0;
    for(int i=0;i<s.size();i++){
        int ch=s[i]-'a';
        if(!t[now].son[ch]){
            t[now].son[ch]=cnt++;
        }
        now=t[now].son[ch];
        t[now].num++;
    }
    t[now].isend=1;
}

bool query(string s){
    queue<int> q;
    memset(e,0,sizeof(e));
    memset(in,0,sizeof(in));
    // for(int i=0;i<=26;i++){
    //     adj[i].clear();
    // }
    int now=0;
    for(int i=0;i<s.size();i++){
        int ch=s[i]-'a';
        if(t[now].isend) return 0;
        for(int j=0;j<26;j++){
            if(j!=ch&&t[now].son[j]&&(!e[ch][j])){
                e[ch][j]=1;
                in[j]++;
            }
        }
        now=t[now].son[ch];
    }
    for(int i=0;i<26;i++){
        if(!in[i]) q.push(i);
    }
    while(!q.empty()){
        int f=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(e[f][i]){
                in[i]--;
                if(!in[i]){
                    q.push(i);
                }
            }
        }
    }

    for(int i=0;i<26;i++){
        if(in[i]) return 0;
    }

    return 1;
}
vector<int> anss;
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
        insert(str[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(query(str[i])){
            ans++;
            anss.push_back(i);
        }
    }
    cout<<ans<<'\n';
    for(auto v:anss){
        cout<<str[v]<<'\n';
    }
    return 0;
}