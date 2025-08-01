#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n;
string s;

struct PAM{
    int len[MN],nxt[MN][26],fail[MN],cnt[MN],tot,lst;

    PAM(){
        init();
    }

    void init(){
        fail[0]=1;
        len[1]=-1;
        tot=1;
    }

    int getfail(int u,int p){
        while(p-len[u]-1<=0||s[p-len[u]-1]!=s[p]){
            u=fail[u];
        }
        return u;
    }

    void insert(int c,int id){
        int p=getfail(lst,id);
        if(!nxt[p][c]){
            fail[++tot]=nxt[getfail(fail[p],id)][c];
            nxt[p][c]=tot;
            len[tot]=len[p]+2;
            cnt[tot]=cnt[fail[tot]]+1;
        }
        lst=nxt[p][c];
    }
}pam;


int main(){
    cin>>s;
    n=s.length();
    s=" "+s;
    for(int i=1,lst;i<=n;i++){
        if(i>1) s[i]=(s[i]-'a'+lst)%26+'a';
        pam.insert(s[i]-'a',i);
        cout<<(lst=pam.cnt[pam.lst])<<" ";

    }

    return 0;
}