#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200;
int n,lcp[MN][MN],cnt[MN],cntlen[MN],ans;
string st;

signed main(){
    freopen("b.in","r",stdin);
    cin>>st;
    n=st.size();
    st=" "+st;
    for(int i=n;i>=1;i--){
        for(int j=n;j>=i;j--){
            lcp[i][j]=(st[i]==st[j]?lcp[i+1][j+1]+1:0);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            cnt[j]=(cnt[j-1]+(lcp[j][i]>=i-j?1:0));
            cntlen[j]=(cntlen[j-1]+(lcp[j][i]>=i-j?i-j:0));
        }
        for(int j=i+3;j<=n;j++){
            int len=min(lcp[i][j],j-i-1);
            if(len<2) continue;
            int cntt=cnt[i-1]-cnt[max(0ll,i-len)];
            int cntl=cntlen[i-1]-cntlen[max(0ll,i-len)];
            ans+=cntt*len-cntl;            
        }
    }
    cout<<ans;
    return 0;
}

// hdkk 枚举 bc ef做法 Orz