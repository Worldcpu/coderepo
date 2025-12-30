#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=5e5+15;
constexpr ull base=13131;
constexpr char ch[]={'A','C','G','T'};
int n,cnt,ans;
char a[MN],b[MN];
bool vis[MN];
unordered_map<ull,set<int>> mp;

void init(){
    mp.clear();
    cnt=ans=0;
    fill(vis+1,vis+1+n,0);
}

void solve(int n){
    // cin>>n;
    init();
    n=4*n;
    for(int i=1,r=0;i<=n;i++,r=(r+1)%4){
        // cin>>a[i];
        b[i]=ch[r];
    }
    for(int i=1;i<=n;i++){
        if(a[i]==b[i]) continue;
        cnt++;
        ull now=a[i]*base+b[i];
        mp[now].insert(i);
    }
    for(int i=1;i<=n&&cnt;i++){
        if(a[i]==b[i]||vis[i]) continue;
        ull fnow=b[i]*base+a[i];
        ull now=a[i]*base+b[i];
        if(mp[fnow].size()){
            vis[*mp[fnow].begin()]=1;
            mp[fnow].erase(mp[fnow].begin());
            cnt-=2;
            ans++;
        }
        mp[now].erase(i);
    }
    // cerr<<ans<<' '<<cnt<<'\n';
    // int ans1=1e9,ans2=1e9;
    // if(cnt%3==0){
    //     ans1=(ans+(cnt/3)*2);
    //     cout<<ans1<<'\n';
    // }else if(cnt%4==0){
    //     ans2=(ans+(cnt/4)*3);
    //     cout<<ans2<<'\n';
    // }else{
    //     cout<<(ans+(cnt/4)*3+(cnt-4*(cnt/4))/3*2)<<'\n';
    // }
}

void dfs(int pos,int ch1,int ch2,int ch3,int ch4){
    if(pos==4*n+1){
        solve(n);
        if(cnt==5){
            cout<<"Yes\n";
            for(int i=1;i<=4*n;i++){
                cout<<(char)a[i];
            }
            exit(0);
        }
        return;
    }
    for(int i=0;i<4;i++){
        a[pos]=ch[i];
        dfs(pos+1);
    }
}

signed main(){
    cin>>n;
    dfs(1);

    return 0;
}