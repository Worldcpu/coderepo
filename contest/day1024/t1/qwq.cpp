#include <bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
//#define int long long
#define ull unsigned long long
#define ll long long
#define db double
#define ili inline
#define fir first
#define sec second
#define pb push_back
#define pii pair<int,int>
#define lb(x) ((x)&(-x))
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
template <typename T>
ili void rd(T &x){
    int f=1;
    x=0;
    char c=getchar();
    while(c<'0'||c>'9') {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    x*=f;
}
template <typename T,typename...Args>
ili void rd(T &x,Args &...args) {
    rd(x),rd(args...);
}
template <typename T>
ili void wr(T x){
    if(x<0) putchar('-'),x=-x;
    if(x<10) putchar(x+'0');
    else wr<T>(x/10),putchar(x%10+'0');
}
using namespace std;
const int N=105;
int num[10]={119,36,93,109,46,107,123,37,127,111};
int T;
int a[N],n,m;
int ans;
int vis[(1<<21)];
void xpigeon(){
    cin>>n>>m;
    string s;
    for(int i=1;i<=n;i++){
        cin>>s;
        a[i]=0;
        for(int j=0;j<m;j++){
            a[i]<<=7;
            a[i]|=num[s[j]-'0'];
        }
    }
    ans=7*m;
    memset(vis,-1,sizeof(vis));
    int lst;
    for(register int s=0;s<(1<<(7*m));s++){
        #pragma unroll 32
        int tmp=__builtin_popcount(s);
        if(tmp>=ans) continue;
        bool flag=1;
        for(lst=1;lst<=n;lst++){
            if(vis[a[lst]&s]==s){flag=0;break;}
            vis[a[lst]&s]=s;
        }
        if(flag) ans=min(ans,tmp);
    }
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--) xpigeon();
    return 0;
}
