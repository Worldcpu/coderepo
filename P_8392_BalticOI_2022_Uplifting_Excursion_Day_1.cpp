#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MM=620;       
constexpr int MN=150000;        
constexpr int MAXB=40,INF=1e18;          
int f[2][2*MN+15],a[2*MM+15],n,m;
vector<int> pos[MAXB+5];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<=(n<<1);i++){
        cin>>a[i];
        if(i==n) continue;
        for(int j=0;j<=MAXB;j++){
            if((1ll<<j)<=a[i]){
                pos[j].push_back(i-n);
                a[i]-=(1ll<<j);
            }
        }
        for(int j=MAXB;j>=0;j--){
            if((1ll<<j)<=a[i]){
                pos[j].push_back(i-n);
                a[i]-=(1ll<<j);
            }
        }
    }
    f[0][MN]=INF;
    int now=0,lst=1,L=MN,R=MN;
    for(int i=0;i<=MAXB;i++){
        for(auto p:pos[i]){
            now^=1; lst^=1;
            int fl=min(L,max(0ll,L+p));
            int fr=max(R,min(2*MN,R+p));
            for(int j=L;j<=R;j++) f[now][j]=f[lst][j];
            for(int j=fl;j<L;j++) f[now][j]=0;
            for(int j=R+1;j<=fr;j++) f[now][j]=0;
            for(int j=L;j<=R;j++){
                int k=j+p;
                if(k>=0&&k<=2*MN)
                    f[now][k]=max(f[now][k],f[lst][j]+(1ll<<i));
            }
            L=fl; R=fr;
        }
        now^=1; lst^=1;
        for(int j=L;j<=R;j++) f[now][j]=0;
        int fl=MN,fr=MN;
        for(int j=L;j<=R;j++){
            if((j&1)==((m>>i)&1)){
                int to=MN+((j-MN)>>1);
                f[now][to]=max(f[now][to],f[lst][j]);
                fl=min(fl,to); fr=max(fr,to);
            }
        }
        L=fl; R=fr;
    }
    int idx=(m>>41)+MN;
    if(idx<L||idx>R||f[now][idx]<INF){
        cout<<"impossible";
    }else{
        cout<<f[now][idx]-INF+a[n];
    }
    return 0;
}
