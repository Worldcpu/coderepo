#include<bits/stdc++.h>
using namespace std;
const int MN=3000*3000+1;
// 我不会，我不会，啊啊啊啊啊啊
// 等会O(n^2)? 
struct trie{
    int son[2];
    int num;
}t[MN];
int cnt=1,n;
string st;

void insert(string s){
    int now=0;
    for(int i=0;i<s.size();i++){
        int ch=s[i]-'0';
        if(!t[now].son[ch]){
            t[now].son[ch]=cnt++;
        }
        now=t[now].son[ch];
        t[now].num++;
    }
}

void dfs(int u){
    if(t[u].num>1)cout<<t[u].num<<'\n';
    if(t[u].son[0]) dfs(t[u].son[0]);
    if(t[u].son[1]) dfs(t[u].son[1]);
}

int main(){
    cin>>n>>st;
    st=' '+st;
    for(int i=1;i<=n;i++){
        string tmp;
        for(int j=i;j<=n;j++){
            tmp.push_back(st[j]);
        }
        insert(tmp);
    }
    dfs(0);
    return 0;
}