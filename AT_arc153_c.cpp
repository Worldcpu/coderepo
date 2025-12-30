#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,a[MN],pre[MN],suf[MN],res[MN],sum;
bool flg;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pre[i]=pre[i-1]+a[i];
    }
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1]+a[i];
    }
    iota(res+1,res+1+n,1);
    for(int i=1;i<=n;i++){
        sum+=a[i]*res[i];
    }

    if(sum>0){
        for(int i=1;i<=n;i++){
            flg|=pre[i]>0;
            flg|=suf[i]<0;
        }
        if(!flg){
            cout<<"No\n";
            return 0;
        }

        int it=0;
        for(int i=1;i<=n;i++){
            if(pre[i]==1){
                it=i;
                break;
            }
        }
        if(it){
            for(int i=1;i<=it;i++){
                res[i]-=sum;
            }
        }else{
            for(int i=n;i>=1;i--){
                if(suf[i]==-1){
                    it=i;
                    break;
                }
            }
            for(int i=n;i>=it;i--) res[i]-=sum;
        }
    }else if(sum<0){
        for(int i=1;i<=n;i++){
            flg|=pre[i]<0;
            flg|=suf[i]>0;
        }
        if(!flg){
            cout<<"No\n";
            return 0;
        }

        int it=0;
        for(int i=1;i<=n;i++){
            if(pre[i]==-1){
                it=i;
                break;
            }
        }
        if(it){
            for(int i=1;i<=it;i++){
                res[i]-= -sum;
            }
        }else{
            for(int i=n;i>=1;i--){
                if(suf[i]==1){
                    it=i;
                    break;
                }
            }
            for(int i=n;i>=it;i--) res[i]+= -sum;
        }
    }

    cout<<"Yes\n";
    for(int i=1;i<=n;i++) cout<<res[i]<<' ';

    return 0;
}