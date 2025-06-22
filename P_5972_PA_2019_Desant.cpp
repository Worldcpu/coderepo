#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=55,INF=1e9;
int n,a[MN],cnt[MN],nxt[MN][MN],f[MN][MN],base[MN][MN];
vector<pir> ans[MN];


void chkmax(pir& a,pir b){
	if(a.first>b.first){
		a=b;
	}
	else if(a.first==b.first){
		a.second+=b.second;
	}
}


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    a[n+1]=n+1;
    for(int i=0;i<=n;i++){
        for(int j=i+1;j<=n+1;j++){
            nxt[i][j]=a[j];
        }
        sort(nxt[i]+i+1,nxt[i]+n+2);
        int tmp=1;
        for(int j=i+1;j<=n+1;j++){
            base[i][j]=tmp;
            tmp*=nxt[i][j]-nxt[i][j-1];
        }
        ans[i].resize(tmp,pir(INF,0ll));  
    }
    ans[0][0]=pir(0,1);
    for(int i=0;i<n;i++){
        int ret=-1;
        for(int j=i+1;j<=n;j++){
            if(nxt[i][j]==a[i+1]){
                ret=j;
                break;
            }
        }
        for(int j=0;j<ans[i].size();j++){
            int tmp=j;
            for(int k=n+1;k>=i+1;k--){
                cnt[k]=tmp/base[i][k];
                tmp%=base[i][k];
            }
            int add=0,to0=0,to1=0;
            for(int k=ret+1;k<=n+1;k++){
                add+=cnt[k];
            }
            for(int k=i+1;k<=n+1;k++){
                if(k<ret){
                    to0+=cnt[k]*base[i+1][k+1];
                    to1+=cnt[k]*base[i+1][k+1];
                }else if(k==ret) continue;
                else if(k==ret+1){
                    to0+=(cnt[k]+cnt[k-1])*base[i+1][k];
                    to1+=(cnt[k]+cnt[k-1]+1)*base[i+1][k];
                }else{
                    to0+=cnt[k]*base[i+1][k];
                    to1+=cnt[k]*base[i+1][k];
                }

            } 
            chkmax(ans[i+1][to0],ans[i][j]);
            chkmax(ans[i+1][to1],pir(ans[i][j].first+add,ans[i][j].second));
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[n][i].first<<" "<<ans[n][i].second<<'\n'; 
    return 0;
}
