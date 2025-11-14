#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,K,d[MN],ans;

void work(){
    priority_queue<pir,vector<pir>,greater<pir>> q;

    for(int i=n-K,cnt=K;i>=1;i--){
        if(cnt>=K){
            q.push(pir(d[i],i));
            cnt-=K;
        }else{
            auto tp=q.top();
            if(tp.first<d[i]){
                q.pop();
                q.push(pir(d[i],i));    
                cnt++;
            }else cnt++;
        }
    }
    while(!q.empty()){
        ans+=q.top().first;
        q.pop();
    }
    

}

void init(){
    ans=0;
}

void solve(){
    cin>>n>>K;
    init();
    for(int i=1;i<=n;i++){
        cin>>d[i];
    }
    work();
    cout<<ans<<'\n';
}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    #endif
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}