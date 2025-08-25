#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int cnt[MN<<1],n,x;
string st;

void init(){
    x=0;
    for(int i=-n;i<=n;i++) cnt[i+MN]=0;
}

void solve(){
    cin>>st;
    n=st.length();
    st=" "+st;
    init();
    for(int i=1;i<=n;i++){
        if(st[i]=='1'){
            cnt[x+MN]++;
            x++;
        }else{
            x--;
            cnt[x+MN]++;
        }
    }
    x=0;
    for(int i=1;i<=n;i++){
        if(cnt[MN+x-1]>0&&(!cnt[MN+x]||cnt[MN+x-1]>1)){
            x--;
            cnt[MN+x]--;
            cout<<0;
        }else{
            cnt[MN+x]--;
            x++;
            cout<<1;
        }
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}