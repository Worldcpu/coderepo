#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e6+15;
int n,q;

struct Trie{
    int nxt[MN][65],end[MN],tot;

    int getx(char a){
        if(a>='A'&&a<='Z'){
            return a-'A';
        }else if(a>='a'&&a<='z'){
            return a-'a'+26;
        }else return a-'0'+52;
    }

    void init(){
        for(int i=0;i<=tot;i++){
            end[i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        tot=0;
    }

    void insert(const string &st){
        int p=0;
        for(auto ch:st){
            int k=getx(ch);
            if(!nxt[p][k]) nxt[p][k]=++tot;
            p=nxt[p][k];
            end[p]++;
        }
    }


    int query(const string &st){
        int p=0;
        for(auto ch:st){
            int k=getx(ch);
            if(!nxt[p][k]) return 0;
            p=nxt[p][k];
        }
        return end[p];
    }

}t;

void init(){
    t.init();
}

void solve(){
    cin>>n>>q;
    init();
    for(int i=1;i<=n;i++){
        string st;
        cin>>st;
        t.insert(st);
    }
    while(q--){
        string st;
        cin>>st;
        cout<<t.query(st)<<'\n';
    }
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}