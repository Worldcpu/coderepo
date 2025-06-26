#include<bits/stdc++.h>
using namespace std;
constexpr int MN=4e5+15;
int n,mxlen;
string retst,mxs;

struct Trie{
    int t[MN][26],tot,cnt;
    bool tag[MN],end[MN];

    void build(string s){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[p]=1;
    }

    void dotag(string s){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            p=t[p][k];
            tag[p]=1;
        }
    }

    void dfs(int now){
        if(end[now]){
            cnt++;
            retst+='P';
        }
        if(cnt==n){
            cout<<retst.size()<<'\n';
            for(auto c:retst){
                cout<<c<<'\n';
            }
            return;
        }
        for(int i=0;i<26;i++){
            if(tag[t[now][i]]==0&&t[now][i]!=0){
                retst+=(char)i+'a';
                dfs(t[now][i]);
                retst+='-';
            }
        }
        for(int i=0;i<26;i++){
            if(tag[t[now][i]]&&t[now][i]!=0){
                retst+=(char)i+'a';
                dfs(t[now][i]);
                retst+='-';
            }
        }
    }

}t;


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        t.build(s);
        if(s.length()>mxlen){
            mxlen=s.length();
            mxs=s;
        }
    }
    t.dotag(mxs);
    t.dfs(0);
    return 0;
}
