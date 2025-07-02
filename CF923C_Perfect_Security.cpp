#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15;
int n,a[MN],b[MN];

struct Trie{
    int t[MN][2],cnt[MN],tot;

    void insert(int x){
        int p=0;
        for(int i=30;i>=0;i--){
            int k=(x>>i)&1;
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
            cnt[p]++;
        }
    }


    int query(int x){
        int p=0,ans=0;
        for(int i=30;i>=0;i--){
            int nxt=(x>>i)&1;
            if(!cnt[t[p][nxt]]) nxt=!nxt;
            ans=(ans<<1)+nxt;
            p=t[p][nxt];
            cnt[p]--;
        }
        return ans^x;
    }

}t;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        t.insert(b[i]);
    }
    for(int i=1;i<=n;i++){
        cout<<t.query(a[i])<<' ';
    }

    return 0;
}
