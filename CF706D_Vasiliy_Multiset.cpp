#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,MK=63;
int q;

struct Trie{
    int t[MN][2],cnt[MN],val[MN],tot;

    void insert(int x){
        int p=0;
        for(int i=MK;i>=0;i--){
            int k=(x>>i)&1ll;
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
            cnt[p]++;
        }
        val[p]=x;
    }

    void del(int x){
        int p=0;
        for(int i=MK;i>=0;i--){
            int k=(x>>i)&1ll;
            p=t[p][k];
            cnt[p]--;
        }
    }

    int query(int x){
        int p=0;
        for(int i=MK;i>=0;i--){
            int k=(x>>i)&1ll;
            if(t[p][k^1]&&cnt[t[p][k^1]]) p=t[p][k^1];
            else p=t[p][k];
        }
        return x^val[p];
    }

}t;


signed main(){
    cin>>q;
    while(q--){
        char op;
        int x;
        cin>>op>>x;
        if(op=='+') t.insert(x);
        if(op=='-') t.del(x);
        if(op=='?') cout<<t.query(x)<<'\n';
    }
    return 0;
}
