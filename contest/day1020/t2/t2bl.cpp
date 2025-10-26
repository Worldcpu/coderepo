#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5520+15;
int n,a,b,h[MN],ans;
bool flagsub2=1;

namespace Sub1{
    constexpr int MD=22;
    bool del[MD];

int dfs(int lst,int res,int mode=0){
    if(lst==0){
        return res;
    }
    int ret=res;
    if(mode==0){
        ret=max(ret,dfs(lst,res,mode^1));
        for(int i=1;i<=n;i++){
            if(!del[i]){
                h[i]-=a;
                if(h[i]<=0){
                    del[i]=1;
                    ret=max(ret,dfs(lst-1,res+1,mode^1));
                    del[i]=0;
                }else{
                    ret=max(ret,dfs(lst,res,mode^1));
                }
                h[i]+=a;
            }
        }
    }else{
        for(int i=1;i<=n;i++){
            if(!del[i]){
                h[i]-=b;
                if(h[i]<=0){
                    del[i]=1;
                    ret=max(ret,dfs(lst-1,res,mode^1));
                    del[i]=0;
                }else{
                    ret=max(ret,dfs(lst,res,mode^1));
                }
                h[i]+=b;
                break;
            }
        }
    }
    return ret;
}

void solve(){
    cout<<dfs(n,0);
}

}

namespace Sub2{
    int f[MN][MN][2];

    void solve(){
        memset(f,128,sizeof(f));
        f[1][0][0]=0;
        int mxcnt=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=mxcnt;j++){
                for(int k=0;k<=1;k++){
                    if(k==1){
                        if(h[i]<=b){
                            f[i+1][j][0]=max(f[i][j][k],f[i+1][j][0]);
                            continue;
                        }
                        h[i]-=b;
                    }
                    if(h[i]<=a){
                        f[i+1][j][1]=max(f[i+1][j][1],f[i][j][k]+1);
                    }else{
                        for(int p=0;p<=j;p++){
                            int tmp=h[i]-p*a;
                            if(tmp<=0){
                                f[i+1][j-p][1]=max(f[i+1][j][k]+1,f[i][j-p][1]);
                                break;
                            }
                            if(h[i]<=b){
                                f[i+1][j+1][0]=max(f[i+1][j+1][0],f[i][j][k]);
                                mxcnt=max(mxcnt,j+1);
                            }
                            int dcnt=(h[i]-1)/b,dmod=h[i]%b;
                            if(dmod==0){
                                if(b<=a){
                                    f[i+1][j-p+dcnt][1]=max(f[i+1][j-p+dcnt][1],f[i][j][k]+1);
                                    mxcnt=max(mxcnt,j-p+dcnt);
                                }
                            }else if(dmod<=a){
                                f[i+1][j-dmod+dcnt][1]=max(f[i+1][j-dmod+dcnt][1],f[i][j][k]+1);
                                mxcnt=max(mxcnt,j-p+dcnt);
                            }
                        }
                    }
                }
            }
            for(int j=0;j<=mxcnt;j++){
                    cout<<"("<<(f[i][j][0]<0?-1:f[i][j][0])<<','<<(f[i][j][1]<0?-1:f[i][j][1])<<") ";
            }
            cout<<'\n';
        }
        int res=0;
        for(int i=0;i<=mxcnt;i++){
            res=max({res,f[n+1][i][0],f[n+1][i][1]});
        }
        cout<<res;
    }
}



signed main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    Sub1::solve();
    return 0;
}