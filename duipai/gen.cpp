#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
constexpr int n=100,m=100,k=6;
int len[k+15];

inline char getC(){return 'a'+rnd()%26;}

signed main(){
    ios::sync_with_stdio(0);
    cout.tie(0);
    freopen("dp.in","w",stdout);
    cout<<n<<" "<<m<<" "<<k<<'\n';
    for(int i=1;i<=k;i++) cout<<(len[i]=rnd()%n+1)<<" ";
    cout<<'\n';
    for(int i=1;i<=n;i++) cout<<getC();
    cout<<'\n';
    for(int i=1;i<=m;i++) cout<<getC();
    cout<<'\n';
    for(int i=1;i<=k;i++){
        
        for(int j=1;j<=len[i];j++) cout<<getC();
        cout<<'\n';
    }
}
