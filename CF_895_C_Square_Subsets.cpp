#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55,MOD=1e9+7;
int n;
int pri[30] = { 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 , 41 , 43 , 47 , 53 , 59 , 61 , 67 } ;

struct xxj{
    int p[MN];

    void insert(int x){
        for(int i=19;i>=0;i--){
            if((x>>i)&1){
                if(!p[i]){
                    p[i]=x;
                    break;
                }
                x^=p[i];
            }
        }
    }
}xj;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,ret=0;
        cin>>x;
        for(int j=0;j<19;j++){
            if(x%pri[j]==0){
                int now=0;
                while(x%pri[j]==0){
                    x/=pri[j];
                    now^=1;
                }
                ret^=(now<<j);
            }
        }
        xj.insert(ret);
    }
    for(int i=0;i<=19;i++){
        if(xj.p[i]) n--;
    }
    cout<<(ksm(2,n)-1)%MOD;
    
    return 0;
}